#include "main.h"

using namespace cv;
using namespace std;

int main() {
	Mat image = imread("..\\..\\lenna.png");
	if (image.empty()) return -1;

	cout << "type: " << (
		image.type() == CV_8UC3 ? "CV_8UC3" :
		image.type() == CV_16SC1 ? "CV_16SC1" :
		image.type() == CV_64FC2 ? "CV_64FC2" :
		"other"
		) << endl;

	// —v‘f‚ÌŒ^
	cout << "depth: " << (
		image.depth() == CV_8U ? "CV_8U" :
		image.depth() == CV_16S ? "CV_16S" :
		image.depth() == CV_64F ? "CV_64F" :
		"other"
		) << endl;

	double zoom[3][3] = { {1.5, 0, 0}, {0, 1.5, 0}, {0, 0, 1} };
	Mat zoom_mat(3, 3, CV_64F, zoom);

	Mat zoom_lenna_bi = imageAffine(zoom_mat, image, ComplementMode::bilinier);
	Mat zoom_lenna_ne = imageAffine(zoom_mat, image, ComplementMode::nearest);
	
	imshow("Bilinier", zoom_lenna_bi);
	imshow("Nearest", zoom_lenna_ne);

	double deg = 30;
	double a = cos(deg * CV_PI / 180);
	double b = sin(deg * CV_PI/180);

	double A[3][3] = { {a, -b, 0}, {b, a, 0}, { 0, 0, 1} };
	double B[3][3] = { {1, 0, 300}, {0, 1, 100}, {0, 0, 1} };
	double C[3][3] = { {0.5, 0, 0}, {0, 0.5, 0}, {0, 0, 1} };
	Mat A_mat(3, 3, CV_64F, A);
	Mat B_mat(3, 3, CV_64F, B);
	Mat C_mat(3, 3, CV_64F, C);
	Mat Trans = B_mat * A_mat * C_mat;

	Mat image_affine = imageAffine(Trans, image, ComplementMode::bilinier);

	imshow("Translation", image_affine);

	waitKey();

	return 0;
}