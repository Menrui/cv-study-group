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

	double A[3][3] = { {1, 0, 100}, {0, 1, 50}, { 0, 0, 1} };

	image = imageAffine(A, image, ComplementMode::bilinier);

	imshow("imshow test", image);
	waitKey();

	return 0;
}