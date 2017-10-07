#include "Environment.hpp"
#include <iostream>
using namespace std;
int main() {
	Environment test;
	//cout << test.at(10, 10);
	test.mapInfo();
	
	VectorPoint x(10, 0);
	VectorPoint y(11, 1);
	
	vector<VectorPoint> result = test.nextPropagation(y, x, 1);
	for (int i = 0; i < result.size(); i++) {
		std::cerr << "[Debug] Point " << i << ": x = " << result[i].x << ", y = " << result[i].y << std::endl;
	}
	
	cerr << test.startPoint().x << " " << test.startPoint().y << endl;
}
