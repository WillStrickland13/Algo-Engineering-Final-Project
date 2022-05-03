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
    for(int i=0;i<edgeList[v].size();i++){
        //get edge of vertex to remove
        int index=edgeList[v][i].data;
        for(int j=0;j<edgeList[index].size();j++){
            //if the edge is v, remove it
            if(edgeList[index][j].data==v){
                cout<<"index = "<<index<<" j = "<<j<<endl;
                //only first index has a degree list pointer

                AdjListNode* degreePointerToChange = edgeList[index].head->degreeListPointer;
                int currDegree=edgeList.getDegree(index);

                if(degreeList[currDegree-1].head!=nullptr) {


                    //first remove node from current degree list
                    //cout<<"test1"<<endl;
                    degreeList[currDegree].removeAdjListNodeByVertex(degreePointerToChange->data);

                    //then append node to the end of degree list -1
                    //cout<<"test2"<<endl;
                    degreePointerToChange->next=nullptr;
                    //cout<<"test3"<<endl;
                    degreePointerToChange->prev=degreeList[currDegree - 1].tail;
                    //cout<<"test4"<<endl;
                    degreeList[currDegree - 1].tail = degreePointerToChange;
                    //cout<<"test5"<<endl;
                    degreePointerToChange->prev->next = degreePointerToChange;

                }
                //  case to handle if the degree list -1 is empty
                else{

                    //cout<<"test6"<<endl;
                    degreeList[currDegree-1].head=degreePointerToChange;
                    //cout<<"test7"<<endl;
                    degreeList[currDegree-1].tail=degreePointerToChange;
                    //cout<<"test8"<<endl;
                    degreeList[currDegree].removeAdjListNodeByVertex(degreePointerToChange->data);
                    //cout<<"test9"<<endl;

                }

                //finally remove the edge from the graph
                edgeList[index].removeAdjListNode(j);
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
    removeVertex(toDelete->data);
}
