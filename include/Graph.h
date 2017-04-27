#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <map>
#include <queue>
#include <iostream>
#include "EdgeDistance.h"
#include "HollowHeap.h"

class Graph {

    struct Edge {
        U32 to;
        U32 weight;
    };

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
    
    EdgeDistance dijkstra(unsigned long origin,  unsigned long dest) {
        
        // instantiate distances calculated
        EdgeDistance distances[m_numberOfElements];

        // clear insert, update and delete-min counters
        m_clearCounters();
        
        // The distance to it self is 0
        distances[origin].distanceTo = 0;
        distances[origin].infinity = false;
        
        // if some over or under flow occurs, the distance is infinity
        if (dest == origin) return distances[dest];
        if (dest >= m_numberOfElements || origin >= m_numberOfElements || dest < 0 || origin < 0) return EdgeDistance();
        
        // instantiate the heap and insert the vertice origin as starting point
        Node* heap = make_heap(make_element(origin), 0);
        
        while (findmin(heap) != NULL) {
            
            // get next and delete the minimun (deletemin* variant name)
            n_deletes += 1;
            Item* e = findmin(heap);
            unsigned long u = e->vertice;
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
                        if (!heap) heap = make_heap(make_element(v), cost);
                        else heap = insert(make_element(v), cost, heap);
                    }
                    // else if we already have an instance of the vertice on the heap,
                    // we must update the distance to origin reling on distances pre
                    // calculated.
                    else if (cost < distances[v].distanceTo) {
                        distances[v].distanceTo = cost;
                        n_updates += 1;
                        if (!heap) heap = make_heap(make_element(v), cost);
                        else heap = decrease_key(e, cost, heap);
                    }
                }
            }
            
        }
        
        return distances[dest];
    }

    unsigned long heigherVertice() {
        return m_graph.rbegin()->first;
    }

    void printNeiborsOf(U32 ni) {
        for(auto neibor : m_graph[ni]) {
            printf("%d\n", neibor.to);
        }
    }

    bool* visiteds = NULL;

    void print(unsigned ni) {
        visiteds = new bool[m_numberOfElements];
        for(U32 i = 0; i < m_numberOfElements; i++) 
            visiteds[i] = false;

        std::queue<U32> qNodes;
        qNodes.push(ni);
        while(!qNodes.empty()) {
            ni = qNodes.front();
            qNodes.pop();
            printf("%d ", ni);
            visiteds[ni] = true;
            for(auto neibor : m_graph[ni]) {
                printf("-(%d)-> ", neibor.weight);
                if (!visiteds[neibor.to]){
                    visiteds[neibor.to] = true;
                    printf("%d ", neibor.to);
                    qNodes.push(neibor.to);
                }
            }
            printf("\n");       
        }
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
