//
// Created by William Strickland on 4/30/22.
//

#ifndef ASSIGNMENT2_GRAPH_H
#define ASSIGNMENT2_GRAPH_H

#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <random>
#include <algorithm>
#include "AdjList.h"
using namespace std;
using namespace std::chrono;


class Graph {

private:
    int V,E;
    vector<pair<int,int>> enumerated_edges;
    struct AdjList *array;

public:

    //default constructor
    Graph() {
        V = 0;

        E = 0;
        array = new AdjList[V];
        array[0].head = nullptr;
        array[0].tail = nullptr;
    }

    //create a graph with V vertices
    Graph(int V) {
        this->V = V;
        array = new AdjList[V];
        for (int i = 0; i < V; ++i) {
            array[i].head = nullptr;
            array[i].tail = nullptr;
        }
    }
    Graph copyGraph() {
        Graph g2(V);
        g2.E = E;
        for (int i = 0; i < V; i++) {
            AdjListNode *temp;
            AdjListNode *index=array[i].head;
            while (index != nullptr) {
                temp = new AdjListNode;
                temp->data= index->data;
                g2.array[i].addAdjListNode(temp);
                index=index->next;
            }

        }
        g2.printGraph();
        cout<<"finished copying"<<endl;
        return g2;
    }


    void removeVertex(int v) {
        //need to go through all vertices with v as an edge and remove v from their edges
        //and update the degree list
        for(int i=0;i<array[v].size();i++){
            //get edge of vertex to remove
            int index=array[v][i].data;
            for(int j=0;j<array[index].size();j++){
                //if the edge is v, remove it
                if(array[index][j].data==v){
                    AdjListNode* degreePointerToChange = array[index].degreeListPointer;

                    //degreeList[degreePointerToChange.data-1].tail = degreePointerToChange
                    array[index].removeAdjListNode(j);
                    break;
                }
            }
        }


        //then set v to null
        array[v].head = nullptr;



    }

    //return the number of vertices
    int getNumVertices() {
        return V;
    }


    //return the number of edges
    int getNumEdges() {
        return E;
    }

    //enumerate the edges, used for the random graph generator to avoid duplicate edges
    void enumerateEdges(){
        cout<<"Enumerating edges..."<<endl;
        for (int i = 0; i < V; i++) {
            for (int j = i+1; j < V; j++) {
                if (i != j) {
                    pair<int, int> edge = make_pair(i, j);
                    enumerated_edges.push_back(edge);
                }
            }
        }
    }

    /*
     * Creating New Adjacency List Node
     */
    AdjListNode *newAdjListNode(int data) {
        AdjListNode *newNode = new AdjListNode;
        newNode->data = data;
        newNode->next = nullptr;
        newNode->prev = nullptr;
        return newNode;
    }

    /*
     * Adding Edge to Graph
     */
    void addEdge(int src, int data) {
        AdjListNode *newNode = newAdjListNode(data);
        newNode->prev = array[src].tail;
        newNode->next = nullptr;
        array[src].tail = newNode;
        if (array[src].head == nullptr)
            array[src].head = newNode;
        else
            newNode->prev->next = newNode;

    }

    //used to create the degree list graph, and adds a pointer to the degree list for each node in original graph
    void addEdgeToDegreeList(int src, int data,Graph& edgeList) {
        AdjListNode *newNode = newAdjListNode(data);
        if(edgeList.array[data].head!=nullptr) {
            edgeList.array[data].degreeListPointer = newNode;
        }
        newNode->prev = array[src].tail;
        newNode->next = nullptr;
        array[src].tail = newNode;
        if (array[src].head == nullptr)
            array[src].head = newNode;
        else
            newNode->prev->next = newNode;

    }

    /*
     * Print the graph
     */
    void printGraph() {
        int v;
        for (v = 0; v < V; ++v) {
            if(array[v].head!=nullptr) {
                AdjListNode *pCrawl = array[v].head;

                cout << "\n Adjacency list of vertex " << v << "\n head ";
                while (pCrawl) {
                    cout << "-> " << pCrawl->data;
                    pCrawl = pCrawl->next;
                }
                cout << "-> tail";
                cout << endl;
            }
        }
    }

    //used to make sure the pointer from graph to degree list is correct
    void testPtr(int v){
        cout<<array[v].degreeListPointer->data<<endl;
    }


    //print the degree list
    void printDegreeGraph() {
        int v;
        for (v = 0; v <= V-1; ++v) {
            AdjListNode *pCrawl = array[v].head;
            cout << "\n Vertices with Degree " << v << "\n head ";
            while (pCrawl) {
                cout << "-> " << pCrawl->data;
//                cout<<(pCrawl->next==nullptr)<<endl;
                pCrawl = pCrawl->next;
            }
            cout << "-> tail";
            cout << endl;
        }
    }

    //get number of edges of a specific vertex
    int getNumEdges(int vertex) {
        if (vertex < 0) {
            return 0;
        }
        int numEdges = 0;
        AdjListNode *pCrawl = array[vertex].head;
        while (pCrawl) {
            numEdges++;
            pCrawl = pCrawl->next;
        }
        return numEdges;
    }

    //get edges of a specific vertex
    vector<int> getEdges(int vertex) {
        vector<int> edges;
        AdjListNode *pCrawl = array[vertex].head;
        while (pCrawl) {
            edges.push_back(pCrawl->data);
            pCrawl = pCrawl->next;
        }
        return edges;
    }

    //generate a complete graph with v vertices
    void genCompleteGraph(int V) {

        this->V = V;
        array = new AdjList[V];
        for (int i = 0; i < V; ++i) {
            array[i].head = nullptr;
            array[i].tail = NULL;
        }

        auto start = chrono::high_resolution_clock::now();
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (i != j) {
                    addEdge(i, j);
                }
            }
        }
        auto stop = chrono::high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);

        cout << "Complete graph with " << V << " vertices took " << duration.count() / 1000.0 << " milliseconds"
             << endl;
    }

    //generate a cycle graph with v vertices
    void genCycleGraph(int V) {
        this->V = V;
        array = new AdjList[V];
        for (int i = 0; i < V; ++i) {
            array[i].head = nullptr;
            array[i].tail = nullptr;
        }
        auto start = chrono::high_resolution_clock::now();

        for (int i = 0; i < V - 1; i++) {
            addEdge(i, i + 1);
            addEdge(i + 1, i);
        }
        addEdge(V - 1, 0);
        addEdge(0, V - 1);
        auto stop = chrono::high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);

        cout << "Cycle graph with " << V << " vertices took " << duration.count() / 1000.0 << " milliseconds" << endl;

    }

    //used for random graph generation
    vector<int> genVector(int size) {
        vector<int> nums;
        for(int i = size-1;i>=0; i--){
            nums.push_back(i);
        }
        return nums;
    }


    //generate a skewed number, used for generating a random index of the enumerated edges
    int genSkewedNum(vector<int> nums){
        //set seed
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        //set generator
        static std::default_random_engine generator(seed);

        //generate skewed random number with smaller numbs being more likely
        std::discrete_distribution<int> distribution(nums.begin(), nums.end());
        return distribution(generator);

    }
    int genSkewedReverseNum(vector<int> nums){
        //set seed
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        //set generator
        static std::default_random_engine generator(seed);
        reverse(nums.begin(), nums.end());

        //generate skewed random number with smaller numbs being more likely
        std::discrete_distribution<int> distribution(nums.begin(), nums.end());
        return distribution(generator);

    }

    //generate a normal number, used for creating a normal index of the enumerated index
    int genNormalNum(int size){
        //set seed
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        //set generator
        static std::default_random_engine generator(seed);

        //generate skewed random number with smaller numbs being more likely
        std::exponential_distribution<int> distribution(1);

        return distribution(generator);

    }

    //generate a completely pseudo-random index of the enumerated edges
    int genRandomNum (int max)
    {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

        static std::default_random_engine generator(seed);
        std::uniform_int_distribution<int> distribution (0,max);
        return distribution(generator);
    }

    //generate a random graph with v vertices and e edges, can specify the type of graph
    //(complete, cycle, random) and if random, can specify the type of random graph
    // (normal, skewed, uniform)
    void genGraph(int V, int E, string type, string distribution) {
        this->V = V;
        this->E = E;
        srand (time(NULL));
        if (type == "COMPLETE") {
            this->E=V*(V-1)/2;
            genCompleteGraph(V);
        }
        else if (type == "CYCLE") {
            this->E=V;
            genCycleGraph(V);
        }
        else if (type == "RANDOM") {

            //enumerate nums
            enumerateEdges();

            vector<int> nums = genVector(enumerated_edges.size()-1);
            for (int i = 0; i < E; i++) {
                if (distribution == "UNIFORM") {

                    //get random edge from list of enumerated edges and add it to the graph
                    int randIndex = genRandomNum(nums.size()-1);

                    //make edge to go both ways
                    addEdge(enumerated_edges[randIndex].first, enumerated_edges[randIndex].second);
                    addEdge(enumerated_edges[randIndex].second, enumerated_edges[randIndex].first);
                    //remove edge from list of enumerated edges once it is added to the graph
                    enumerated_edges.erase(enumerated_edges.begin() + randIndex);
                    nums.erase(nums.begin() + randIndex);

                }
                else if (distribution == "SKEWED") {
                    //get skewed index from list of enumerated edges and add it to the graph
                    int skewedIndex = genSkewedNum(nums);

                    //make edge to go both ways
                    addEdge(enumerated_edges[skewedIndex].first, enumerated_edges[skewedIndex].second);
                    addEdge(enumerated_edges[skewedIndex].second, enumerated_edges[skewedIndex].first);
                    //remove edge from list of enumerated edges once it is added to the graph
                    enumerated_edges.erase(enumerated_edges.begin() + skewedIndex);
                    nums.erase(nums.begin() + skewedIndex);
                }
                //this distribution is normal
                else if (distribution == "YOURS") {
                    //get skewed index from list of enumerated edges and add it to the graph
                    int skewedReverseIndex = genSkewedReverseNum(nums);

                    //make edge to go both ways
                    addEdge(enumerated_edges[skewedReverseIndex].first, enumerated_edges[skewedReverseIndex].second);
                    addEdge(enumerated_edges[skewedReverseIndex].second, enumerated_edges[skewedReverseIndex].first);
                    //remove edge from list of enumerated edges once it is added to the graph
                    enumerated_edges.erase(enumerated_edges.begin() + skewedReverseIndex);
                    nums.erase(nums.begin() + skewedReverseIndex);
                }
            }
        }
    }

    //return the list of edges of a vertex in the graph
    AdjList* getAdjList(int v) {
        return &array[v];
    }
    int getDegree(int v) {
        int size=0;
        AdjListNode *pCrawl = array[v].head;
        while (pCrawl) {
            size++;
            pCrawl = pCrawl->next;
        }
        return size;
    }

    AdjList& operator[](int index)
    {
        return array[index];

    }


};

//
//void printSerialization(Graph g, int V) {
//    ofstream myFile;
//    myFile.open("output.txt");
//    myFile << V << endl;
//    int lastLine = V;
//    for (int i = 1; i <= V; i++) {
//        myFile << lastLine + g.getNumEdges(i - 1) << endl;
//        lastLine = lastLine + g.getNumEdges(i - 1);
//    }
//    for (int i = 0; i < V; i++) {
//        vector<int> vEdges = g.getEdges(i);
//        for (int j = 0; j < vEdges.size(); j++) {
//            myFile << vEdges[j] << endl;
//        }
//    }
//
//}








#endif //ASSIGNMENT2_GRAPH_H
