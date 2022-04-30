#include "Graph.h"
#include <random>

using namespace std;
using namespace std::chrono;

//https://www.sanfoundry.com/cpp-program-implement-adjacency-list/
// Add edge


int main() {
    int V = 25 ;
    Graph graph(V);
//    for(int i=0;i<1000;i++) {
//        cout << graph.genNormalNum(V)<<endl;
//    }
//    graph.genCycleGraph(V);
//    graph.genCompleteGraph(V);
    graph.genGraph(V,50,"RANDOM","YOURS");
    graph.printGraph();


    return 0;
}
