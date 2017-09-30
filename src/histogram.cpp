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
    double rmin, rmax;
	cv::minMaxLoc(*src_image, &rmin, &rmax);

	std::cout << "The min intensity is: " << rmin << std::endl;
	std::cout << "The max intensity is: " << rmax << std::endl;

	cv::Mat proc_image = src_image->clone();

	 for (int row = 0; row < src_image->rows; ++row) {
 		for (int col = 0; col < src_image->cols; ++col) {
			proc_image.at<uchar>(row, col) = Kynan::CalcSValue(src_image->at<uchar>(row,col), rmin, rmax, 8);
 		}
	}

    return proc_image;
}

} // namespace
