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

	// show souce histogram
	cv::namedWindow("Source histogram before full-scale contrast stretch", CV_WINDOW_AUTOSIZE);
	cv::imshow("Source histogram before full-scale contrast stretch", src_image_hist);

	cv::Mat proc_image = Kynan::GenerateFSImage(&src_image);

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
