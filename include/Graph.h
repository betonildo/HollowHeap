#include <vector>
#include <map>

#include <iostream>
#include "Edge.h"
#include "HollowHeap.h"

#ifndef GRAPH_H
#define GRAPH_H

class Graph {

public:
    Graph() {
        m_graph.clear();
    }

    void setHeapAridity(unsigned long aridity) {
        m_aridity = aridity;
    }
    
    void setSize(unsigned long numberOfElements) {
        m_numberOfElements = numberOfElements + 1;
    }
    
    void set(unsigned long origin, unsigned long dest, unsigned long weight) {
        m_graph[origin].push_back({dest, weight});
    }
    
    EdgeDistance dijkstra(unsigned long origin,  unsigned long dest) {
        
        // instantiate distances calculated
        EdgeDistance distances[m_numberOfElements];

        // if some over or under flow occurs, the distance is infinity
        if (dest >= m_numberOfElements || origin >= m_numberOfElements || dest < 0 || origin < 0) return distances[0];
        
        // clear insert, update and delete-min counters
        m_clearCounters();
        
        // The distance to it self is 0
        distances[origin].distanceTo = 0;
        
        // instantiate the heap and insert the vertice origin as starting point
        Item* e = make_element(0);
        Node* heap = make_heap(e, origin);
        
        while (findmin(heap) != NULL) {
            
            // get next and delete the minimun (deletemin* variant name)
            n_deletes += 1;
            Item* e = findmin(heap);
            unsigned long u = e->distance;
            heap = delete_min(heap);
            
            // if this vertice was not visited yet, look for each neibor 
            // and verify the distance to the origin
            if (distances[u].visited == false) {                
                distances[u].visited = true;
                
                for(auto neibor : m_graph[u]) {
                    
                    unsigned long v = neibor.to;
                    unsigned long w = neibor.weight;
                    unsigned long cost = distances[u].distanceTo + w;
                    // if the current distance is infinity (not calculated yet)
                    // and the cost is less than infinity we try the path by this
                    // vertice.
                    if (distances[v].infinity && cost < distances[v].distanceTo) {
                        distances[v].infinity = false;
                        distances[v].distanceTo = cost;
                        n_inserts += 1;
                        heap = insert(make_element(cost), v, heap);
                    }
                    // else if we already have an instance of the vertice on the heap,
                    // we must update the distance to origin reling on distances pre
                    // calculated.
                    else if (cost < distances[v].distanceTo) {
                        distances[v].distanceTo = cost;
                        n_updates += 1;
                    }
                }
            }
        }
        
        return distances[dest];
    }

    unsigned long heigherVertice() {
        return m_graph.rbegin()->first;
    }

    void print(unsigned ni) {
        
        printf("%d ", ni);
        for(auto neibor : m_graph[ni]) {
            printf("-(%ld)-> ", neibor.weight);
            print(neibor.to);
        }

        if (m_graph[ni].size() == 0)
            printf("\n");
    }



    unsigned long getNumberOfInserts() {
        return n_inserts;
    }

    unsigned long getNumberOfDeletes() {
        return n_deletes;
    }

    unsigned long getNumberOfUpdates() {
        return n_updates;
    }

private:
    unsigned long m_aridity;
    unsigned long m_numberOfElements;
    std::map<unsigned long, std::vector<Edge> > m_graph;

    unsigned long n_inserts;
    unsigned long n_deletes;
    unsigned long n_updates;

    void m_clearCounters() {
        n_inserts = n_deletes = n_updates = 0;
    }
    
};

#endif /*GRAPH_H*/
