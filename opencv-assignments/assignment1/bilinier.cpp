#include "bilinier.h"

using namespace cv;

Vec3b bilinier(cv::Mat image, double x, double y)
{
	int gauss_x = floor(x);
	int gauss_y = floor(y);
	Vec3b value;

	if ((gauss_x < 0 || gauss_y < 0) || (gauss_x >= image.rows || gauss_y >= image.cols)) {
		value = Vec3b(0, 0, 0);
	}
	else {
		value = (Vec3b)((gauss_x + 1.0 - x) * (gauss_y + 1.0 - y) * image.at<Vec3i>(gauss_y, gauss_x) +
			(gauss_x + 1.0 - x) * (y - gauss_y) * image.at<Vec3i>(gauss_y + 1, gauss_x) +
			(x - gauss_x) * (gauss_y + 1.0 - y) * image.at<Vec3i>(gauss_y, gauss_x + 1) +
			(x - gauss_x) * (y - gauss_y) * image.at<Vec3i>(gauss_y + 1, gauss_x + 1));
	}

	return value;
}
