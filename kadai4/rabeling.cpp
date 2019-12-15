#include "rabeling.h"
using namespace cv;
using namespace std;

cv::Mat rabeling(cv::Mat image)
{
	copyMakeBorder(image, image, 1, 1, 1, 1, BORDER_CONSTANT, Scalar(255));
	int rows = image.rows;
	int cols = image.cols;
	cout << rows << ", " << cols << endl;
	//imwrite("data2.png", image);
	Mat mapping = Mat(rows, cols, CV_8UC1);
	mapping = 255;

	int old_dir = 0, new_dir = 0;
	Point clockwise[8] = { Point(-1, 1), Point(0, 1), Point(1, 1),
							Point(1, 0), Point(1, -1),
							Point(0, -1), Point(-1, -1),
							Point(-1, 0) };
	return cv::Mat();
}
