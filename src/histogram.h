# pragma once

#include <iostream>
#include <cmath>

#include "opencv2/imgproc/imgproc.hpp"

namespace Kynan {

/*
 * Generates a basic rectangle histogram for an 8 bit image.
 */
cv::Mat GenerateSimpleHistogram(int num_bins, const cv::Mat* src_image, int nimages,
                                const int* channels, cv::Mat hist,
                                int dims, const int* histSize, const float** ranges,
                                bool uniform=true, bool accumulate=false);

/*
 * Generates a basic histogram image from a previously generated histogram matrix (the data).
 * Automatically normalizes the image as well.

cv::Mat generateSimpleHistogramImage(int histogram_width, int histogram_height, bin_width);
*/

/*
 * Calculates the new pixel value by way of full-scale contrast stretch.
 * PARAMS: double r      - the original pixel value
 *         double rmin   - the minimum intensity value for the image matrix
 *         double rmax   - the maximum intensity value for the image matrix
 *         int bpp       - the number of bits per pixel to represent the image
 * RETURN: unsigned char - the new value pixel value
 */
unsigned char CalcSValue(double r, double rmin, double rmax, int bpp);

} // namespace
