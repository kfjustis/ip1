#include "histogram.h"

namespace Kynan {

cv::Mat GenerateHistogramImage(int num_bins, const cv::Mat* src_image, int nimages,
                                const int* channels, cv::Mat* hist,
                                int dims, const int* histSize, const float** ranges,
                                bool uniform, bool accumulate) {

    // calculate the histogram data from parameters
    cv::calcHist(src_image, nimages, channels, cv::Mat(), *hist, dims, histSize, ranges,
                 uniform, accumulate);

    // generate the histogram image from the data and normalize
    int histogram_width = 512;
    int histogram_height = 400;
    int bin_width = cvRound((double)histogram_width/num_bins);

    cv::Mat histogram_image(histogram_height, histogram_width, CV_8UC1, cv::Scalar(0,0,0));

    cv::normalize(*hist, *hist, 0, histogram_image.rows, cv::NORM_MINMAX, -1, cv::Mat());

    // draw with rectangles
	for (int i = 1; i < num_bins; ++i) {
		cv::rectangle(histogram_image, cv::Point(bin_width*(i), histogram_height),
									   cv::Point(bin_width*(i), histogram_height - cvRound(hist->at<float>(i))),
									   cv::Scalar(255, 0, 0), 1, cv::LINE_8, 0);
	}

    return histogram_image;
}

uchar CalcSValue(uchar r, uchar rmin, uchar rmax, unsigned int bpp) {
    // convert from char to pixel value
    uchar r_pix = r - '0';
    uchar rmin_pix = rmin - '0';
    uchar rmax_pix = rmax - '0';
    uchar s = '0' - '0';

    // calculate s
    s = std::round(((std::pow(2, bpp)) - 1) * ((r_pix - rmin_pix)/(rmax_pix - rmin_pix))) + '0';

    return s;
}

cv::Mat GenerateFSImage(const cv::Mat* src_image) {
    if (src_image == NULL) {
        return cv::Mat();
    }

    double rmin, rmax;
	cv::minMaxLoc(*src_image, &rmin, &rmax);

	cv::Mat proc_image = src_image->clone();

	 for (int row = 0; row < src_image->rows; ++row) {
 		for (int col = 0; col < src_image->cols; ++col) {
			proc_image.at<uchar>(row, col) = Kynan::CalcSValue(src_image->at<uchar>(row,col), rmin, rmax, 8);
 		}
	}

    return proc_image;
}

cv::Mat GenerateLinearImage(const cv::Mat* src_image, double c_scale, double b_scale) {
    if (src_image == NULL) {
        return cv::Mat();
    }

    cv::Mat lin_image = src_image->clone();
    uchar src_val = 0;
    int val_container = 0, new_val = 0;
    for (int row = 0; row < src_image->rows; ++row) {
       for (int col = 0; col < src_image->cols; ++col) {
           // grab the source value
           src_val = src_image->at<uchar>(row, col);
           val_container = src_val;

           // calculate the new value with clamping
           new_val = int (val_container * c_scale) + b_scale;
           if (new_val > 255) {
               new_val = 255;
           } else if (new_val < 0) {
               new_val = 0;
           }

           // drop new value into output image matrix
           lin_image.at<uchar>(row, col) = (uchar) new_val;
       }
   }

   return lin_image;
}

cv::Mat GenerateEqualizeImage(const cv::Mat* src_histogram, const cv::Mat* src_image, cv::Mat* eq_histogram, const unsigned int bpp) {
    if (src_histogram == NULL || src_image == NULL || eq_histogram == NULL) {
        std::cout << "histogram::GenerateEqualizeImage error - encountered null parameter(s)" << std::endl;
        return cv::Mat();
    }

    cv::Size hist_size = src_histogram->size();
    cv::Size src_size = src_image->size();

    double rmin, rmax;
	cv::minMaxLoc(*src_image, &rmin, &rmax);

    if (hist_size.width != 1) {
        std::cout << "histogram::GenerateEqualizeImage error - invalid histogram dimensions" << std::endl;
        return cv::Mat();
    }

    // generate H' histogram
    *eq_histogram = src_histogram->clone();
    float local_sum = 0, adjusted_intensity = 0;
    for (int i = 0; i < hist_size.height; ++i) {
        local_sum = 0;
        for (int j = 0; j < i; ++j) {
            local_sum += src_histogram->at<float>(j, 0);
        }
        adjusted_intensity = ((local_sum*(src_size.height-1)*bpp/(src_size.height*src_size.width)));
        if (adjusted_intensity < 0) {
            adjusted_intensity = (float) 0;
        } else if (adjusted_intensity > 255) {
            adjusted_intensity = (float) 255;
        }

        eq_histogram->at<float>(i, 0) = adjusted_intensity;
    }

    // use H' as lookup table to generate the equalized image
    cv::Mat eq_image = src_image->clone();
    uchar src_char = 0;
    int src_int = 0, new_int = 0;
    for (int row = 0; row < src_image->rows; ++row) {
       for (int col = 0; col < src_image->cols; ++col) {
           // grab the source value
           src_char = src_image->at<uchar>(row, col);
           src_int = src_char;

           // get the new_val from H'
           new_int = (int) eq_histogram->at<float>(src_int, 0);

           // drop new value into output image matrix
           eq_image.at<uchar>(row, col) = (uchar) new_int;
       }
   }

   return eq_image;
}

} // namespace
