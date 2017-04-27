#include "utils.h"
#include "Graph.h"
#include "read_dimacs.h"
#include <iostream>
#include <cassert>

#include <unistd.h>

int main(int argc, char** argv) {

    assert(argc >= 3);
    int origin = atoi(argv[1]);
    int dest = atoi(argv[2]);

    Graph g;
    if (argc > 3) read_dimacs(argv[3], g);
    else read_dimacs(std::cin, g);

    U32 elapsed = 0;
    EdgeDistance ed;
    MeasureMS(&elapsed, ed = g.dijkstra(origin, dest));
    std::cout << ed << std::endl;
    // std::cout << elapsed << " ms" << std::endl;
    return 0;
}