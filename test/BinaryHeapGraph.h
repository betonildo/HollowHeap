#ifndef BINARYHEAPGRAPH_H
#define BINARYHEAPGRAPH_H

#include <map>
#include <vector>
#include <iostream>
#include "NHeap.h"
#include "Edge.h"
#include "definitions.h"
#include "EdgeDistance.h"

namespace BinaryHeap {
    class Graph {

    public:

        Graph() {
            m_graph.clear();
        }
        
        void setSize(U32 numberOfElements) {
            m_numberOfElements = numberOfElements + 1;
        }
        
        void set(U32 origin, U32 dest, U32 weight) {
            m_graph[origin].push_back({dest, weight});
        }
        
        EdgeDistance dijkstra(U32 origin,  U32 dest) {

            // clear counters
            m_clearCounters();

            // instantiate distances calculated
            EdgeDistance* distances = new EdgeDistance[m_numberOfElements];

            // The distance to it self is 0
            distances[origin].distanceTo = 0;
            distances[origin].infinity = false;

            // if some over or under flow occurs, the distance is infinity
            if (dest == origin) {
                EdgeDistance result = distances[dest];
                delete[] distances;
                return result;
            }
            if (dest >= m_numberOfElements || origin >= m_numberOfElements) return EdgeDistance();
            
            // instantiate the heap and insert the vertice origin as starting point
            NHeap<Edge> edgesHeap(2);
            edgesHeap.insert({origin, 0});
            
            while (!edgesHeap.empty()) {
                
                // get next and delete the minimun (deletemin* variant name)
                n_deletes += 1;
                Edge e = edgesHeap.getNext();
                U32 u = e.to;
                
                // if this vertice was not visited yet, look for each neibor 
                // and verify the distance to the origin
                if (distances[u].visited == false) {                
                    distances[u].visited = true;
                    
                    for(auto neibor : m_graph[u]) {
                        
                        U32 v = neibor.to;
                        U32 w = neibor.weight;
                        U32 cost = distances[u].distanceTo + w;
                        // if the current distance is infinity (not calculated yet)
                        // and the cost is less than infinity we try the path by this
                        // vertice.
                        if (distances[v].infinity && cost < distances[v].distanceTo) {
                            distances[v].infinity = false;
                            distances[v].distanceTo = cost;
                            n_inserts += 1;
                            edgesHeap.insert({v, cost});
                        }
                        // else if we already have an instance of the vertice on the heap,
                        // we must update the distance to origin reling on distances pre
                        // calculated.
                        else if (cost < distances[v].distanceTo) {
                            distances[v].distanceTo = cost;
                            n_updates += 1;
                            edgesHeap.update({v, cost});
                        }
                    }
                }
            }
            EdgeDistance result = distances[dest];
            delete[] distances;
            return result;
        }

        U32 getNumberOfInserts() {
            return n_inserts;
        }

        U32 getNumberOfDeletes() {
            return n_deletes;
        }

        U32 getNumberOfUpdates() {
            return n_updates;
        }

    private:
        U32 m_numberOfElements;
        std::map<U32, std::vector<Edge> > m_graph;

        U32 n_inserts;
        U32 n_deletes;
        U32 n_updates;

        void m_clearCounters() {
            n_inserts = n_deletes = n_updates = 0;
        }

    };

};

#endif /*BINARYHEAPGRAPH_H*/
