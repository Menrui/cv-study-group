#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include<iostream>
#include<string>
#include<tuple>
#include<opencv2\opencv.hpp>

cv::Mat erosion(cv::Mat image);
cv::Mat dilation(cv::Mat image);
cv::Mat closiong(cv::Mat image, int dilation_num, int erosion_num);
cv::Mat opening(cv::Mat image, int erosion_num, int dilation_num);