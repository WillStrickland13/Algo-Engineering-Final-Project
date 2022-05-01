//
// Created by William Strickland on 5/1/22.
//

#ifndef ASSIGNMENT2_VERTEX_H
#define ASSIGNMENT2_VERTEX_H
#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <random>
#include "Graph.h"
using namespace std;
using namespace std::chrono;
class Vertex{
private:
    int id;
    AdjList* edges;
    int degree;
    int color;


public:
    Vertex(int id, AdjList* edges, int degree, int color){
        this->id = id;
        this->edges = edges;
        this->degree = degree;
        this->color = color;
    }
};

#endif //ASSIGNMENT2_VERTEX_H
