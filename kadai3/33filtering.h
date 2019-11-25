#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include<iostream>
#include<string>
#include<tuple>
#include<opencv2\opencv.hpp>

enum class sobelMode {vertical, horizontal};
cv::Mat filtering(cv::Matx33d kernel, cv::Mat image);
cv::Mat averagingFilter(cv::Mat image);
cv::Mat gaussianFilter(double sigma, cv::Mat image);
double gaussianFunction(double sigma, int x, int y);
cv::Mat sobelFilter(cv::Mat image, sobelMode mode);
cv::Mat laplacianFilter(cv::Mat image);