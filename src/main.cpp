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

	// test matrix
	cv::Mat test = (cv::Mat_<double>(4,4) << 4, 8, 6, 6, 6, 4, 11, 8, 8, 8, 9, 10, 8, 11, 10, 7);

	std::cout << "Test before stretch = " << std::endl << " " << test << std::endl << std::endl;

	double rmin, rmax;
	cv::minMaxLoc(test, &rmin, &rmax);

	for (int row = 0; row < test.rows; ++row) {
		for (int col = 0; col < test.cols; ++col) {
			test.at<double>(row,col) = Kynan::CalcSValue(test.at<double>(row,col), rmin, rmax, 4);
		}
	}

	std::cout << "Test after stretch = " << std::endl << " " << test << std::endl << std::endl;


	/*// load source image, 0 flag for grayscale
	cv::Mat src_image;
	src_image = cv::imread(argv[1],0);

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
	std::cout << "The max intensity is: " << rmax << std::endl; */

	/* Source:
	 * https://stackoverflow.com/questions/11977954/opencv-matrix-iteration
	 *//*
	for (int row = 0; row < src_image.rows; ++row) {
		uchar* p = src_image.ptr(row);
		for (int col = 0; col < src_image.cols; ++col) {
			*p = Kynan::CalcSValue((double)(*p), rmin, rmax, 8);
			p++;
		}
	}

	// generate new histogram
	cv::Mat proc_histogram;
	cv::Mat proc_image_hist = Kynan::GenerateSimpleHistogram(num_bins, &src_image, 1, 0,
							 proc_histogram, 1, &num_bins, &histogram_range, uniform, accumulate);

	// show processed image
	cv::namedWindow("Source image after full-scale contrast stretch", CV_WINDOW_AUTOSIZE);
	cv::imshow("Source image after full-scale contrast stretch", src_image);

	cv::namedWindow("Source histogram after full-scale contrast stretch", CV_WINDOW_AUTOSIZE);
	cv::imshow("Source histogram after full-scale contrast stretch", proc_image_hist);
	*/
	//cv::waitKey(0);

	return 0;
}
