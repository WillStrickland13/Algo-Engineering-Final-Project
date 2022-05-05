//
// Created by William Strickland on 5/1/22.
//

#ifndef ASSIGNMENT2_RUNNER_H
#define ASSIGNMENT2_RUNNER_H

#include "Vertex.h"
#include "Graph.h"
#include <vector>
using namespace std;
class Runner {
private:
    Graph edgeList;
    Graph edgeListTemp;
    Graph degreeList;
    AdjList orderDeletedList;
public:
    Runner(Graph, Graph, AdjList);
    Runner(Graph);
    void removeVertex(int v);
    void genDegreeList();
    AdjListNode* getSmallestDegree();
    int deleteSmallestDegree();
    void deleteAll();
    void colorGraph(vector<int>&);
    int getColorToUse(int);
    void printColors();
};


#endif //ASSIGNMENT2_RUNNER_H
