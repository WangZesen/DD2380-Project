#include "Environment.hpp"
#include <vector>
class Route {
    public:
        std::vector<VectorPoint> set;
        
        Route(VectorPoint &x, VectorPoint &y);
        Route(std::vector<VectorPoint> &set1, VectorPoint &newPoint);
        Route(std::vector<VectorPoint> &set1, std::vector<VectorPoint> &set2, int index1, int index2);
        
        double adaptability(VectorPoint &endPoint);
        std::vector<Route> mutation(Environment& env);
        Route hybrid(Route &route, Environment& env);
        
    private:
        
        double partialAdaptability(std::vector<VectorPoint> &set1, std::vector<VectorPoint> &set2, int index1, int index2);
};
