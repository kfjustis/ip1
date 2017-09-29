#include <iostream>
#include <stdio.h>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

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

	// histogram data matrix
	cv::Mat src_histogram;

	// calculate the histogram data
	cv::calcHist(&src_image, 1, 0, cv::Mat(), src_histogram, 1, &num_bins, &histogram_range, uniform, accumulate);

	// draw the histogram
	int histogram_width = 512;
	int histogram_height = 400;
	int bin_width = cvRound((double)histogram_width/num_bins);

	// create histogram image
	cv::Mat histogram_image(histogram_height, histogram_width, CV_8UC1, cv::Scalar(0,0,0));

	// normalize values to [0, histogram_image.rows]
	cv::normalize(src_histogram, src_histogram, 0, histogram_image.rows, cv::NORM_MINMAX, -1, cv::Mat());

	// use rectangles to show histogram
	for (int i = 1; i < num_bins; ++i) {
		cv::rectangle(histogram_image, cv::Point(bin_width*(i), histogram_height),
									   cv::Point(bin_width*(i), histogram_height - cvRound(src_histogram.at<float>(i))),
									   cv::Scalar(255, 0, 0), 1, cv::LINE_8, 0);
	}

	// do the contrast stretch on the source image
	

	// show source image
	cv::namedWindow("Source image", CV_WINDOW_AUTOSIZE);
	cv::imshow("Source image", src_image);

	// show histogram
	cv::namedWindow("Source histogram", CV_WINDOW_AUTOSIZE);
	cv::imshow("Source histogram", histogram_image);


	cv::waitKey(0);

	return 0;
}
