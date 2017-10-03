#include <iostream>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string>

#define PI 3.14159265359

class VectorPoint {
	private:
		
		double length() const {
			return (x * x + y * y);
		}
	public:
		double x, y;
		void info();
		VectorPoint(double initX, double initY);
		VectorPoint operator-(const VectorPoint &c) const;
		VectorPoint operator+(const VectorPoint &c) const;
		double operator*(const VectorPoint &c) const;
		double cosin(const VectorPoint &c);
		VectorPoint calAngle(double angle, double dist);
		//std::vector<VectorPoint> nextPropagate(const Environment& env, const VectorPoint& pre, double dist);
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
		int at(VectorPoint &c);
		
		
		// Return possible successor
		std::vector<VectorPoint> nextPropagation(const VectorPoint& x, const VectorPoint& y, int dist);
		


	private:
		const int width = 500;
		const int height = 500;
		const int numObstacles = 5;
		int Map[500][500];
		std::vector<Obstacle> obstacles;



};
