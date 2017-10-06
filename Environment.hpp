#include <iostream>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string>

#define PI 3.14159265359

class VectorPoint {
		
	public: 
		//	      90
		//         |
		//         |
		// 180------------0(360)
		//         |
		//         |
		//        270 
		double length() const;
		double x, y;
		void info();
		VectorPoint(double initX, double initY);
		
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
		//error: expected initializer before ‘switch’
		// 1 = circle

		Obstacle();

		Obstacle(int X, int Y, int Kind, int R, int A, int B);

		void set(int X, int Y, int Kind, int R, int A, int B);

		bool isIn(int testX, int testY);
};

class Environment {
	public:
		// initial a map
		Environment();

		// Return map in string
		std::string mapToString();

		// Return map information
		void mapInfo();

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

		VectorPoint closestPoint(const VectorPoint &c, int index);
		double calDist(const VectorPoint &c, int index);
		double potential(const VectorPoint& c);

	private:
		const int width = 500;
		const int height = 500;
		const int numObstacles = 5;
		int Map[500][500];
		std::vector<Obstacle> obstacles;
		
		double s(double x) {
			return x * x;
		}
		
		double r(double x) {
			return sqrt(x);
		}



};
