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

	// do the contrast stretch on the source image
	// determine rmin and rmax
	double rmin, rmax;
	cv::minMaxLoc(src_image, &rmin, &rmax);

	std::cout << "The min intensity is: " << rmin << std::endl;
	std::cout << "The max intensity is: " << rmax << std::endl;

	/* Source:
	 * https://stackoverflow.com/questions/11977954/opencv-matrix-iteration
	 */
	for (int row = 0; row < src_image.rows; ++row) {
		uchar* p = src_image.ptr(row);
		for (int col = 0; col < src_image.cols; ++col) {
			//Kynan::CalcSValue(src_image.data[0], rmin, rmax, 8);
			//std::cout << ((*p) - '0') << std::endl;
			//*p++
			*p = Kynan::CalcSValue((double)(*p), rmin, rmax, 8);
			p++;
		}
	}

	// show processed image
	cv::namedWindow("Source image after full-scale contrast stretch", CV_WINDOW_AUTOSIZE);
	cv::imshow("Source image after full-scale contrast stretch", src_image);

	cv::waitKey(0);

	return 0;
}
