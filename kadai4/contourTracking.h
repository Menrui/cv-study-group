#pragma once

#include<iostream>
#include<string>
#include<tuple>
#include<opencv2\opencv.hpp>

enum class enterDirection {from_left, from_right, from_top, from_bottom};
enum class Direction { left, top_left, top, top_right, right, bottom_right, bottom, bottom_left};
enum class pixelDirection { left, top_left, top, top_right, right, bottom_right, bottom, bottom_left, none};
cv::Mat contourTracking(cv::Mat image);
pixelDirection clockwiseSearch(cv::Mat image, cv::Mat map, int x, int y, enterDirection mode);
pixelDirection clockwise(cv::Mat image, int x, int y, Direction begin);