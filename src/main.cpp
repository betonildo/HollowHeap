#include "Graph.h"
#include "read_dimacs.h"
#include <iostream>
#include <cassert>
#include <chrono>
#include <fstream>

int main(int argc, char** argv) {

    // assert(argc >= 3);
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
    
    // inicio
    auto start = std::chrono::system_clock::now();
    EdgeDistance ed = g.dijkstra(origin, dest);
    auto end = std::chrono::system_clock::now();
    U32 elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << ed << std::endl;        

    return 0;
}