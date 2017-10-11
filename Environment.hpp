#ifndef __ENVIRONMENT_HPP__
#define __ENVIRONMENT_HPP__

#include <iostream>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <ctime>
#include <random>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "Parameter.hpp"

#define PI 3.14159265359

using namespace cv;
using namespace std;

struct Random {
    uniform_real_distribution<double> dist;
    mt19937 seed;
};

class VectorPoint {
		
	public: 
		//	      90
		//         |
		//         |
		// 180------------0(360)
		//         |
		//         |
		//        270 
		
		double x, y;
				
		// Return the length of the vector
		double length() const;
		
        // Constructor
		VectorPoint(double initX, double initY);
		VectorPoint();		
		
		// Substraction of two point gives a vector
		VectorPoint operator-(const VectorPoint &c) const;
		
		// Addition of two vectors gives the combination of them
		VectorPoint operator+(const VectorPoint &c) const;

		// Dot product of two vectors
		double operator*(const VectorPoint &c) const;
		
		// Product of a vector and scalar
		VectorPoint operator*(int scalar) const;
		
		// Get a unit vecotr
		VectorPoint operator/(int len) const;
		
		// Cosin value of the angle between two vectors
		double cosin(const VectorPoint &c);
		
		// Gives a vector with angle and dist
		VectorPoint calAngle(double angle, double dist) const;
		
        // Cerr the information of a vector (Debug)
		void info();		
};

class Obstacle {
	public:
		int x, y, kind, r, a, b;

	public:
		// For Kind
		// 0 = rectangle
		//           b
		//    _____________
		//    |            |
		// a  |            | 
		//    |            |
		//    |____________|
		//
		// 1 = circle

        // Constructor with some attributes
		Obstacle();
		Obstacle(int X, int Y, int Kind, int R, int A, int B);

        // Set the values of attributes
		void set(int X, int Y, int Kind, int R, int A, int B);

        // Return true if point (testX, testY) is in this obstacle
		bool isIn(int testX, int testY);
		// Return true if point indicated by VectorPoint is in this obstacle
		bool isIn(VectorPoint &v);
		
		// Return the position of this obstacle as a VectorPoint
		VectorPoint vectorForm();
		
		// Visualization
		void drawObstacle(Mat &image);
};

class Environment {
	public:
		// Initial a random map
		Environment();
		
		// Initial a preset map
		Environment(int mapset);


		// Return the circustance on point (x, y)
		// 0 = start area
		// 1 = goal area
		// 2 = obstacle
		// 3 = empty
		int at(double x, double y);
		int at(int x, int y);
		int at(VectorPoint c);

		// Return possible successor
		// Param x, y: present a vector from y to x
		// Param dist: propagation distance
		std::vector<VectorPoint> nextPropagation(const VectorPoint& x, const VectorPoint& y, int dist);

        // Calculate the closest point from a obstacle (#index)
		VectorPoint closestPoint(const VectorPoint &c, int index);
		
		// Calculate the distance between a point (c) and a obstacle (#index)
		double calDist(const VectorPoint &c, int index);
		
		// Calculate the potential at certain point
		double potential(const VectorPoint& c);
		
		// Return true if no obstacles between point x and point y
        bool blocked(const VectorPoint& x, const VectorPoint& y);

        // Return start point as a VectorPoint
        VectorPoint startPoint();
        
        // Return end point as a VectorPoint
		VectorPoint endPoint();
		
		// Return map in string (Debug)
		std::string mapToString();
		
		// Return map information (Debug)
		void mapInfo();
		
		const int numObstacles = obstacleNum;
		std::vector<Obstacle> obstacles;						
		
	private:
		const int width = 500;
		const int height = 500;

		int Map[600][600];		
		
		
		// Auxiliary functions
		double s(double x) { // square
			return x * x;
		}
		double r(double x) { // square root
			return sqrt(x);
		}
};


#endif
