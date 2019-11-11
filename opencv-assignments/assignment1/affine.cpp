#include "affine.h"
using namespace std;
using namespace cv;

tuple<double, double> pixelAffine(Mat A, int x, int y)
{
	Mat affine_pixel = (Mat_<double>(3, 1) << x, y, 1);
	Mat ori_pixel = (Mat_<double>::zeros(3, 1));

	ori_pixel = A.inv() * affine_pixel;

	return forward_as_tuple(ori_pixel.at<double>(0, 0), ori_pixel.at<double>(1, 0));
}

Mat imageAffine(double A[3][3], Mat image, string mode) {
	
	Mat A_mat = Mat_<double>::zeros(3, 3);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			A_mat.at<double>(i, j) = A[i][j];
		}
	}

	Mat affined = image.clone();
	int cols = affined.cols;
	int rows = affined.rows;
	for (int j = 0; j < rows; j++) {
		for (int i = 0; i < cols; i++) {
			affined.at<cv::Vec3b>(j, i)[0] = 0; //ê¬
			affined.at<cv::Vec3b>(j, i)[1] = 0; //óŒ
			affined.at<cv::Vec3b>(j, i)[2] = 0; //ê‘
		}
	}

	for (int j = 0; j < rows; j++) {
		for (int i = 0; i < cols; i++) {
			tuple<double, double> pixel = pixelAffine(A_mat, i, j);
			double x = get<0>(pixel);
			double y = get<1>(pixel);
			//if(x<=cols && y<=rows){
				affined.at<cv::Vec3b>(j, i) = bilinier(image, x, y);
			//}
			//else {
			//	affined.at<cv::Vec3b>(j, i) = 255; 
			//}
		}
	}


	return affined;
}