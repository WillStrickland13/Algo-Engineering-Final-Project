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
                cout<<"degreePointerToChange: "<<degreePointerToChange->data<<endl;
                int currDegree=edgeList.getDegree(index);
                cout<<"currdegree "<<currDegree<<endl;

//                cout<<"tail = "<<degreeList[currDegree - 1].tail->data;

                if(degreeList[currDegree-1].head!=nullptr) {


                    cout<<"step1"<<endl;

                    degreeList[currDegree].removeAdjListNodeByVertex(degreePointerToChange->data);
                    degreePointerToChange->next=nullptr;
                    cout<<"step4"<<endl;
                    degreePointerToChange->prev=degreeList[currDegree - 1].tail;
                    cout<<"step5"<<endl;
                    degreeList[currDegree - 1].tail = degreePointerToChange;
                    cout<<"step6"<<endl;
                    degreePointerToChange->prev->next = degreePointerToChange;
                    cout<<"step7"<<endl;




//                    cout<<"error1"<<endl;
//
//                    degreePointerToChange->prev = degreeList[currDegree - 1].tail;
//                    cout<<"error2"<<endl;
//                    degreeList[currDegree - 1].tail->next = degreePointerToChange;
//
//
//                    cout<<"error3"<<endl;
//                    degreeList[currDegree - 1].tail = degreePointerToChange;
                }
                else{
                    cout<<"error4"<<endl;
                    degreeList[currDegree-1].head=degreePointerToChange;
                    cout<<"error5"<<endl;
                    degreeList[currDegree-1].tail=degreePointerToChange;
                    cout<<"error6"<<endl;
                    degreeList[currDegree].removeAdjListNodeByVertex(degreePointerToChange->data);


                }
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
