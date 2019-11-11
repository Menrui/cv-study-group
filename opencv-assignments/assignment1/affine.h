#pragma once

#include<iostream>
#include<string>
#include<opencv2\opencv.hpp>
#include "bilinier.h"
#include "nearest.h"

std::tuple<double, double> pixelAffine(cv::Mat A, int x, int y);
cv::Mat imageAffine(double A[3][3], cv::Mat image, std::string mode);