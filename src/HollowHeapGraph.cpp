#include "HollowHeapGraph.h"

namespace HollowHeap {

    Graph::Graph() {
        m_graph.clear();
    }

    void Graph::setSize(U32 numberOfElements) {
        m_numberOfElements = numberOfElements + 1;
    }

    void Graph::set(U32 origin, U32 dest, U32 weight) {
        m_graph[origin].push_back({dest, weight});
    }

    EdgeDistance Graph::dijkstra(unsigned long origin,  unsigned long dest) {
        
        // clear insert, update and delete-min counters
        m_clearCounters();
        U32 heigherVertice = MAX(m_getHeigherVertice() + 1, m_numberOfElements);

        // instantiate distances calculated
        // EdgeDistance* distances = new EdgeDistance[m_numberOfElements];
        std::vector<EdgeDistance> distances;
        distances.resize(heigherVertice);

        // if some over or under flow occurs, the distance is infinity
        if (dest == origin) {
            EdgeDistance result;
            result.distanceTo = 0;
            result.infinity = false;
            result.visited = true;
            // delete[] distances;
            return result;
        }
        
        if (dest > heigherVertice || origin > heigherVertice) {
            // delete[] distances;
            return EdgeDistance();
        }

        // The distance to it self is 0
        distances[origin].distanceTo = 0;
        distances[origin].infinity = false;
        
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

        // finalize deleting the heap
        heap = delete_heap(heap);
        EdgeDistance result = distances[dest];
        // delete[] distances;

        return result;
    }

    unsigned long Graph::getNumberOfInserts() {
        return n_inserts;
    }

    unsigned long Graph::getNumberOfDeletes() {
        return n_deletes;
    }

    unsigned long Graph::getNumberOfUpdates() {
        return n_updates;
    }

    void Graph::m_clearCounters() {
        n_inserts = n_deletes = n_updates = 0;
    }

    U32 Graph::m_getHeigherVertice() {
        U32 heigher = 0;
        for (auto& ve : m_graph) {
            
            if (ve.first > heigher) heigher = ve.first;
            for (EdgeLink& e : ve.second) {
                if (e.to > heigher) heigher = e.to;
            }
        }
        return heigher;
    }
};
