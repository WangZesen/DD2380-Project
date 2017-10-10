#include "Environment.hpp"
#include "Route.hpp"

#include <ctime>
#include <random>

using namespace cv;
using namespace std;

struct Random {
    uniform_real_distribution<double> dist;
    mt19937 seed;
};

void filter(vector<Route> &survivals, Environment &env, int survivalNum, Random &generator) {
    double sum = 0, min = 0x7fffffff, max = -0x7fffffff;
    int num = survivals.size();
    
    if (num <= survivalNum)
        return;
    
    VectorPoint endPoint = env.endPoint();

    for (vector<Route>::iterator iter = survivals.begin(); iter != survivals.end(); iter++) {
        if ((*iter).adaptability(endPoint) > max)
            max = (*iter).adaptability(endPoint);
        if ((*iter).adaptability(endPoint) < min)
            min = (*iter).adaptability(endPoint);
    }

    vector<double> accAdapt;
    for (vector<Route>::iterator iter = survivals.begin(); iter != survivals.end(); iter++) {
        sum = sum + (max + min - (*iter).adaptability(endPoint));
        accAdapt.push_back(sum);
    }
    
    vector<Route> newRouteList;    
    
    for (int i = 0; i < survivalNum; i++) {
        double randomNumber = generator.dist(generator.seed);
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
	
	Random generator;
	generator.dist = uniform_real_distribution<double>(0.0, 1.0);
    generator.seed.seed(random_device{}());    
    
	// Algorithm starts here

    // Initial start routes

    Environment env(2);
    vector<Route> survivals;

    //Mat image(500, 500, 6);

    VectorPoint startPoint = env.startPoint();	
    
    const int gap = 3;
    const int survivalNum = 200;
    const int extendDist = 5;
    const double hybridPro = 0.2;
    
    
	for (int i = 0; i < 360; i += gap) {
        survivals.push_back(Route(startPoint, startPoint + startPoint.calAngle(i, extendDist)));
	}
	
	filter(survivals, env, survivalNum, generator);

    //for (int i = 0; i < survivalNum; i++) {
    //    survivals[i].drawRoute(image);
	//}
    // Start of Genetic Algorithm	
	for (int t = 0; t < 10000; t++) {
	    int size = survivals.size();
	    
	    //cerr << "[Debug] Before Mutation, Size = " << size << "\n";
	    
	    // Mutation
	    
	    for (int i = 0; i < size; i++) {
            vector<Route> mutations = survivals[i].extendMutation(env, extendDist);
            survivals.insert(survivals.end(), mutations.begin(), mutations.end());
            mutations = survivals[i].shortMutation(env, extendDist);
            survivals.insert(survivals.end(), mutations.begin(), mutations.end());
	    }
	    
	    //cerr << "[Debug] Before Hybrid\n";	    
	    
	    // Hybrid
	    /*
	    for (int i = 0; i < size; i++) {
	        for (int j = i + 1; j < size; j++) {
	            if (generator.dist(generator.seed) < hybridPro) {
	                vector<Route> hybrids = survivals[i].hybrid(survivals[j], env);
                    survivals.insert(survivals.end(), hybrids.begin(), hybrids.end());
                }
	        }
	    }
	    */
	    //cerr << "[Debug] Before Filter\n";	    
	    
	    // Filter
	    
	    filter(survivals, env, survivalNum, generator);
	    
	    // Show
	    
	    if (t % 100 == 0) {
	    
	        //cerr << "[Debug] Before Show\n";	        
	        
	        Mat image(500, 500, 6);
	        
	        for (int i = 0; i < 500; i++) {
	            for (int j = 0; j < 500; j++) {
	                image.at<double>(i, j) = 0;
	            }
	        }
	        
	        for (int i = 0; i < env.numObstacles + 2; i++) {
	            env.obstacles[i].drawObstacle(image);
	        }
	    
    	    
	    
    	    for (int i = 0; i < survivalNum; i++) {
    	        survivals[i].drawRoute(image);
    	    }
	    
       	   	imshow("map", image);
        	waitKey(0);
        }
	}
	
	

	

}
