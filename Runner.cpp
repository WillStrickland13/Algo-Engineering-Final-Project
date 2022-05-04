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

void Runner::removeVertex(int v) {

    //need to go through all vertices with v as an edge and remove v from their edges
    //and update the degree list

    int degree=edgeList.getDegree(v);
    degreeList[degree].removeAdjListNodeByVertex(v);

    for(int i=0;i<edgeList[v].size();i++){
        //get edge of vertex to remove
        int index=edgeList[v][i].data;
        for(int j=0;j<edgeList[index].size();j++){
            //if the edge is v, remove it
            if(edgeList[index][j].data==v){
                cout<<"index = "<<index<<" j = "<<j<<endl;
                //only first index has a degree list pointer

                AdjListNode* degreePointerToChange = edgeList[index].degreeListPointer;
                cout<<"test";
                int currDegree=edgeList.getDegree(index);

                degreeList[currDegree].removeAdjListNodeByVertex(degreePointerToChange->data);
                degreeList.addEdgeToDegreeList(currDegree - 1, degreePointerToChange->data, degreeList);


                //finally remove the edge from the graph
                cout<<"deleting edge "<<v<<endl;
                edgeList[index].removeAdjListNodeByVertex(v);
                cout<<"done"<<endl;

                break;
            }
        }
    }


    //then set v to null
    edgeList[v].head = NULL;
    degreeList.printDegreeGraph();


}

AdjListNode* Runner::getSmallestDegree() {
    AdjListNode *temp;
    for(int i=0;i<degreeList.getNumVertices();i++){
        if(degreeList[i].head!=NULL){
            temp = degreeList[i].head;
            return temp;
        }
    }

}

int Runner::deleteSmallestDegree() {
    AdjListNode* toDelete = getSmallestDegree();
    int degree = toDelete->data;
//    orderDeletedList.addAdjListNode(toDelete);
    removeVertex(toDelete->data);
    return degree;

}

void Runner::deleteAll(){
    int numVertices=edgeList.getNumVertices();
    vector<int> orderDeleted;
    int vertex;
    for(int i=0;i<numVertices;i++){
        vertex= (deleteSmallestDegree());
        orderDeleted.push_back(vertex);
    }


    for(int i =0;i<orderDeleted.size();i++){
        cout<<orderDeleted[i]<<" ";
    }

}

void Runner::printOrderDeletedList(){
    orderDeletedList.printAdjList();
//    for(int i=0;i<order.size();i++){
//        cout<<order[i]<<" ";
//    }
}


