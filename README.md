# DD2380-Project
DD2380 Artificial Intelligence Project

This project implements route planning with Genetic Algorithm and Genetic Algorithm assisted by Artificial Potential Field. The details of implementation is commented in the program. 

Prerequisites:
    Opencv 2.4.9 (Installed on Linux computers in Building E & D)
    
Adjustable Parameters (in Parameters.hpp):
    angleGap: the angle difference between initial routes
    survivalNum: the number of routes remained after filter
    extendDist: the distance extended when doing extending mutation
    hybridPro: the probability that two routes hybrid
    APFOn: set it 1 if wanting to open Artificial Potential Field's assistance
    obstacleNum: the number of obstacles (used in random map initialization)
    mapNum: initialize a preset map, and the number of map is mapNum
    stepVisual: set it true if wanting to show the result for every 50 generations

Note:
    The program can be perfectly compiled and run on the Linux computers in Building D & E.
    
Github Link:
    https://github.com/WangZesen/DD2380-Project/tree/APF

![solarized dualmode](https://github.com/WangZesen/DD2380-Project/blob/APF/sample.png)

![solarized dualmode](https://github.com/WangZesen/DD2380-Project/blob/APF/sample1.png)
