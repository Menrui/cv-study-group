#include "bilinier.h"

using namespace cv;

Vec3b bilinier(cv::Mat image, double x, double y)
{
	unsigned char gauss_x = floor(x);
	unsigned char gauss_y = floor(y);

	Vec3b value = ((gauss_x + 1 - x) * (gauss_y + 1 - y) * image.at<Vec3b>(gauss_y, gauss_x) +
		(gauss_x + 1 - x) * (y - gauss_y) * image.at<Vec3b>(gauss_y + 1, gauss_x) +
		(x - gauss_x) * (gauss_y + 1 - y) * image.at<Vec3b>(gauss_y, gauss_x + 1) +
		(x - gauss_x) * (y - gauss_y) * image.at<Vec3b>(gauss_y + 1, gauss_x + 1));


	return value;
}
