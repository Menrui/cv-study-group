#include "main.h"
using namespace cv;

int main() {
	Mat image = imread("..\\image\\lenna.png");
	if (image.empty()) return -1;

	Mat gaussian_image = gaussianFilter(4, image);

	imshow("Origin", image);
	imshow("Gaussian", gaussian_image);
	imshow("Averaging", averagingFilter(image));
	imshow("Sobel_horizontal", sobelFilter(image, sobelMode::horizontal));
	imshow("Sobel_vertical", sobelFilter(image, sobelMode::vertical));
	imshow("Laplacian", laplacianFilter(image));
	waitKey();

	return 1;
}