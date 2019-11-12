#include "nearest.h"

using namespace cv;

Vec3b nearest(cv::Mat image, double x, double y)
{	
	int gauss_x = (int)floor(x + 0.5);
	int gauss_y = (int)floor(y + 0.5);
	Vec3b value;
	if ((gauss_x < 0 || gauss_y < 0) || ( gauss_x >= image.rows || gauss_y >= image.cols)) {
		value = Vec3b(0, 0, 0);
	}
	else {
		value = image.at<Vec3b>(Point(gauss_x, gauss_y));
	}
	return value;
}
