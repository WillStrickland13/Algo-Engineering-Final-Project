#include "Graph.h"
#include <random>
#include "Runner.h"
using namespace std;
using namespace std::chrono;

//https://www.sanfoundry.com/cpp-program-implement-adjacency-list/


int main() {
    int V = 5 ;
    int E = 7;
    Graph graph(V);
    // Create graph
    graph.genGraph(V,E,"RANDOM","UNIFORM");
    graph.printGraph();
    Runner runner(graph);
    runner.genDegreeList();
    runner.deleteSmallestDegree();
    graph.printGraph();

    return 0;
}
