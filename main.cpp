#include "Environment.hpp"
#include "Route.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <math.h>
#include <string>
#include <ctime>
#include <random>

using namespace cv;
using namespace std;
void filter(vector<Route> &survivals, Environment &env, int survivalNum) {
    double sum = 0;
    int num = survivals.size();
    
    if (num <= survivalNum)
        return;
    
    VectorPoint endPoint = env.endPoint();
    

    vector<double> accAdapt;
    for (vector<Route>::iterator iter = survivals.begin(); iter != survivals.end(); iter++) {
        sum = sum + (*iter).adaptability(endPoint);
        accAdapt.push_back(sum);
    }
    
    uniform_real_distribution<double> dist(0.0, 1.0);
    mt19937 seed;
    seed.seed(random_device{}());
    
    vector<Route> newRouteList;    
            
    for (int i = 0; i < survivalNum; i++) {
        double randomNumber = dist(seed);
        int j;
        for (j = 0; j < num; j++) {
            if (randomNumber < accAdapt[j] / sum) 
                break;
        }
        newRouteList.push_back(survivals[j]);
    }
    
    survivals = newRouteList;
    
}

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

    // Initial start routes

    Environment env;
    vector<Route> survivals;

    Mat image(500, 500, 6);

    VectorPoint startPoint = env.startPoint();	
    
    const int gap = 3;
    const int survivalNum = 50;
    
	for (int i = 0; i < 360; i += gap) {
        survivals.push_back(Route(startPoint, startPoint + startPoint.calAngle(i, 10)));
        //survivals[i / gap].drawRoute(image);
	}
	
	filter(survivals, env, survivalNum);
	
	/*for (int i = 0; i < survivals.size(); i++) {
        survivals[i].drawRoute(image);
        //survivals[i / gap].drawRoute(image);
	}*/
	
	for (int t = 0; t < 100; t++) {
	    
	}
	
	
	imshow("map", image);
	waitKey(0);
	

}
