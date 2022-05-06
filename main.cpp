#include "Graph.h"
#include <random>
#include "Runner.h"
using namespace std;
using namespace std::chrono;

//https://www.sanfoundry.com/cpp-program-implement-adjacency-list/


int main() {
    int V = 100;
    int E = 4000;
    Graph graph(V);
    // Create graph
    graph.genGraph(V,E,"RANDOM","YOURS");
    graph.printGraph();
    Runner runner(graph);
    runner.genDegreeList();
    runner.SLVO();
    return 0;
}
