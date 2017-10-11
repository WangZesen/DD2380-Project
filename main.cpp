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

void output(vector<Route> &survivals, Environment &env) {

    cout << "clear\n";

    double sum = 0, min = 0x7fffffff, max = -0x7fffffff;
    int num = survivals.size();
    
    VectorPoint endPoint = env.endPoint();

    for (vector<Route>::iterator iter = survivals.begin(); iter != survivals.end(); iter++) {
        if ((*iter).adaptability(endPoint) > max)
            max = (*iter).adaptability(endPoint);
        if ((*iter).adaptability(endPoint) < min)
            min = (*iter).adaptability(endPoint);
    }

    vector<double> adapt;
    for (vector<Route>::iterator iter = survivals.begin(); iter != survivals.end(); iter++) {
        cout << "line\n";
        cout << int(((*iter).adaptability(endPoint) - min) * 255 / (max - min)) << endl;
        for (int i = 0; i < (*iter).set.size(); i++) {
            cout << int((*iter).set[i].x) << " " << int((*iter).set[i].y) << endl; 
        }
        cout << "endline\n";
    }
}

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

	Random generator;
	generator.dist = uniform_real_distribution<double>(0.0, 1.0);
    generator.seed.seed(random_device{}());    
    
	// Algorithm starts here

    // Initial start routes

    Environment env(1);
    vector<Route> survivals;


    // Output Obstacles' information (for visualization)
    
    for (int i = 0; i < env.numObstacles + 2; i++) {
        cout << "obstacle\n";
        cout << env.obstacles[i].x << " " << env.obstacles[i].y << " ";
        cout << env.obstacles[i].kind << " " << env.obstacles[i].r << " ";
        cout << env.obstacles[i].a << " " << env.obstacles[i].b << "\n";        
    }

    //Mat image(500, 500, 6);

    VectorPoint startPoint = env.startPoint();	
    
    const int gap = 3;
    const int survivalNum = 100;
    const int extendDist = 6;
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
	    
	    for (int i = 0; i < size; i++) {
	        for (int j = i + 1; j < size; j++) {
	            if (generator.dist(generator.seed) < hybridPro) {
	                vector<Route> hybrids = survivals[i].hybrid(survivals[j], env);
                    survivals.insert(survivals.end(), hybrids.begin(), hybrids.end());
                }
	        }
	    }
	    
	    //cerr << "[Debug] Before Filter\n";	    
	    
	    // Filter
	    
	    filter(survivals, env, survivalNum, generator);
	    
	    // Check Terminal State
	    
	    for (int i = 0; i < survivals.size(); i++) {
	        if (env.obstacles[env.numObstacles + 1].isIn(*(survivals[i].set.end() - 1))) {
	            output(survivals, env);
	            cout << "exit\n";
	            return 0;
	        }
	    }
	    
	    // Show
	    
	    if (t % 50 == 0) {
	    
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
        	
        	output(survivals, env);
        }
	}
	
	

	

}
