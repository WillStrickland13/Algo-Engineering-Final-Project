//
// Created by William Strickland on 5/1/22.
//

#include "Runner.h"
Runner::Runner(Graph edgeList, Graph degreeList, AdjList orderDeletedList) {
    this->edgeList = edgeList;
    this->degreeList = degreeList;
    this->orderDeletedList = orderDeletedList;
}
Runner::Runner(Graph edgeList) {
    this->edgeList = edgeList;
    Graph degreeList(edgeList.getNumVertices());
    this->degreeList = degreeList;
}

void Runner::genDegreeList(){
    int v;

    for (v = 0; v < edgeList.getNumVertices(); v++) {
        degreeList.addEdgeToDegreeList(edgeList.getDegree(v), v,edgeList);
    }
    edgeListTemp=edgeList;
    degreeList.printDegreeGraph();
}
AdjListNode* Runner::getSmallestDegree() {
    int smallestDegree;
    AdjListNode *temp;
    for(int i=0;i<degreeList.getNumVertices();i++){
        if(degreeList[i].head!=NULL){
            int smallestDegree=i;
            temp = degreeList[i].head;
            return temp;
        }
    }
}
void Runner::deleteSmallestDegree() {
    AdjListNode* toDelete = getSmallestDegree();
    orderDeletedList.addAdjListNode(toDelete);
    edgeList.removeVertex(toDelete->data);
}
