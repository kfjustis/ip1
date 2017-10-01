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
 * Applies a linear function to every pixel in the source image, thus generating an output image.
 * The linear function takes the form of "OUT = a * IN(i) + b" where "a" is the constrast scale
 * factor, "b" is the brightness scale factor, and "IN(i)" represents the i'th pixel from the input
 * image. Output values < 0 and > 255 get clamped to 0 and 255 respectively to comply with 8-bit
 * grayscale images.
 * Source: http://www.ece.ubc.ca/~irenek/techpaps/introip/manual01.html
 * PARAMS: src_image - reference to the original source image matrix
 *         c_scale   - the constrast scaling factor; contrast is reduced when c_scale is < 1
 *                                                   contrast is increased when c_scale is > 1
 *         b_scale   - the brightness scaling factor; brightness is reduced when b_scale is < 0
 *                                                    brightness is increased when b_scale is > 0
 * RETURN: lin_image - the new matrix containing the output image data on success, empty matrix on failure
 */
cv::Mat GenerateLinearImage(const cv::Mat* src_image, double c_scale, double b_scale);

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
