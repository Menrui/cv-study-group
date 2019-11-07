#include<opencv2\opencv.hpp>
using namespace cv;

int main() {
	Mat image = imread("..\\..\\lenna.png");
	if (image.empty()) return -1;

	imshow("imshow test", image);
	waitKey();

	return 0;
}