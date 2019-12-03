#include "contourTracking.h"
using namespace cv;
using namespace std;

cv::Mat contourTracking(cv::Mat image)
{
	int rows = image.rows;
	int cols = image.cols;
	cout << rows << ", " << cols << endl;
	unsigned char pre_value = 255;
	unsigned char value = 255;
	copyMakeBorder(image, image, 1, 1, 1, 1, BORDER_CONSTANT, Scalar(255));
	Mat mapping = Mat(rows, cols, CV_8UC1);
	mapping = 255;

	int old_dir = 0, new_dir = 0;

	//raster scan
	for (int y = 0; y < rows; y++) {
		for (int x = 0; x < cols; x++) {
			value = image.at<unsigned char>(Point(x, y));

			if (x != 0 && pre_value == 255 && value == 0 ) {
				cout << "start : " << x << ", " << y << endl;
				//mapping.at<unsigned char>(Point(x, y)) = 0;
				int x_ = x, y_ = y;
				bool check = true;

				while (check) {
					Point search = Point(x_, y_);
					if (mapping.at<unsigned char>(search) == 0) {
						check = false;
					}
					switch (new_dir)
					{
					case 0:
						search = Point(x_ - 1, y - 1);
						if (image.at<unsigned char>(search) == 0 && mapping.at<unsigned char>(search) != 0) {
							mapping.at<unsigned char>(search) = 0;
							x_--; y_--;
							break;
						}
					case 1:
						search = Point(x_, y_ - 1);
						if (image.at<unsigned char>(search) == 0 && mapping.at<unsigned char>(search) != 0) {
							mapping.at<unsigned char>(search) = 0;
							y_--;
							break;
						}
					case 2:
						search = Point(x_ + 1, y_ - 1);
						if (image.at<unsigned char>(search) == 0 && mapping.at<unsigned char>(search) != 0) {
							mapping.at<unsigned char>(search) = 0;
							x_++; y_--;
							break;
						}
					case 3:
						search = Point(x_ + 1, y_);
						if (image.at<unsigned char>(search) == 0 && mapping.at<unsigned char>(search) != 0) {
							mapping.at<unsigned char>(search) = 0;
							x_++;
							break;
						}
					case 4:
						search = Point(x_ + 1, y_ + 1);
						if (image.at<unsigned char>(search) == 0 && mapping.at<unsigned char>(search) != 0) {
							mapping.at<unsigned char>(search) = 0;
							x_++; y_++;
							break;
						}
					case 5:
						search = Point(x_, y_ + 1);
						if (image.at<unsigned char>(search) == 0 && mapping.at<unsigned char>(search) != 0) {
							mapping.at<unsigned char>(search) = 0;
							y_++;
							break;
						}
					case 6:
						search = Point(x_ - 1, y_ + 1);
						if (image.at<unsigned char>(search) == 0 && mapping.at<unsigned char>(search) != 0) {
							mapping.at<unsigned char>(search) = 0;
							x_--; y_++;
							break;
						}
					case 7:
						search = Point(x_ - 1, y_);
						if (image.at<unsigned char>(search) == 0 && mapping.at<unsigned char>(search) != 0) {
							mapping.at<unsigned char>(search) = 0;
							x_--;
							break;
						}
					default:
						check = false;
					}
					old_dir = new_dir;
					new_dir = (old_dir + 6) % 8;
				};

				//clockwiseSearch(image, mapping, x, y, enterDirection::from_left);
			}

			pre_value = value;
		}
	}
	
	return mapping;
}




/*
pixelDirection clockwiseSearch(cv::Mat image, cv::Mat map, int x, int y, enterDirection mode)
{
	Direction begin; //�T���J�n����
	int x_ = x, y_ = y;

	//�N����������T�����������߂�
	switch (mode) 
	{
	case enterDirection::from_left:
		begin = Direction::top_left;
		break;
	case enterDirection::from_right:
		begin = Direction::bottom_right;
		break;
	case enterDirection::from_top:
		begin = Direction::top_right;
		break;
	case enterDirection::from_bottom:
		begin = Direction::bottom_left;
		break;
	}

	pixelDirection result = clockwise(image, x, y, begin);
	enterDirection next_mode;
	switch (result)
	{
	case pixelDirection::left:
		x_--;
		next_mode = enterDirection::from_bottom;
		break;
	case pixelDirection::top_left:
		x_--;
		y_++;
		next_mode = enterDirection::from_bottom;
		break;
	case pixelDirection::top:
		y_++;
		next_mode = enterDirection::from_left;
		break;
	case pixelDirection::top_right:
		x_++;
		y_++;
		next_mode = enterDirection::from_left;
		break;
	case pixelDirection::right:
		x_++;
		next_mode = enterDirection::from_top;
		break;
	case pixelDirection::bottom_right:
		x_++;
		y_--;
		next_mode = enterDirection::from_top;
		break;
	case pixelDirection::bottom:
		y_--;
		next_mode = enterDirection::from_right;
		break;
	case pixelDirection::bottom_left:
		x_++;
		y_--;
		next_mode = enterDirection::from_right;
		break;
	case pixelDirection::none:
		map.at<unsigned char>(Point(x_, y_)) = 255;
		return pixelDirection();
	}

	if (map.at<unsigned char>(Point(x_, y_)) == 0)
		return pixelDirection();
	map.at<unsigned char>(Point(x_, y_)) = 0;
	clockwiseSearch(image, map, x_, y_, next_mode);

	return pixelDirection();
}



pixelDirection clockwise(Mat image, int x, int y, Direction begin) {
	int m = 0, n = 0;

	switch (begin)
	{
	case Direction::left:
		m = -1;
		n = 0;
		if (image.at<unsigned char>(Point(x + m, y + n)) == 0)
			return pixelDirection::left;
	case Direction::top_left:
		m = -1;
		n = 1;
		if (image.at<unsigned char>(Point(x + m, y + n)) == 0)
			return pixelDirection::top_left;
	case Direction::top:
		m = 0;
		n = 1;
		if (image.at<unsigned char>(Point(x + m, y + n)) == 0)
			return pixelDirection::top;
	case Direction::top_right:
		m = 1;
		n = 1;
		if (image.at<unsigned char>(Point(x + m, y + n)) == 0)
			return pixelDirection::top_right;
	case Direction::right:
		m = 1;
		n = 0;
		if (image.at<unsigned char>(Point(x + m, y + n)) == 0)
			return pixelDirection::right;
	case Direction::bottom_right:
		m = 1;
		n = -1;
		if (image.at<unsigned char>(Point(x + m, y + n)) == 0)
			return pixelDirection::bottom_right;
	case Direction::bottom:
		m = 0;
		n = -1;
		if (image.at<unsigned char>(Point(x + m, y + n)) == 0)
			return pixelDirection::bottom;
	case Direction::bottom_left:
		m = -1;
		n = -1;
		if (image.at<unsigned char>(Point(x + m, y + n)) == 0)
			return pixelDirection::bottom_left;
	default:
	return pixelDirection::none;
	}
}
*/