//
// Created by William Strickland on 5/1/22.
//

#ifndef ASSIGNMENT2_RUNNER_H
#define ASSIGNMENT2_RUNNER_H

#include "Vertex.h"
#include "Graph.h"
using namespace std;
class Runner {
private:
    Graph edgeList;
    Graph edgeListTemp;
    Graph degreeList;
    vector<Vertex> orderDeletedList;
public:
    Runner(Graph, Graph, vector<Vertex>);
    Runner(Graph);
    void genDegreeList();
};


#endif //ASSIGNMENT2_RUNNER_H
