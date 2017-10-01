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
 * PARAMS: uchar r          - the original pixel value
 *         uchar rmin       - the minimum intensity value for the image matrix
 *         uchar rmax       - the maximum intensity value for the image matrix
 *         unsigned int bpp - the number of bits per pixel to represent the image
 * RETURN: uchar - the new value pixel value
 */
uchar CalcSValue(uchar r, uchar rmin, uchar rmax, unsigned int bpp);

/*
 * Generates a new image using full-scale contrast stretching from a source image.
 * PARAMS: src_image - reference to the original source image matrix
 * RETURN: the new image as type cv::Mat on success, empty matrix on failure
 */
cv::Mat GenerateFSImage(const cv::Mat* src_image);

/*
 * Transforms intensity values from an input image (src) into acceptable new values using
 * discrete histogram linearization.
 * PARAMS: src           - reference to the original source matrix
 *         max_intensity - the largest intensity value in the source matrix
 *         M             - the height dimension for the source image
 *         N             - the width dimension for the source image
 * RETURN: trans_image   - the new image matrix with transformed intensity values,
                           returns an empty matrix on failure
 */
cv::Mat GenerateTransform(const cv::Mat* src, unsigned int max_intensity, int M, int N);

} // namespace
