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

	// ------------------------------
	// source image and its histogram
	// ------------------------------
	int num_bins = 256;

	float i_range[] = {0, 256};
	const float* histogram_range = {i_range};

	bool uniform = true;
	bool accumulate = false;

	cv::Mat src_histogram;
	cv::Mat src_hist_image = Kynan::GenerateHistogramImage(num_bins, &src_image, 1, 0,
							 &src_histogram, 1, &num_bins, &histogram_range, uniform, accumulate);

	// ---------------------------
	// full-scale contrast stretch
	// ---------------------------
	cv::Mat proc_image = Kynan::GenerateFSImage(&src_image);

	cv::Mat proc_histogram;
	cv::Mat proc_hist_image = Kynan::GenerateHistogramImage(num_bins, &proc_image, 1, 0,
							  &proc_histogram, 1, &num_bins, &histogram_range, uniform, accumulate);

	// ---------------------
	// linear transformation
	// ---------------------
	cv::Mat lin_image = Kynan::GenerateLinearImage(&src_image, 1.2, 30);

	cv::Mat lin_histogram;
	cv::Mat lin_hist_image = Kynan::GenerateHistogramImage(num_bins, &lin_image, 1, 0,
							  &lin_histogram, 1, &num_bins, &histogram_range, uniform, accumulate);

	// ----------------------
	// histogram equalization
	// ----------------------
	cv::Mat eq_histogram;
	cv::Mat eq_image = Kynan::GenerateEqualizeImage(&src_histogram, &src_image, &eq_histogram, 8);
	cv::Mat eq_hist_image = Kynan::GenerateHistogramImage(num_bins, &eq_image, 1, 0,
							&eq_histogram, 1, &num_bins, &histogram_range, uniform, accumulate);

  	// show source
	cv::namedWindow("Source image", CV_WINDOW_AUTOSIZE);
	cv::imshow("Source image", src_image);
	cv::namedWindow("Source histogram", CV_WINDOW_AUTOSIZE);
	cv::imshow("Source histogram", src_hist_image);

	cv::waitKey(0);

	// show fscs
	cv::namedWindow("Full-scale contrast stretch image", CV_WINDOW_AUTOSIZE);
	cv::imshow("Full-scale contrast stretch image", proc_image);
	cv::namedWindow("Full-scale contrast stretch histogram", CV_WINDOW_AUTOSIZE);
	cv::imshow("Full-scale contrast stretch histogram", proc_hist_image);

	cv::waitKey(0);

	// show linear transformation
	cv::namedWindow("Linear transformation image", CV_WINDOW_AUTOSIZE);
	cv::imshow("Linear transformation image", lin_image);
	cv::namedWindow("Linear transformation histogram", CV_WINDOW_AUTOSIZE);
	cv::imshow("Linear transformation histogram", lin_hist_image);

	cv::waitKey(0);

	// show equalized image
	cv::namedWindow("Equalized image", CV_WINDOW_AUTOSIZE);
	cv::imshow("Equalized image", eq_image);
	cv::namedWindow("Equalized image histogram", CV_WINDOW_AUTOSIZE);
	cv::imshow("Equalized image histogram", eq_hist_image);

	cv::waitKey(0);

	return 0;
}
