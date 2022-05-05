#include "Graph.h"
#include <random>
#include "Runner.h"
using namespace std;
using namespace std::chrono;

//https://www.sanfoundry.com/cpp-program-implement-adjacency-list/


int main() {
    int V = 10;
    int E = 20;
    Graph graph(V);
    // Create graph
    graph.genGraph(V,E,"RANDOM","UNIFORM");
    graph.printGraph();
    Runner runner(graph);
    runner.genDegreeList();
    runner.deleteAll();
    cout<<"Printing colors"<<endl;
    runner.printColors();
    return 0;
}
