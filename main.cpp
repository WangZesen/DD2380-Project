#include "Environment.hpp"
#include "Route.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <math.h>
#include <string>
using namespace cv;
using namespace std;
int main() {
	/*Environment test;
	//cout << test.at(10, 10);
	test.mapInfo();
	
	VectorPoint x(357, 70);
	VectorPoint y(100, 234);
	
	vector<VectorPoint> result = test.nextPropagation(y, x, 1);
	for (int i = 0; i < result.size(); i++) {
		std::cerr << "[Debug] Point " << i << ": x = " << result[i].x << ", y = " << result[i].y << std::endl;
	}
	
	double t = test.potential(y);
	std::cerr << "[Debug] Potential " << t << std::endl;
	
	//string a = "123";
	//Mat image = imread(a.c_str(), CV_LOAD_IMAGE_COLOR);
	Mat image1(500, 500, 6);
	
	//cout << image1.at<double>(0,0) << endl;
	
	//line(image1, Point(10, 100), Point(50, 200), Scalar(255, 0, 0));
	
	
	vector<Route> routeList;
	
    //routeList[0].drawRoute(image1);
	
	for (int i = 0; i < test.numObstacles + 2; i++)
    	test.obstacles[i].drawObstacle(image1);
	
	imshow("image", image1);
	waitKey(0);	*/
	
    
    
	// Algorithm starts here

    // Initial start 

    Environment env;
    vector<Route> survivals;

    Mat image(500, 500, 6);

    VectorPoint startPoint = env.startPoint();	
	for (int i = 0; i < 360; i++) {
	   survivals.push_back(Route(startPoint, startPoint + startPoint.calAngle(i, 10)));
	   survivals[i].drawRoute(image);
	}
	
	imshow("map", image);
	waitKey(0);
	

}
