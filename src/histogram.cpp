#include "histogram.h"

namespace Kynan {

cv::Mat GenerateSimpleHistogram(int num_bins, const cv::Mat* src_image, int nimages,
                                const int* channels, cv::Mat hist,
                                int dims, const int* histSize, const float** ranges,
                                bool uniform, bool accumulate) {

    // calculate the histogram data from parameters
    cv::calcHist(src_image, nimages, channels, cv::Mat(), hist, dims, histSize, ranges,
                 uniform, accumulate);

    // generate the histogram image from the data and normalize
    int histogram_width = 512;
    int histogram_height = 400;
    int bin_width = cvRound((double)histogram_width/num_bins);

    cv::Mat histogram_image(histogram_height, histogram_width, CV_8UC1, cv::Scalar(0,0,0));

    cv::normalize(hist, hist, 0, histogram_image.rows, cv::NORM_MINMAX, -1, cv::Mat());

    // draw with rectangles
	for (int i = 1; i < num_bins; ++i) {
		cv::rectangle(histogram_image, cv::Point(bin_width*(i), histogram_height),
									   cv::Point(bin_width*(i), histogram_height - cvRound(hist.at<float>(i))),
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
           /*std::cout << "Old val: " << val_container << std::endl;
           std::cout << "New val: " << new_val << std::endl << std::endl;*/

           // drop new value into output image matrix
           lin_image.at<uchar>(row, col) = (uchar) new_val;

           // Notes:
           /*std::cout << "Src val char: " << src_val << std::endl;
           std::cout << "Src val num: " << src_val - '0' << std::endl; // this does not
           std::cout << "Val container: " << val_container << std::endl;
           std::cout << "Val cont as char: " << (uchar) val_container << std::endl; // this works*/
       }
   }

   return lin_image;
}

cv::Mat GenerateTransform(const cv::Mat* src, unsigned int max_intensity, int M, int N) {
    if (src == NULL) {
        return cv::Mat();
    }

    uchar n_sum = 0;

    //std::cout << "Passed histogram: " << std::endl << *src << std::endl;

    cv::Mat trans_image = src->clone();
    for (int row = 0; row < src->rows; ++row) {
        for (int col = 0; col < src->cols; ++col) {
            // grab intensity value
            n_sum += src->at<uchar>(row,col);
            trans_image.at<uchar>(row,col) = ((max_intensity-1)/(M*N)) * n_sum;
        }
    }

    return trans_image;
}

} // namespace
