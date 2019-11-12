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

tuple<double, double> pixelAffine2(Mat A, int x, int y)
{
	Mat affine_pixel = (Mat_<double>(3, 1) << x, y, 1);
	Mat ori_pixel = (Mat_<double>::zeros(3, 1));

	ori_pixel = A * affine_pixel;

	return forward_as_tuple(ori_pixel.at<double>(0, 0), ori_pixel.at<double>(1, 0));
}

Mat imageAffine(Matx33d A, Mat image, ComplementMode mode) {
	
	Mat A_mat = Mat(A);

	tuple<double, double> tl = pixelAffine2(A_mat, 0, 0);
	tuple<double, double> tr = pixelAffine2(A_mat, image.cols, 0);
	tuple<double, double> bl = pixelAffine2(A_mat, 0, image.cols);
	tuple<double, double> br = pixelAffine2(A_mat, image.cols, image.rows);

	int cols = max(max(get<0>(tl), get<0>(tr)), max(get<0>(bl), get<0>(br)));
	int rows = max(max(get<1>(tl), get<1>(tr)), max(get<1>(bl), get<1>(br)));
	Mat affined(rows, cols, CV_8UC3);
	cout << affined.size << endl;

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
			switch (mode) 
			{
				case ComplementMode::bilinier	:
					affined.at<cv::Vec3b>(j, i) = bilinier(image, x, y);
				case ComplementMode::nearest	:
					affined.at<cv::Vec3b>(j, i) = nearest(image, x, y);
			}
			
		}
	}


	return affined;
}