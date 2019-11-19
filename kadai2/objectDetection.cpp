#include "objectDetection.h"

using namespace cv;

cv::Mat objectDetection(cv::Mat background, cv::Mat object)
{
	cv::Mat gray_back;
	cv::Mat gray_obj;
	cv::cvtColor(background, gray_back, cv::COLOR_BGR2GRAY);
	cv::cvtColor(object, gray_obj, cv::COLOR_BGR2GRAY);

	cv::Mat diff = difference(gray_obj, gray_back);
	cv::Mat binary_diff = binarization(diff);

	int rows = binary_diff.rows;
	int cols = binary_diff.cols;
	unsigned char value = 0;
	cv::Mat detection = object.clone();

	for (int j = 0; j < rows; j++) {
		for (int i = 0; i < cols; i++) {
			value = binary_diff.at<unsigned char>(j, i);
			if (value != 255) {
				detection.at<Vec3b>(j, i) = 0;
			}
		}
	}

	//imwrite("object.png", object);
	//imwrite("background.png", background);
	//imwrite("difference.png", diff);
	//imwrite("binary.png", binary_diff);


	return detection;
}
