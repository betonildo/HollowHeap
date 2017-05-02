#ifndef READ_DIMACS_H
#define READ_DIMACS_H

#include <sstream>
#include <iostream>
#include <fstream>

void read_dimacs(std::istream& in, HollowHeap::Graph& g);
void read_dimacs(char* path, HollowHeap::Graph& g);

void read_dimacs(char* path, HollowHeap::Graph& g) {
    std::ifstream f(path);
    read_dimacs(f, g);
}

void read_dimacs(std::istream& in, HollowHeap::Graph& g) {
    
    unsigned int n, m;
    std::string line="", dummy;
    while (line.substr(0,4) != "p sp")
        getline(in,line);
    
    // (1) get nodes and edges
    std::stringstream linestr;
    linestr.str(line);
    linestr >> dummy >> dummy >> n >> m;
    g.setSize(n);
    
    unsigned i = 0;
    while (i < m) {
        
        getline(in, line);
        
        if (line.substr(0,2) == "a ") {
            std::stringstream arc(line);
            unsigned u,v,w;
            char ac;
            arc >> ac >> u >> v >> w;
            // std::cout << u << " " << v << " " << w << std::endl;
            // processar arco (u,v) com peso w
            g.set(u, v, w);
            i++;
        }
    }
}

#endif /*READ_DIMACS_H*/