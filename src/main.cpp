#include "Graph.h"
#include "HollowHeap.h"
#include "read_dimacs.h"
#include <iostream>
#include <assert.h>
#include <chrono>


int main(int argc, char** argv) {

    assert(argc == 3);
    int origin = atoi(argv[1]);
    int dest = atoi(argv[2]);

    Graph<HollowHeap> g;

    read_dimacs(std::cin, g);
    
    // inicio
    auto start = std::chrono::system_clock::now();
    EdgeDistance ed = g.dijkstra(origin, dest);
    auto end = std::chrono::system_clock::now();
    unsigned long elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << ed << std::endl;        

    return 0;
}