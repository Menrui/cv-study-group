#include "bilinier.h"

using namespace cv;

Vec3b bilinier(cv::Mat image, double x, double y)
{
	int gauss_x = floor(x);
	int gauss_y = floor(y);
	Vec3b value;

	if ((gauss_x < 0 || gauss_y < 0) || (gauss_x >= image.cols-1 || gauss_y >= image.rows-1)) {
		value = Vec3b(0, 0, 0);
	}
	else {
		value = 
			(gauss_x + 1.0 - x) * (gauss_y + 1.0 - y) * image.at <Vec3b>(Point(gauss_x, gauss_y)) +
			(gauss_x + 1.0 - x) * (y - gauss_y) * image.at <Vec3b>(Point(gauss_x, gauss_y + 1)) +
			(x - gauss_x) * (gauss_y + 1.0 - y) * image.at <Vec3b>(Point(gauss_x + 1, gauss_y)) +
			(x - gauss_x) * (y - gauss_y) * image.at <Vec3b>(Point(gauss_x + 1, gauss_y + 1));
	}

	return value;
}
