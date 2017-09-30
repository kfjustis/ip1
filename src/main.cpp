//#include <iostream>
//#include <stdio.h>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "histogram.h"

int main(int argc, char** argv) {

	if (argc != 2) {
		std::cout << "Invalid command line args\nUSAGE: " << argv[0] << " <image file>" << std::endl;
		return -1;
	}

	// load source image, 0 flag for grayscale
	cv::Mat src_image;
	src_image = cv::imread(argv[1],0);
	if (src_image.data == NULL) {
		std::cout << "Failed to load source image" << std::endl;
		return -1;
	}

	// graph source image histogram
	// number of bins
	int num_bins = 256;

	// intensity ranges
	float i_range[] = {0, 256};
	const float* histogram_range = {i_range};

	// histogram settings
	bool uniform = true;
	bool accumulate = false;

	// generate histogram
	cv::Mat src_histogram;

	cv::Mat src_image_hist = Kynan::GenerateSimpleHistogram(num_bins, &src_image, 1, 0,
							 src_histogram, 1, &num_bins, &histogram_range, uniform, accumulate);

	// show source image
	cv::namedWindow("Source image before full-scale contrast stretch", CV_WINDOW_AUTOSIZE);
	cv::imshow("Source image before full-scale contrast stretch", src_image);

	// show histogram
	cv::namedWindow("Source histogram before full-scale contrast stretch", CV_WINDOW_AUTOSIZE);
	cv::imshow("Source histogram before full-scale contrast stretch", src_image_hist);

	// TODO make a function!
	// do the contrast stretch on the source image
	// determine rmin and rmax
	double rmin, rmax;
	cv::minMaxLoc(src_image, &rmin, &rmax);

	std::cout << "The min intensity is: " << rmin << std::endl;
	std::cout << "The max intensity is: " << rmax << std::endl;

	cv::Mat proc_image = src_image.clone();

	 for (int row = 0; row < src_image.rows; ++row) {
 		for (int col = 0; col < src_image.cols; ++col) {
 			//proc_image.at<double>(row,col) = 0;
			//std::cout << Kynan::CalcSValue(src_image.at<uchar>(row,col), rmin, rmax, 8) << std::endl;
			//std::cout << src_image.at<uint8_t>(row, col) << std::endl;
			proc_image.at<uchar>(row, col) = Kynan::CalcSValue(src_image.at<uchar>(row,col), rmin, rmax, 8);
			//proc_image.at<uchar>(row, col) = 0;
 		}
	}

	// generate new histogram
	cv::Mat proc_histogram;
	cv::Mat proc_image_hist = Kynan::GenerateSimpleHistogram(num_bins, &proc_image, 1, 0,
							 proc_histogram, 1, &num_bins, &histogram_range, uniform, accumulate);

	// show processed image
	cv::namedWindow("Source image after full-scale contrast stretch", CV_WINDOW_AUTOSIZE);
	cv::imshow("Source image after full-scale contrast stretch", proc_image);

	cv::namedWindow("Source histogram after full-scale contrast stretch", CV_WINDOW_AUTOSIZE);
	cv::imshow("Source histogram after full-scale contrast stretch", proc_image_hist);

	cv::waitKey(0);

	return 0;
}
