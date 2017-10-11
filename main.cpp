#include "Environment.hpp"
#include "Route.hpp"

using namespace cv;
using namespace std;

// Output Information for Visualization 

void output(vector<Route> &survivals, Environment &env, int successIndex) {

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

    if (successIndex != -1) {
        max += 100;
    }

    vector<double> adapt;
    for (vector<Route>::iterator iter = survivals.begin(); iter != survivals.end(); iter++) {
        cout << "line\n";
        
        if (iter - survivals.begin() != successIndex) {
            cout << int(((*iter).adaptability(endPoint) - min) * 255 / (max - min)) << endl;
        } else {
            cout << int(((*iter).adaptability(endPoint) + 100 - min) * 255 / (max - min)) << endl;
        }
        
        for (int i = 0; i < (*iter).set.size(); i++) {
            cout << int((*iter).set[i].x) << " " << int((*iter).set[i].y) << endl; 
        }
        cout << "endline\n";
    }
}

// Use Roulette Wheel Selection to Filter All Survivals

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

    clock_t lastTime;
    double timeCount = 0;
    
	Random generator;
	generator.dist = uniform_real_distribution<double>(0.0, 1.0);
    generator.seed.seed(random_device{}());    
    
	

    // Initial routes and maps

    bool used[505][505];
    for (int i = 0; i < 505; i++) {
        for (int j = 0; j < 505; j++) {
            used[i][j] = false;
        }
    }
    
    Environment env(mapNum);
    vector<Route> survivals;


    // Output Obstacles' information (for visualization)
    
    for (int i = 0; i < env.numObstacles + 2; i++) {
        cout << "obstacle\n";
        cout << env.obstacles[i].x << " " << env.obstacles[i].y << " ";
        cout << env.obstacles[i].kind << " " << env.obstacles[i].r << " ";
        cout << env.obstacles[i].a << " " << env.obstacles[i].b << "\n";        
    }

    VectorPoint startPoint = env.startPoint();	
    

    
    
	for (int i = 0; i < 360; i += angleGap) {
	    VectorPoint nextPoint = startPoint + startPoint.calAngle(i, extendDist);
        survivals.push_back(Route(startPoint, nextPoint));
        used[int(nextPoint.x)][int(nextPoint.y)] = true;
	}
	
	filter(survivals, env, survivalNum, generator);

    // Start of Genetic Algorithm	
    
	for (int t = 0; t < 10000; t++) {

	    int size = survivals.size();
	    
	    // Mutation
	    
	    for (int i = 0; i < size; i++) {
	        // Extending Mutation Method
            vector<Route> mutations = survivals[i].extendMutation(env, extendDist, generator);
            survivals.insert(survivals.end(), mutations.begin(), mutations.end());
            // Shortening Mutation Method
            mutations = survivals[i].shortMutation(env, extendDist);
            survivals.insert(survivals.end(), mutations.begin(), mutations.end());
	    }
	    
	    for (int i = 0; i < survivals.size(); i++) {
	        VectorPoint lastPoint = *(survivals[i].set.end() - 1);
	        used[int(lastPoint.x)][int(lastPoint.y)] = true;
	    }
	    
	    // Hybrid
	    
	    for (int i = 0; i < size; i++) {
	        for (int j = i + 1; j < size; j++) {
	            if (generator.dist(generator.seed) < hybridPro) {
	                vector<Route> hybrids = survivals[i].hybrid(survivals[j], env);
                    survivals.insert(survivals.end(), hybrids.begin(), hybrids.end());
                }
	        }
	    }
	    
	    // Filter
	    
	    filter(survivals, env, survivalNum, generator);
	    
	    // Check Whether survivals reach end area
	    
	    for (int i = 0; i < survivals.size(); i++) {
	        if (env.obstacles[env.numObstacles + 1].isIn(*(survivals[i].set.end() - 1))) {
	            output(survivals, env, i);
	            cout << "exit\n";
	            
	            cerr << "End with " << t << " generations\n";
	            cerr << "Total Time: " << (timeCount + clock() - lastTime) / CLOCKS_PER_SEC << endl;
	            
	            
	            int count = 0;
	            for (int xi = 0; xi < 500; xi++) {
	                for (int xj = 0; xj < 500; xj++) {
	                    if (used[xi][xj])
	                        count++;
	                }
	            }
	            cerr << "# of Points Reached: " << count << " out of 250000 (" << count / 250000.0 << "%)\n";
	            cerr << "Route Length: " << survivals[i].length() << endl;
	            
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
	                
	            return 0;
	        }
	    }
	    
	    // Visualization
	    
	    if ((t % 50 == 0) && (stepVisual)) {
	    
	        timeCount += clock() - lastTime;
	    
	        cerr << "# of Generation: " << t << ", Time Consumed: " << timeCount / CLOCKS_PER_SEC << endl;
	        
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
        	
        	output(survivals, env, -1);
        	
        	lastTime = clock();
        }
        
	}
}
