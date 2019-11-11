#include "nearest.h"

using namespace cv;

Vec3b nearest(cv::Mat image, double x, double y)
{
	Vec3b value = image.at<Vec3b>((unsigned char)floor(y+0.5), (unsigned char)floor(x+0.5));
	return value;
}
