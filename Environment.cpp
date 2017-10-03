#include "Environment.hpp"

// VectorPoint

void VectorPoint::info() {
	std::cerr << "[Debug] x = " << x << ", y = " << y << std::endl;
}

VectorPoint::VectorPoint(double initX, double initY) {
	x = initX;
	y = initY;
}

VectorPoint VectorPoint::operator-(const VectorPoint &c) const {
	return VectorPoint(x - c.x, y - c.y);
}

VectorPoint VectorPoint::operator+(const VectorPoint &c) const {
	return VectorPoint(x + c.x, y + c.y);
}

double VectorPoint::operator*(const VectorPoint &c) const {
	return (x * c.x + y * c.y);
}

double VectorPoint::cosin(const VectorPoint &c) {
	return (VectorPoint(x, y) * c) / this->length() / c.length();
}

VectorPoint VectorPoint::calAngle(double angle, double dist) {
	return VectorPoint(x + dist * sin(angle * PI / 180.0), y + dist * cos(angle * PI / 180.0));
}


// Obstacle

Obstacle::Obstacle() {
	x = y = kind = r = a = b = 0;
}

Obstacle::Obstacle(int X, int Y, int Kind, int R, int A, int B) {
	x = X;
	y = Y;
	kind = Kind;
	r = R;
	a = A;
	b = B;
}

void Obstacle::set(int X, int Y, int Kind, int R, int A, int B) {
	x = X;
	y = Y;
	kind = Kind;
	r = R;
	a = A;
	b = B;
}

bool Obstacle::isIn(int testX, int testY) {
	switch (kind) {
		case 1: {
			if ((testX - x) * (testX - x) + (testY - y) * (testY - y) <= r * r)
				return true;
			return false;
		}
		case 0: {
			if ((abs(testX - x) < a / 2.0) && (abs(testY - y) < b / 2.0)) 
				return true;
			return false;
		}
	}
}

// Environment

Environment::Environment() {
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
			for (int k = 0; k < numObstacles; k++) {
				within = within || obstacles[k].isIn(i, j);
			}
			
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


std::string Environment::mapToString() {
	std::string output;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			switch (this->at(i, j)) {
				case 0:
					break;
				case 1:
					break;
				case 2:
					output += '#';
					break;
				case 3:
					output += '.';
					break;
			}
		}
		output += '\n';
	}
	return output;
}

void Environment::mapInfo() {
	std::cerr << "[Info] Map height: " << height << ", width = " << width << std::endl;
	for (int i = 0; i < numObstacles; i++) {
		std::cerr << "[Info] Obstacle " << i;
		switch (obstacles[i].kind) {
			case 0:
				std::cerr << " (rectangle): x = " << obstacles[i].x  << ", y = " << obstacles[i].y << ", a = " << obstacles[i].a << ", b = " << obstacles[i].b << std::endl;
				break;
			case 1:
				std::cerr << " (circle): x = " << obstacles[i].x  << ", y = " << obstacles[i].y << ", r = " << obstacles[i].r << std::endl;
				break;
		}
	}
}

int Environment::at(double x, double y) {
	return Map[(int) round(x)][(int) round(y)];
}

int Environment::at(int x, int y) {
	if (0 <= x && x < height && 0 <= y && y < height)
		return Map[x][y];
	else 
		return -1;
}

int Environment::at(VectorPoint &c) {
	return this->at(c.x, c.y);
}

std::vector<VectorPoint> nextPropagation(const VectorPoint& x, const VectorPoint& y, int dist) {
	VectorPoint dir = x - y;
	
	
}





