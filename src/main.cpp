#include <iostream> 
#include <fstream>
#include <cmath>
#include <opencv2/opencv.hpp>

cv::Mat readimage(const std::string &filename) {
	return cv::imread(filename, CV_LOAD_IMAGE_COLOR);
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
	auto myint = (int)mychar;
	return myint;
}

void capturewebcam() {
	std::string command = "imagesnap -w 0 snapshot.jpg";
	system(command.c_str());
}

float analyze() {
	capturewebcam();
	cv::Mat img = readimage("snapshot.jpg");
	int radius = img.cols * 0.05;
	radius += radius % 2 == 0; // radius must be odd because cv::Size(x, y), x and y must be odd
	cv::Mat orig, gray;
	img.copyTo(orig);

	// Get the brightest area
	cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
	cv::GaussianBlur(gray, gray, cv::Size(radius, radius), 0);

	cv::Point maxLoc;
	cv::minMaxLoc(gray, nullptr, nullptr, nullptr, &maxLoc);

	// calc the average color of that area
	//std::cout << maxLoc.x - (radius/2) << " " << maxLoc.y - (radius/2) << " " << radius << "\n";
	img = orig(cv::Rect(maxLoc.x - (radius/2), maxLoc.y - (radius/2), radius, radius));
	cv::Mat outImg;
	cv::resize(img, outImg, cv::Size(1, 1));
	return (float)getint(&outImg, 0, 0) / 255;

}

float calc() {
	cv::Mat inImg = readimage("screenshot.jpg");
	cv::Mat outImg;;

	// calc average color
	cv::resize(inImg, outImg, cv::Size(1, 1));
	return (float)getint(&outImg, 0, 0) / 1200;
}

void getscreenres(int &width, int &height) {
	std::string command = "screencapture -t jpg -x screenshot.jpg";
	system(command.c_str());
	cv::Mat img = readimage("screenshot.jpg");
	width = img.cols;
	height = img.rows;
}

int main() {
	int MAX_BLUE = 10000;
	int cur_blue;
	float tolerance = analyze();
	int width, height = 0;
	getscreenres(width, height);
	while (true) {
		screenshot(width * 0.2, height * 0.2, width * 0.6, height * 0.6);
		cur_blue = (int)sqrt(MAX_BLUE * (calc()/tolerance));
		std::cout << "cur_blue: " << cur_blue << "\n";
		std::string command = "./nshift " + std::to_string(cur_blue);
		system(command.c_str());
	}
	return 0;
}
