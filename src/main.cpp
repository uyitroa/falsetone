#include <iostream> 
#include <fstream>
#include <math.h>
#include <opencv2/opencv.hpp>

#include "wrapper/MyCPPWrapper.h"

cv::Mat readimage() {
	return cv::imread("screenshot.jpg", CV_LOAD_IMAGE_COLOR);
}

void screenshot() {
	std::string command = "screencapture -t jpg -x screenshot.jpg";
	system(command.c_str());
}

int getint(cv::Mat *img, int col, int row) {
	cv::Vec3b intensity = img->at<cv::Vec3b>(col, row);
	uchar mychar = intensity.val[0];
	int myint = (int)mychar;
	return myint;
}

float calc() {
	screenshot();
	cv::Mat img = readimage();
	int center_col = (int)img.cols / 2;
	int center_row = (int)img.rows / 2;
	uint sum_color = 0;
	uint max_color = 0;

	uint point_col = 0;
	uint point_row = 0;
	uint color = 0;

	int col_begin = img.cols * 0.2;
	int col_end = img.cols * 0.8;
	int row_begin = img.rows * 0.2;
	int row_end = img.rows * 0.8;
	for (int i = col_begin; i < col_end; i++) {
		for (int j = row_begin; j < row_end; j++) {
			coefficient_col = center_col - abs(center_col - i);
			coefficient_row = center_row - abs(center_row - j);
			color = getint(&img, j, i);
			sum_color += (color * (coefficient_col + coefficient_row)) / 10000;
			max_color += (200 * (coefficient_col + coefficient_row)) / 1000;
		}
		//std::cout << sum_color << "\n";
	}
	//std::cout << sum_color << " " << max_color << "\n";
	//std::cout << (float)sum_color / max_color << "\n";
	return (float)sum_color / max_color;
}

int main() {
	int MAX_BLUE = 10000;
	int cur_blue = 10000;
	MyCPPWrapper c;
	c.init();
	while (true) {
		cur_blue = (int)sqrt(MAX_BLUE * calc());
		std::cout << "cur_blue: " << cur_blue << "\n";
		std::string command = "./nshift " + std::to_string(cur_blue);
		system(command.c_str());
	}
	return 0;
}
