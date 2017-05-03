#ifndef HOLLOWHEAPGRAPH_H
#define HOLLOWHEAPGRAPH_H

#include <vector>
#include <map>
#include <queue>
#include <iostream>
#include "EdgeDistance.h"
#include "HollowHeap.h"
#include "memory_used.h"

namespace HollowHeap {

    class Graph {

        struct EdgeLink {
            U32 to;
            U32 weight;
        };

    public:
        Graph();    
        void setSize(U32 numberOfElements);    
        void set(U32 origin, U32 dest, U32 weight);    
        EdgeDistance dijkstra(unsigned long origin,  unsigned long dest);    
        unsigned long getNumberOfInserts();
        unsigned long getNumberOfDeletes();
        unsigned long getNumberOfUpdates();

    private:
        unsigned long m_numberOfElements;
        std::map<unsigned long, std::vector<EdgeLink> > m_graph;

        unsigned long n_inserts;
        unsigned long n_deletes;
        unsigned long n_updates;

        void m_clearCounters();

    public:
        U32 m_getHeigherVertice();
        
    };

};

#endif /*HOLLOWHEAPGRAPH_H*/
