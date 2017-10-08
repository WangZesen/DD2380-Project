#include "Route.hpp"

Route::Route(std::vector<VectorPoint> &set1, std::vector<VectorPoint> &set2, int index1, int index2) {
    for (int i = 0; i <= index1; i++) {
        set.push_back(set1[i]);
    }
    for (int i = index2; i < set2.size(); i++) {
        set.push_back(set2[i]);
    }
}

Route::Route(std::vector<VectorPoint> &set1, VectorPoint &newPoint) {
    int len = set1.size();
    set = set1;
    set.push_back(newPoint);
}

Route::Route(VectorPoint x, VectorPoint y) {
    set.push_back(x);
    set.push_back(y);
}

double Route::adaptability(VectorPoint &endPoint) {
    int len = set.size();
    double sum = 0;
    for (int i = 0; i < len - 1; i++) {
        sum += (set[i + 1] - set[i]).length();
    }
    sum *= 2;
    sum += (set[len - 1] - endPoint).length();
    return sum;
}

std::vector<Route> Route::mutation(Environment& env) {
    
    int len = set.size();
    std::vector<VectorPoint> result = env.nextPropagation(set[len - 1], set[len - 2], 1);
    int stateNum = result.size();
    
    std::vector<Route> mutatedRoutes;
    
    for (int i = 0; i < stateNum; i++) {
        mutatedRoutes.push_back(Route(set, result[i]));
    }
    return mutatedRoutes;
}

Route Route::hybrid(Route &route, Environment& env) {
    int len1 = set.size();
    int len2 = route.set.size();
    
    double min = 0x7fffffff;
    int index1, index2;
    
    for (int i = 1; i < len1; i++) {
        for (int j = 1; j < len2; j++) {
            if (env.blocked(set[i], route.set[j])) {
                double temp = partialAdaptability(set, route.set, i, j);
                if (temp < min) {
                    min = temp;
                    index1 = i;
                    index2 = j;
                }
            }
        }
    }
    
    return Route(set, route.set, index1, index2);
}

void Route::drawRoute(Mat &image) {
    int len = set.size();
    
    for (int i = 0; i < len - 1; i++) {
        line(image, Point(int(set[i].x), int(set[i].y)), Point(int(set[i + 1].x), int(set[i + 1].y)), Scalar(255, 0, 0));
    }
}

double Route::partialAdaptability(std::vector<VectorPoint> &set1, std::vector<VectorPoint> &set2, int index1, int index2) {
    double sum = 0;
    for (int i = 0; i < index1; i++) {
        sum += (set1[i + 1] - set1[i]).length();
    }
    sum += (set1[index1] - set2[index2]).length();
    for (int i = index2; i < set2.size() - 1; i++) {
        sum += (set2[i + 1] - set2[i]).length();
    }
    return sum;
}
