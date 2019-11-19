#include "difference.h"

cv::Mat difference(cv::Mat image1, cv::Mat image2)
{
	cv::Mat diff(image1.rows, image1.cols, image1.type());
	cv::absdiff(image1, image2, diff);
	return diff;
}
