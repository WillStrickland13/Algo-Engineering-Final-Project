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
    this->edgeListTemp = edgeListTemp;
}

void Runner::genDegreeList(){
    int v;
    cout<<"degreeList"<<endl;
    for (v = 0; v < edgeList.getNumVertices(); v++) {
        degreeList.addEdgeToDegreeList(edgeList.getDegree(v), v,edgeList);
    }
    cout<<"Starting to copy"<<endl;
    edgeListTemp=edgeList.copyGraph();
    cout<<"done"<<endl;
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
    colorGraph(orderDeleted);
}

void Runner::colorGraph(vector<int>& orderDeleted) {
    cout<<"Printing temp graph"<<endl;
    //edgeListTemp.printGraph();
    for(int i = 0;i<orderDeleted.size();i++){
        int vertex=orderDeleted[i];
        int color= getColorToUse(vertex);
        edgeListTemp[vertex].color=color;
        cout<<"vertex "<<vertex<<" color "<<color<<endl;


    }
}
int Runner::getColorToUse(int v){
    //get the
    AdjListNode* node = edgeListTemp[v].head;
    set<int> colors={-1};
    while (node != nullptr)
    {
        colors.insert(edgeListTemp[node->data].color);
        node = node->next;
    }
    for(int i = 0;i < colors.size();i++){
        if(colors.find(i)==colors.end()){
            cout<<"FOUND COLOR "<<i<<endl;
            return i;
        }
    }
    return colors.size();
}

void Runner::printColors() {
    cout<<endl;
    for(int i=0;i<edgeListTemp.getNumVertices();i++){
        cout<<"Color of vertex "<<i<<": "<<edgeListTemp[i].color<<endl;
    }
    cout<<endl;
}
