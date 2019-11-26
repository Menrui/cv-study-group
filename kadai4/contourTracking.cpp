#include "contourTracking.h"
using namespace cv;

cv::Mat contourTracking(cv::Mat image)
{
	int rows = image.rows;
	int cols = image.cols;
	Mat result = Mat(rows, cols, CV_8UC1);

	//raster scan
	for (int y = 0; y < rows; y++) {
		for (int x = 0; x < cols; x++) {

			//clockwise search
			

		}
	}
	
	return cv::Mat();
}
