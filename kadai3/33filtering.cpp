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
//					if (x + m < 0 && y + n < 0) {
//						center_value += image.at<Vec3b>(Point(0, 0)) * kernel_.at<double>(Point(m + 1, n + 1));
//					}
//					else if (x + m < 0) {
//						center_value += image.at<Vec3b>(Point(0, y + n)) * kernel_.at<double>(Point(m+1, n+1));
//					}
//					else if (y + n < 0) {
//						center_value += image.at<Vec3b>(Point(x + m, 0)) * kernel_.at<double>(Point(m+1, n+1));
//					}
					if (x + m < 0 || y + n < 0 || x + m >= cols || y + n >= rows) {
						center_value += Vec3b::ones()*128 * kernel_.at<double>(Point(m+1, n+1));
					}
					else {
						center_value += image.at<Vec3b>(Point(x + m, y + n)) * kernel_.at<double>(Point(m+1, n+1));
					}
					
				}
			}
//			cout << kernel(1, 1) << endl;
//			cout << image.at<Vec3b>(Point(x, y)) * kernel(1, 1) << endl;
//			cout << center_value << endl;
//			cout << image.at<Vec3b>(Point(x, y)) << endl;
			image_.at<Vec3b>(Point(x, y)) = center_value;
		}
	}
	return image_;
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
	cout << gaussian_kernel << endl;
	Mat image_ = filtering(gaussian_kernel, image);

	return image_;
}

double gaussianFunction(double sigma, int x, int y) {
	double value = (1.0 / (2.0 * M_PI * pow(sigma, 2))) * exp(-(pow(x, 2) + pow(y, 2)) / (2.0 * pow(sigma, 2)));
	return value;
}

