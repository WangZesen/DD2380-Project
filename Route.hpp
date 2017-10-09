#ifndef __ROUTE_HPP__
#define __ROUTE_HPP__

#include "Environment.hpp"

using namespace cv;

class Route {
    public:
        std::vector<VectorPoint> set;
        
        Route(VectorPoint x, VectorPoint y);
        Route(std::vector<VectorPoint> &set1, VectorPoint &newPoint);
        Route(std::vector<VectorPoint> &set1, std::vector<VectorPoint> &set2, int index1, int index2);
        Route(Route *r, VectorPoint &x);
        
        double adaptability(VectorPoint &endPoint);
        std::vector<Route> extendMutation(Environment& env, double dist);
        std::vector<Route> shortMutation(Environment& env, double dist);        
        Route hybrid(Route &route, Environment& env);
        
        // Visualization
        void drawRoute(Mat &image);

        int indexSum;
        double lengthSum;
        
    private:

        double partialAdaptability(std::vector<VectorPoint> &set1, std::vector<VectorPoint> &set2, int index1, int index2);
};

#endif
