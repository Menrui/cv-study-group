#include "binarization.h"

using namespace cv;
using namespace std;

double distribution(cv::Mat image, unsigned char t)
{
	if (image.type() == CV_8UC3) {
		cout << "please CV_8UC1" << endl;
		return -1;
	}
	int rows = image.rows;
	int cols = image.cols;
	int cntBlack = 0;
	int cntWhite = 0;
	int aveBlack = 0;
	int aveWhite = 0;
	unsigned char value = 0;

	for (int j = 0; j < rows; j++) {
		for (int i = 0; i < cols; i++) {
			value = image.at<unsigned char>(j, i);
			if (t < value) {
				cntBlack++;
				aveBlack += value;
			}
			else {
				cntWhite++;
				aveWhite += value;
			}
		}
	}

	aveBlack /= cntBlack;
	aveWhite /= cntWhite;

	double interclass_variance = (cntBlack * pow((aveBlack - aveWhite), 2) + cntWhite * pow(aveWhite - aveBlack, 2)) / (cntBlack + cntWhite);

	return interclass_variance;
}

cv::Mat binarization(cv::Mat image)
{
	return cv::Mat();
}
