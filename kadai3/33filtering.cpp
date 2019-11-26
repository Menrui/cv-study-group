#include "33filtering.h"
using namespace cv;
using namespace std;

cv::Mat filtering(cv::Matx33d kernel, cv::Mat image)
{
	Mat kernel_ = Mat(kernel);
	Mat image_ = image.clone();
	int rows = image.rows;
	int cols = image.cols;
	int cnt=0;

	Vec3b center_value = 0;
	for (int y = 0; y < rows; y++) {
		for (int x = 0; x < cols; x++) {
			center_value = 0;
			
			for (int n = -1; n <= 1; n++) {
				for (int m = -1; m <= 1; m++) {
					if (x + m < 0 || y + n < 0 || x + m >= cols || y + n >= rows) {
						center_value += Vec3b::ones()*128 * kernel_.at<double>(Point(m+1, n+1));
					}
					else {
						center_value += image.at<Vec3b>(Point(x + m, y + n)) * kernel_.at<double>(Point(m+1, n+1));
					}
					
				}
			}

			image_.at<Vec3b>(Point(x, y)) = center_value;
		}
	}
	return image_;
}

cv::Mat averagingFilter(cv::Mat image)
{
	Matx33d averaging_kernel;
	averaging_kernel << 1.0/9.0, 1.0 /9.0, 1.0 /9.0, 1.0 /9.0, 1.0 /9.0, 1.0 /9.0, 1.0 /9.0, 1.0 /9.0, 1.0 /9.0;
	cout << "averaging_kernel=\n" << averaging_kernel << endl;

	return filtering(averaging_kernel, image);
}

cv::Mat gaussianFilter(double sigma, cv::Mat image)
{
	Matx33d gaussian_kernel;
	double sum = 0;

	for (int n = -1; n <= 1; n++) {
		for (int m = -1; m <= 1; m++) {
			gaussian_kernel(n+1, m+1) = gaussianFunction(sigma, m, n);
			sum += gaussianFunction(sigma, m, n);
		}
	}
	gaussian_kernel = gaussian_kernel * (1.0 / sum);
	cout << "gaussian_kernel=\n" << gaussian_kernel << endl;
	Mat image_ = filtering(gaussian_kernel, image);

	return image_;
}

double gaussianFunction(double sigma, int x, int y) {
	double value = (1.0 / (2.0 * M_PI * pow(sigma, 2))) * exp(-(pow(x, 2) + pow(y, 2)) / (2.0 * pow(sigma, 2)));
	return value;
}

cv::Mat sobelFilter(cv::Mat image, sobelMode mode)
{
	Matx33d sobel_kernel;
	switch (mode)
	{
	case sobelMode::vertical:
		sobel_kernel << -1.0, 0.0, 1.0, -2.0, 0.0, 2.0, -1.0, 0.0, 1.0;
		break;
	case sobelMode::horizontal:
		sobel_kernel << -1.0, -2.0, -1.0, 0, 0, 0, 1.0, 2.0, 1.0;
		break;
	}
	cout << "sobel_kernel=\n" << sobel_kernel << endl;

	return filtering(sobel_kernel, image);
}

cv::Mat laplacianFilter(cv::Mat image)
{
	Matx33d laplacian_kernel;
	laplacian_kernel << 0.0, 1.0, 0.0, 1.0, -4.0, 1.0, 0.0, 1.0, 0.0;
	cout << "laplacian_kernel=\n" << laplacian_kernel << endl;

	return filtering(laplacian_kernel, image);
}

