#pragma once

#include<iostream>
#include<string>
#include<tuple>
#include<opencv2\opencv.hpp>
#include<math.h>

double distribution(cv::Mat image, unsigned char t);
cv::Mat binarization(cv::Mat image);