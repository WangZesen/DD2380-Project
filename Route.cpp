#include "Route.hpp"

Route::Route(std::vector<VectorPoint> &set1, std::vector<VectorPoint> &set2, int index1, int index2) {
    for (int i = 0; i <= index1; i++) {
        set.push_back(set1[i]);
    }
    for (int i = index2; i < set2.size(); i++) {
        set.push_back(set2[i]);
    }
    lengthSum = 0.0;
    indexSum = 0;
    srand((unsigned int)time(NULL));
}

Route::Route(std::vector<VectorPoint> &set1, VectorPoint &newPoint) {
    int len = set1.size();
    set = set1;
    set.push_back(newPoint);
}

Route::Route(VectorPoint x, VectorPoint y) {
    set.push_back(x);
    set.push_back(y);
    
    lengthSum = (x - y).length();
    indexSum = 1;
}

Route::Route(Route *r, VectorPoint &x) {
    if (r->indexSum < r->set.size() - 1) {
        for (int i = indexSum; i < r->set.size() - 1; i++) {
            r->lengthSum += (r->set[i] - r->set[i + 1]).length();
            r->indexSum++;
        }
    }
    lengthSum = r->lengthSum + (r->set[r->set.size() - 1] - x).length();
    indexSum = r->indexSum + 1;
    set = r->set;
    set.push_back(x);
}

double Route::adaptability(VectorPoint &endPoint) {
    int len = set.size();
    for (int i = indexSum; i < len - 1; i++) {
        lengthSum += (set[i + 1] - set[i]).length();
        indexSum += 1;
    }
    //sum *= 2;
    double sum = lengthSum;
    sum += (set[len - 1] - endPoint).length() * 2;
    if (len > 100) len = 100;
    return sum / len;
}

std::vector<Route> Route::shortMutation(Environment& env, double dist) {
    
    int len = set.size();
    
    if (len < 80)
        return std::vector<Route>(); 
    
    std::vector<Route> mutatedRoutes;
    
    for (int i = 0; i < 5; i++) {
        int index = rand() % (len - 50) + 1;
        int nextIndex = index + rand() % 45 + 2;
        if (nextIndex >= len - 2)
            nextIndex = len - 2;
            
        if ( ( (set[index] - set[index - 1]).cosin(set[nextIndex] - set[index]) >= 0.697106781) && ((set[nextIndex + 1] - set[nextIndex]).cosin(set[nextIndex] - set[index]) >= 0.697106781) && (env.blocked(set[index], set[nextIndex]))) {
            mutatedRoutes.push_back(Route(set, set, index, nextIndex));
        }
    }
    
    return mutatedRoutes;
}

std::vector<Route> Route::extendMutation(Environment& env, double dist) {
    
    int len = set.size();
    std::vector<VectorPoint> result = env.nextPropagation(set[len - 1], set[len - 2], dist);
    int stateNum = result.size();
    
    std::vector<Route> mutatedRoutes;
    
    for (int i = 0; i < stateNum; i++) {
        mutatedRoutes.push_back(Route(this, result[i]));
    }
    
    return mutatedRoutes;
}

std::vector<Route> Route::hybrid(Route &route, Environment& env) {


    int len1 = set.size();
    int len2 = route.set.size();
    

    
    if ((len1 < 50) || (len2 < 50))
        return std::vector<Route>();

    std::vector<Route> hybrids;
    int index1, index2;    
    
    index1 = rand() % (len1 - 2) + 1;
    index2 = rand() % (len2 - 2) + 1;
    if ( ((set[index1] - set[index1 - 1]).cosin(route.set[index2] - set[index1]) >= 0.697106781) && ((route.set[index2 + 1] - route.set[index2]).cosin(route.set[index2] - set[index1]) >= 0.697106781) && (env.blocked(set[index1], route.set[index2]))) {
        hybrids.push_back(Route(set, route.set, index1, index2));
    }
        
    return hybrids;
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
