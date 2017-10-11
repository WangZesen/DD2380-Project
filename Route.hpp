#ifndef __ROUTE_HPP__
#define __ROUTE_HPP__

#include "Environment.hpp"

using namespace cv;

class Route {
    public:
        // Point list in a route
        std::vector<VectorPoint> set;
        
        // Constructors
        
        // Route with two points
        Route(VectorPoint x, VectorPoint y);
        // Route with one point added
        Route(std::vector<VectorPoint> &set1, VectorPoint &newPoint);
        // Route combined by two routes
        Route(std::vector<VectorPoint> &set1, std::vector<VectorPoint> &set2, int index1, int index2);
        // Route with one point added
        Route(Route *r, VectorPoint &x);
        
        
        // Calculate adaptability for current route
        double adaptability(VectorPoint &endPoint);
        
        // Calculate the length of the route
        double length();
        
        // Return possible mutations with extend mutation method
        std::vector<Route> extendMutation(Environment& env, double dist, Random &generator);
        
        // Return possible mutations with shortening mutation method
        std::vector<Route> shortMutation(Environment& env, double dist);        
        
        // Return possible hybrid results
        std::vector<Route> hybrid(Route &route, Environment& env);
        
        // Visualization
        void drawRoute(Mat &image);

        int indexSum;
        double lengthSum;
        
    private:
        
        // For calculating adaptability in hybrid case
        double partialAdaptability(std::vector<VectorPoint> &set1, std::vector<VectorPoint> &set2, int index1, int index2);
};

#endif
