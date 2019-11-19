#pragma once

#include<iostream>
#include<string>
#include<tuple>
#include<opencv2\opencv.hpp>

#include "difference.h"
#include "binarization.h"

cv::Mat objectDetection(cv::Mat background, cv::Mat object);