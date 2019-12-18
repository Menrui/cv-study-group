#include "rabeling.h"
using namespace cv;
using namespace std;

cv::Mat rabeling(cv::Mat image)
{
	copyMakeBorder(image, image, 1, 1, 1, 1, BORDER_CONSTANT, Scalar(255));
	int rows = image.rows;
	int cols = image.cols;
	std::cout << rows << ", " << cols << endl;
	Mat mapping = Mat(rows, cols, CV_32SC1);
	mapping = 0;

	Mat rabeling = Mat(rows, cols, CV_8UC3);

	Point around[4] = { Point(-1, 0), //left
						Point(-1, -1), //topleft
						Point(0, -1), //top
						Point(1, 0) }; //topright
	int newest_rabel = 1;
	vector<vector<int>> table(1);
	vector<int> topleft_top{0, 0};
	vector<int> left_top_topright{0, 0, 0};
	vector<int> left_topleft_top{0, 0, 0};

	unsigned char pre_value = 255;
	unsigned char value = 255;

	for (int y = 0; y < rows; y++) {
		for (int x = 0; x < cols; x++) {
			value = image.at<unsigned char>(Point(x, y));

			if (x != 0 && value == 0) {

				Point search = Point(x, y);
				Point search_tmp = search + around[0];

				//if (mapping.at<unsigned char>(search) == 0) continue;
				topleft_top[0] = mapping.at<int>(search + around[1]);
				topleft_top[1] = mapping.at<int>(search + around[2]);
				if (*max_element(topleft_top.begin(), topleft_top.end()) != 0) {
					if (topleft_top[0] == 0) mapping.at<int>(search) = topleft_top[1];
					else if (topleft_top[1] == 0) mapping.at<int>(search) = topleft_top[0];
					else mapping.at<int>(search) = *min_element(topleft_top.begin(), topleft_top.end());
				}

				left_top_topright[0] = mapping.at<int>(search + around[0]);
				left_top_topright[1] = topleft_top[1];
				left_top_topright[2] = mapping.at<int>(search + around[3]);
				if (*max_element(left_top_topright.begin(), left_top_topright.end()) != 0) {
					for (int i = 0; i < 3; i++) {
						if (left_top_topright[i] != 0 && left_top_topright[i] != mapping.at<int>(search)) {
							
							table[std::min(mapping.at<int>(search), left_top_topright[i])]
								.push_back(std::max(mapping.at<int>(search), left_top_topright[i]));
						}
					}
				}

				left_topleft_top[0] = left_top_topright[0];
				left_topleft_top[1] = topleft_top[0];
				left_topleft_top[2] = topleft_top[1];
				if (left_topleft_top[0] != 0 && left_topleft_top[1] == 0 && left_topleft_top[2] == 0) {
					mapping.at<int>(search) = left_topleft_top[0];
				}
				else if (left_topleft_top[0] == 0 && left_topleft_top[1] == 0 && left_topleft_top[2] == 0) {
					mapping.at<int>(search) = newest_rabel++;
					table.push_back({});
				}
				
			}
		}
	}
	cout << table.size() << endl;

	int table_size = table.size();
	int table_i_size = table[0].size();
	for (int i = 0; i < table.size(); i++) {
		for (int j = 0; j < table[i].size(); j++) {
			//cout << table[i][j] << "," << table[table[i][j]].size() << endl;
			if (table[table[i][j]].size() > 0) {
				table[i].insert(table[i].begin(), table[table[i][j]].begin(), table[table[i][j]].end());
			}
			table_i_size = table[i].size();
		}
		table_size = table.size();
	}
	cout << table.size() << endl;

	for (int y = 0; y < rows; y++) {
		for (int x = 0; x < cols; x++) {
			if (mapping.at<int>(Point(x, y)) != 0) {

			}
		}
	}

	return mapping;
}
