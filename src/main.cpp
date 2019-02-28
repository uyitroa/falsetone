#include <iostream> 
#include <fstream>
#include <math.h>
#include <opencv2/opencv.hpp>

cv::Mat readimage() {
	return cv::imread("screenshot.jpg", CV_LOAD_IMAGE_COLOR);
}

void screenshot(int x, int y, int w, int h) {
	std::string command = "screencapture -t jpg -x screenshot.jpg -R ";
	command += std::to_string(x); 
	command += ","; 
	command += std::to_string(y);
	command += ",";
	command += std::to_string(w);
	command += ",";
	command += std::to_string(h);
	system(command.c_str());
}

int getint(cv::Mat *img, int col, int row) {
	cv::Vec3b intensity = img->at<cv::Vec3b>(col, row);
	uchar mychar = intensity.val[0];
	int myint = (int)mychar;
	return myint;
}

float calc() {
	cv::Mat inImg = readimage();
	cv::Mat outImg;
	cv::Size size(1, 1);

	cv::resize(inImg, outImg, size);
	return (float)getint(&outImg, 0, 0) / 1200;
}

void getscreenres(int &width, int &height) {
	std::string command = "screencapture -t jpg -x screenshot.jpg";
	system(command.c_str());
	cv::Mat img = readimage();
	width = img.cols;
	height = img.rows;
}

int main() {
	int MAX_BLUE = 10000;
	int cur_blue = 10000;

	int width, height = 0;
	getscreenres(width, height);
	while (true) {
		screenshot(width * 0.2, height * 0.2, width * 0.6, height * 0.6);
		cur_blue = (int)sqrt(MAX_BLUE * calc());
		std::cout << "cur_blue: " << cur_blue << "\n";
		std::string command = "./nshift " + std::to_string(cur_blue);
		system(command.c_str());
	}
	return 0;
}
