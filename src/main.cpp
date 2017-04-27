#include "utils.h"
#include "Graph.h"
#include "read_dimacs.h"
#include <iostream>
#include <cassert>
#include <fstream>

int main(int argc, char** argv) {

    assert(argc >= 3);
    int origin = atoi(argv[1]);
    int dest = atoi(argv[2]);

    Graph g;
    if (argc > 3) {
        std::ifstream f(argv[3]);
        read_dimacs(f, g);
    }
    else {
        read_dimacs(std::cin, g);
    }
    
    U32 elapsed = 0;
    EdgeDistance ed;
    MeasureMS(&elapsed, ed = g.dijkstra(origin, dest));
    std::cout << ed << std::endl;

    return 0;
}