#include "main.h"

using namespace std;

int main() {
	cv::Mat image = cv::imread("..\\image\\DSC_0438.JPG", 0);
	cout << "image ok" << endl;
	cv::Mat background = cv::imread("..\\image\\background.jpg");
	cout << "background ok" << endl;
	cv::Mat object = cv::imread("..\\image\\object.jpg");
	cout << "object ok" << endl;

	if (image.cols > 1000) {
		cv::resize(image, image, cv::Size(), 0.1, 0.1);
		cv::resize(background, background, cv::Size(), 0.1, 0.1);
		cv::resize(object, object, cv::Size(), 0.1, 0.1);
	}

	cv::Mat mono_image = binarization(image);
	cv::Mat detection = objectDetection(background, object);

	//cv::imwrite("binary senpai.png", mono_image);
	//cv::imwrite("object detection.png", detection);
	cv::imshow("binary senpai", mono_image);
	cv::imshow("object detection", detection);

	cv::waitKey();

	return 0;
}