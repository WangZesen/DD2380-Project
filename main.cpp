#include "Environment.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <math.h>
#include <string>
using namespace cv;
using namespace std;
int main() {
	Environment test;
	//cout << test.at(10, 10);
	test.mapInfo();
	
	VectorPoint x(10, 0);
	VectorPoint y(100, 234);
	
	vector<VectorPoint> result = test.nextPropagation(y, x, 1);
	for (int i = 0; i < result.size(); i++) {
		std::cerr << "[Debug] Point " << i << ": x = " << result[i].x << ", y = " << result[i].y << std::endl;
	}
	
	double t = test.potential(y);
	std::cerr << "[Debug] Potential " << t << std::endl;
	
	string a = "123";
	Mat image = imread(a.c_str(), CV_LOAD_IMAGE_COLOR);
}
