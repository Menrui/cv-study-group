#include "main.h"
using namespace cv;

int main() {
	Mat image = imread("..\\image\\data.png", 0);

	image = closiong(image, 1, 1);
	image = opening(image, 1, 1);
	imshow("origin", image);
	Mat mapping = contourTracking(image);
	imshow("trace", mapping);
	waitKey();

	return -0;
}