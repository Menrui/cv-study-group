#include "main.h"
using namespace cv;

int main() {
	Mat image = imread("..\\image\\lenna.png");
	Mat e = imread("..\\image\\e.png", 0);
	if (image.empty()) return -1;

	Mat gaussian_image = gaussianFilter(4, image);

	imshow("Origin", image);
	imshow("Gaussian", gaussian_image);
	imshow("Averaging", averagingFilter(image));
	imshow("Sobel_horizontal", sobelFilter(image, sobelMode::horizontal));
	imshow("Sobel_vertical", sobelFilter(image, sobelMode::vertical));
	imshow("Laplacian", laplacianFilter(image));
	imshow("erosion", erosion(e));
	imshow("dilation", dilation(e));
	imshow("opening", opening(e, 3, 3));
	imshow("closing", closiong(e, 3, 3));
	waitKey();

	return 1;
}