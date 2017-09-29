#include <iostream>
#include <stdio.h>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

int main(int argc, char** argv) {

	if (argc != 2) {
		std::cout << "Invalid command line args\nUSAGE: " << argv[0] << " <image file>" << std::endl;
		return -1;
	}

	// load image
	cv::Mat img;
	// 0 flag for grayscale image
	img = cv::imread(argv[1],0);

	// show image
	cv::namedWindow("Source image", CV_WINDOW_NORMAL);
	cv::imshow("Source image", img);
	cv::waitKey(0);

	return 0;
}
