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
using namespace std;
using namespace std::chrono;

struct AdjListNode {
    int data;
    struct AdjListNode *next;
    struct AdjListNode *prev;
    struct AdjListNode *degreeListPointer;
};

/*
 * Adjacency List
 */
struct AdjList {
    struct AdjListNode *head;
    struct AdjListNode *tail;
};

class Graph {

private:
    int V,E;
    vector<pair<int,int>> enumerated_edges;
    struct AdjList *array;

public:
    Graph() {
        V = 0;

        E = 0;
        array = new AdjList[V];
        array[0].head = NULL;
        array[0].tail = NULL;
    }

    Graph(int V) {
        this->V = V;
        array = new AdjList[V];
        for (int i = 0; i < V; ++i) {
            array[i].head = NULL;
            array[i].tail = NULL;
        }
    }
    int getNumVertices() {
        return V;
    }
    int getNumEdges() {
        return E;
    }

    void enumerateEdges(){
        cout<<"Enumerating edges..."<<endl;
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
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
        newNode->next = NULL;
        newNode->prev = NULL;
        newNode->degreeListPointer = NULL;
        return newNode;
    }

    /*
     * Adding Edge to Graph
     */
    void addEdge(int src, int data) {
        AdjListNode *newNode = newAdjListNode(data);
        newNode->prev = array[src].tail;
        newNode->next = NULL;
        array[src].tail = newNode;
        if (array[src].head == NULL)
            array[src].head = newNode;
        else
            newNode->prev->next = newNode;

    }

    void addEdgeToDegreeList(int src, int data,Graph& edgeList) {
        AdjListNode *newNode = newAdjListNode(data);
        if(edgeList.array[data].head!=NULL) {
            edgeList.array[data].head->degreeListPointer = newNode;
        }
        newNode->prev = array[src].tail;
        newNode->next = NULL;
        array[src].tail = newNode;
        if (array[src].head == NULL)
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


    void printDegreeGraph() {
        int v;
        for (v = 0; v < V; ++v) {
            AdjListNode *pCrawl = array[v].head;
            cout << "\n Vertices with Degree " << v << "\n head ";
            while (pCrawl) {
                cout << "-> " << pCrawl->data;
                pCrawl = pCrawl->next;
            }
            cout << "-> tail";
            cout << endl;
        }
    }

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

    vector<int> getEdges(int vertex) {
        vector<int> edges;
        AdjListNode *pCrawl = array[vertex].head;
        while (pCrawl) {
            edges.push_back(pCrawl->data);
            pCrawl = pCrawl->next;
        }
        return edges;
    }

    void genCompleteGraph(int V) {

        this->V = V;
        array = new AdjList[V];
        for (int i = 0; i < V; ++i) {
            array[i].head = NULL;
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

    void genCycleGraph(int V) {
        this->V = V;
        array = new AdjList[V];
        for (int i = 0; i < V; ++i) {
            array[i].head = NULL;
            array[i].tail = NULL;
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
    vector<int> genVector(int size) {
        vector<int> nums;
        for(int i = size-1;i>=0; i--){
            nums.push_back(i);
        }
        return nums;
    }

    int genSkewedNum(vector<int> nums){
        //set seed
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        //set generator
        static std::default_random_engine generator(seed);

        //generate skewed random number with smaller numbs being more likely
        std::discrete_distribution<int> distribution(nums.begin(), nums.end());
        return distribution(generator);

    }
    int genNormalNum(int size){
        //set seed
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        //set generator
        static std::default_random_engine generator(seed);

        //generate skewed random number with smaller numbs being more likely
        std::normal_distribution<double> distribution((size/2+1), (size/5));
        return distribution(generator);

    }
    int genRandomNum (int max)
    {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

        static std::default_random_engine generator(seed);
        std::uniform_int_distribution<int> distribution (0,max);
        return distribution(generator);
    }

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
                    int normalIndex = genNormalNum(nums.size()-1);

                    //make edge to go both ways
                    addEdge(enumerated_edges[normalIndex].first, enumerated_edges[normalIndex].second);
                    addEdge(enumerated_edges[normalIndex].second, enumerated_edges[normalIndex].first);
                    //remove edge from list of enumerated edges once it is added to the graph
                    enumerated_edges.erase(enumerated_edges.begin() + normalIndex);
                    nums.erase(nums.begin() + normalIndex);
                }
            }
        }
    }
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
