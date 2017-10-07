#include "Environment.hpp"

// VectorPoint
VectorPoint calAngle(double angle, double dist) {
    return VectorPoint(dist * sin(angle * PI / 180.0), dist * cos(angle * PI / 180.0));
}

double VectorPoint::length() const {
	return (x * x + y * y);
}

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

VectorPoint VectorPoint::calAngle(double angle, double dist) const {
	return VectorPoint(dist * sin(angle * PI / 180.0), dist * cos(angle * PI / 180.0));
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
	//VectorPoint x(1, 2);
	//x.calAngle(150, 2).info();

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
	
	Obstacle temp(20, 20, 0, 0, 20, 20);
	obstacles.push_back(temp);
	temp.set(height - 20, width - 20, 0, 0, 20, 20);
	obstacles.push_back(temp);
	
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			int within = 4;
			for (int k = 0; k < numObstacles + 2; k++) {
				if ((obstacles[k].isIn(i, j)) && (within > obstacles[k].kind)) {
					within = obstacles[k].kind;
				}
			}
			
			switch (within) {
				case 0: 
					Map[i][j] = 0;
					break;
				case 1:
					Map[i][j] = 1;
					break;
				case 2:
					Map[i][j] = 2;
					break;				
				case 3:
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
					output += 's';
					break;
				case 1:
					output += 't';				
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

int Environment::at(VectorPoint c) {
	return this->at(c.x, c.y);
}

std::vector<VectorPoint> Environment::nextPropagation(const VectorPoint& x, const VectorPoint& y, int dist) {
	std::vector<VectorPoint> result;
	VectorPoint dir = x - y;
	for (int i = 0; i < 360; i += 15) {
		VectorPoint angle = x.calAngle(i, dist);
		if ((angle.cosin(dir) >= 0.697106781) && (this->at(x + angle) != 2) && ((x + angle).x >= 0) && ((x + angle).y >= 0) && ((x + angle).x <= height) && ((x + angle).y <= width)) {
			result.push_back(x + angle);
		}
	}
	return result;
}





