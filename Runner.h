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
    vector<int> degreeWhenDeleted;
    AdjList orderDeletedList;
public:
    Runner(Graph, Graph, AdjList);
    Runner(Graph);
    void removeVertex(int v);
    void genDegreeList();
    AdjListNode* getSmallestDegree();
    AdjListNode* getSmallestOriginalDegree();
    int deleteSmallestDegree();
    void SLVO();
    void SFVO();
    void colorGraph(vector<int>&);
    void colorGraphSLVO(vector<int>&);
    int getColorToUse(int);
    void SODO();
    void URO();
    void printColors();
};


#endif //ASSIGNMENT2_RUNNER_H
