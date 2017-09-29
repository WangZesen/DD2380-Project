#include <iostream>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string>

#define PI 3.14159265359

class VectorPoint {
	private:
		double x, y;
		double length() const {
			return (x * x + y * y);
		}
	public:
		void info() {
			std::cerr << "[Debug] x = " << x << ", y = " << y << std::endl;
		}
		VectorPoint(double initX, double initY) {
			x = initX;
			y = initY;
		}
		VectorPoint operator-(const VectorPoint &c) const {
			return VectorPoint(x - c.x, y - c.y);
		}
		double operator*(const VectorPoint &c) const {
			return (x * c.x + y * c.y);
		}
		double cosin(const VectorPoint &c) {
			return (VectorPoint(x, y) * c) / this->length() / c.length();
		}
		VectorPoint calAngle(double angle, double dist) {
			return VectorPoint(x + dist * sin(angle * PI / 180.0), y + dist * cos(angle * PI / 180.0));
		}
};

class Obstacle {
	private:
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

		Obstacle() {
			x = y = kind = r = a = b = 0;
		}

		Obstacle(int X, int Y, int Kind, int R, int A, int B) {
			x = X;
			y = Y;
			kind = Kind;
			r = R;
			a = A;
			b = B;
		}

		void set(int X, int Y, int Kind, int R, int A, int B) {
			x = X;
			y = Y;
			kind = Kind;
			r = R;
			a = A;
			b = B;
		}

		bool isIn(int testX, int testY) {
			switch (kind) {
				case 0: {
					if ((testX - x) * (testX - x) + (testY - y) * (testY - y) <= r * r)
						return true;
					return false;
				}
				case 1: {
					if ((abs(testX - x) < a / 2.0) && (abs(testY - y) < b / 2.0)) 
						return true;
					return false;
				}
			}
		}
};

class Environment {
	public:
		// initial a map
		Environment() {
		
			VectorPoint x(1, 2);
			x.calAngle(150, 2).info();
		
			srand((unsigned int) time(NULL));
			for (int i = 0; i < numObstacles; i++) {
				switch (rand() % 2) {
					case 0: {
						Obstacle temp(rand() % height, rand() % width, 0, 0, rand() % (height / 10) + 10, rand() % (height / 10) + 10);
						obstacles.push_back(temp);
						break;
					}
					case 1: {
						Obstacle temp(rand() % height, rand() % width, 1, rand() % (height / 10) + 10, 0, 0);
						obstacles.push_back(temp);
						break;
					}
				}
			}

			for (int i = 0; i < height; i++) {
				for (int j = 0; j < width; j++) {
					bool within = false;
					for (int k = 0; k < numObstacles; k++) 
						within = within || obstacles[k].isIn(i, j);
					switch ((int) within) {
						case 1: 
							Map[i][j] = 2;
							break;
						case 0:
							Map[i][j] = 3;
							break;
					}
				}
			}
		}

		// Return map in string
		std::string mapToString() {

		}

		// Return map information
		std::string mapInfo() {

		}

		// Return the circustance on point (x, y)
		// 0 = start area
		// 1 = goal area
		// 2 = obstacle
		// 3 = empty
		int at(double x, double y) {
			return Map[(int) round(x)][(int) round(y)];
		}
		int at(int x, int y) {
			if (0 <= x && x < height && 0 <= y && y < height)
				return Map[x][y];
			else 
				return -1;
		}
		
		// Return possible successor
		std::vector<int> test() {
		}
		


	private:
		const int width = 500;
		const int height = 500;
		const int numObstacles = 5;
		int Map[500][500];
		std::vector<Obstacle> obstacles;



};
