#include "main.h"
using namespace cv;

int main() {
	Mat image = imread("..\\image\\data.png", 0);
	imshow("origin", image);
	Mat mapping = contourTracking(image);
	imshow("trace", mapping);
	waitKey();

	return -0;
}