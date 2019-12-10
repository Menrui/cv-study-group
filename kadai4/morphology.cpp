#include "morphology.h"

using namespace cv;

cv::Mat erosion(cv::Mat image)
{
	Mat image_ = image.clone();

	int rows = image.rows;
	int cols = image.cols;
	bool check_white;

	for (int y = 0; y < rows; y++) {
		for (int x = 0; x < cols; x++) {

			check_white = false;
			
			for (int n = -1; n <= 1; n++) {
				for (int m = -1; m <= 1; m++) {
					if (x + m < 0 || y + n < 0 || x + m >= cols || y + n >= rows) {}
					else {
						
						if (image.at<unsigned char>(Point(x + m, y + n)) == 0)
							check_white = true;
					
					}

				}
			}

			if (check_white) {
				image_.at<unsigned char>(Point(x, y)) = 0;
			}
		}
	}
	return image_;
}

cv::Mat dilation(cv::Mat image)
{
	Mat image_ = image.clone();

	int rows = image.rows;
	int cols = image.cols;
	bool check_black;

	for (int y = 0; y < rows; y++) {
		for (int x = 0; x < cols; x++) {

			check_black = false;

			for (int n = -1; n <= 1; n++) {
				for (int m = -1; m <= 1; m++) {
					if (x + m < 0 || y + n < 0 || x + m >= cols || y + n >= rows) {}
					else {

						if (image.at<unsigned char>(Point(x + m, y + n)) == 255)
							check_black = true;

					}

				}
			}

			if (check_black) {
				image_.at<unsigned char>(Point(x, y)) = 255;
			}
		}
	}
	return image_;
}

cv::Mat closiong(cv::Mat image, int dilation_num, int erosion_num)
{
	Mat image_ = image.clone();

	for (int i = 0; i < dilation_num; i++) {
		image_ = dilation(image_);
	}
	for (int j = 0; j < erosion_num; j++) {
		image = erosion(image_);
	}

	return image_;
}

cv::Mat opening(cv::Mat image, int erosion_num, int dilation_num)
{
	Mat image_ = image.clone();

	for (int i = 0; i < erosion_num; i++) {
		image_ = erosion(image_);
	}
	for (int j = 0; j < dilation_num; j++) {
		image = dilation(image_);
	}

	return image_;
}
