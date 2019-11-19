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
	int cntBlack = 1;
	int cntWhite = 1;
	float aveBlack = 0;
	float aveWhite = 0;
	double aveValue = 0;
	unsigned char value = 0;

	for (int j = 0; j < rows; j++) {
		for (int i = 0; i < cols; i++) {
			value = image.at<unsigned char>(j, i);
			aveValue += value;
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
	aveValue /= rows * cols;

	double interclass_variance = (cntBlack * pow((aveBlack - aveValue), 2) + cntWhite * pow(aveWhite - aveValue, 2)) / (cntBlack + cntWhite);

	return interclass_variance;
}


cv::Mat binarization(cv::Mat image)
{
	if (image.type() == CV_8UC3) {
		cout << "please CV_8UC1" << endl;
	}

	int rows = image.rows;
	int cols = image.cols;
	unsigned char threshold = 0;
	double prevar = 0;
	
	for (int i = 0; i < 255; i++) {
		double var = distribution(image, i);
		if (prevar < var) {
			prevar = var;
			threshold = i;
		}
	}

	cout << "‚µ‚«‚¢’l‚Í" <<(short)threshold << endl;

	unsigned char value = 0;
	cv::Mat mono_image = image.clone();

	for (int j = 0; j < rows; j++) {
		for (int i = 0; i < cols; i++) {
			value = image.at<unsigned char>(j, i);
			if (value <= threshold) {
				mono_image.at<unsigned char>(j, i) = 0;
			}
			else {
				mono_image.at<unsigned char>(j, i) = 255;
			}
		}
	}


	return mono_image;
}
