#include <iostream>
#include <stdio.h>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

int main(int argc, char** argv) {

	/*if (argc != 2) {
		std::cout << "Invalid command line args\nUSAGE: " << argv[0] << " <image file>" << std::endl;
		return -1;
	}*/

	// load image
	cv::Mat img;
	//img = cv::imread(argv[1],1);

	// show image
	//cv::namedWindow("Greyon", CV_WINDOW_AUTOSIZE);
	//cv::imshow("Greyon", img);
	std::cout << "We linked opencv2 and built. Waiting..." << std::endl;
	cv::waitKey(0);

	return 0;
}
