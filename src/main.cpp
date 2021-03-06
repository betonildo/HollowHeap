#include "utils.h"
#include "HollowHeapGraph.h"
#include "read_dimacs.h"
#include <iostream>
#include <cassert>

#include <unistd.h>

int main(int argc, char** argv) {

    assert(argc >= 3);
    int origin = atoi(argv[1]);
    int dest = atoi(argv[2]);

    HollowHeap::Graph g;
    if (argc > 3) {
        FILE* f = fopen(argv[3], "r");
        read_dimacs(f, g);
    }
    else read_dimacs(stdin, g);

    U32 elapsed = 0;
    EdgeDistance ed;
    MeasureMS(&elapsed, ed = g.dijkstra(origin, dest));
    std::cout << ed << std::endl;
    // std::cout << elapsed << " ms" << std::endl;
    return 0;
}