#ifndef DIJKSTRA_TEST
#define DIJKSTRA_TEST

#include "BinaryHeapGraph.h"
#include "HollowHeapGraph.h"
#include "utils.h"
#include "definitions.h"
#include "memory_used.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <math.h>

struct DijkstraTest {

    static inline void testDijkstraFixedNVaringM(std::ostream& outTimesHHFile, std::ostream& outTimesBHFile, std::ostream& outIDUnmFile) {
        std::srand(time(0));

        // set headers
        outTimesHHFile << "# m x T /(n + m) log(n)" << std::endl;
        outTimesBHFile << "# m x T /(n + m) log(n)" << std::endl;
        outIDUnmFile << "# inserts, deletes, updates" << std::endl;

        const U32 MAX_I = 15;
        // fixed N        
        U32 n = pow(2, MAX_I);
        HollowHeap::Graph hhg;
        hhg.setSize(n);

        BinaryHeap::Graph bhg;
        bhg.setSize(n);

        U32 currentConnections = 0;

        for (U32 i = 1; i <= MAX_I; i++) {
            
            // define M
            U32 m = pow(2, i);
            U32 E = (n + m) * logBase(n, 2);

            // create and generate graphs
            std::cout << "Starting to generate a graph with n = " << n << " and m = " << m << std::endl;
            //generateGraph<HollowHeap::Graph>(hhg, n, m);
            addConnectionsToGraph<HollowHeap::Graph>(hhg, n, currentConnections, m);
            U32 hhg_time = 0;
            
            // generateGraph<BinaryHeap::Graph>(bhg, n, m);
            addConnectionsToGraph<BinaryHeap::Graph>(bhg, n, currentConnections, m);
            U32 bhg_time = 0;
            std::cout << "Finished generating graphs" << std::endl;

            // set next iteration connections
            currentConnections = m;

            // define search and time for elapsed time register
            U32 origin = -1;
            U32 dest = -1;
            
            // define max iteration
            U32 time_i_max = 1;

            for(U32 time_i = 0; time_i < time_i_max; time_i++) {

                // define origin and destiny to search into the graph
                while(origin == dest) {
                    origin = std::rand() % n;
                    dest = std::rand() % n;

                    std::cout << "Generating origin and destiny respectively " << origin << " and " << dest << std::endl;
                }

                // measure time spent on search shortest path
                U32 temp_time_measure = 0;
                MeasureMS(&temp_time_measure, {
                    // U32 mem_start = memory_used(false);
                    bhg.dijkstra(origin, dest);
                    // U32 mem_end = memory_used(false);
                    // std::cout << "Binary Heap Dijkstra:" << std::endl;
                    // std::cout << "Memory Start: " << mem_start << std::endl;
                    // std::cout << "Memory End  : " << mem_end   << std::endl;
                    // std::cout << "Memory Used : " << MAX(mem_start, mem_end) - MIN(mem_start, mem_end) << std::endl;
                });
                bhg_time += temp_time_measure;

                temp_time_measure = 0;
                MeasureMS(&temp_time_measure, {
                    // U32 mem_start = memory_used(false);
                    hhg.dijkstra(origin, dest);
                    // U32 mem_end = memory_used(false);
                    // std::cout << "Hollow Heap Dijkstra:" << std::endl;
                    // std::cout << "Memory Start: " << mem_start << std::endl;
                    // std::cout << "Memory End  : " << mem_end   << std::endl;
                    // std::cout << "Memory Used : " << MAX(mem_start, mem_end) - MIN(mem_start, mem_end) << std::endl;
                });
                
                hhg_time += temp_time_measure;
            }

            // T /(n + m) log(n)
            double HHFT = (double)hhg_time / (double) time_i_max / (double) E;
            double BHFT = (double)bhg_time / (double) time_i_max / (double) E;

            // store into files
            outTimesHHFile << m << " " << HHFT << std::endl;
            outTimesBHFile << m << " " << BHFT << std::endl;
            outIDUnmFile << "HH " << bhg.getNumberOfInserts() << " " << bhg.getNumberOfDeletes() << " " << bhg.getNumberOfUpdates() << std::endl;
            outIDUnmFile << "BH " << hhg.getNumberOfInserts() << " " << hhg.getNumberOfDeletes() << " " << hhg.getNumberOfUpdates() << std::endl;

            std::cout << "Finished "<< i << " iteration" << std::endl;
        }
    }   

    static inline void testDijkstraVaringNFixedM(std::ostream& outTimesHHFile, std::ostream& outTimesBHFile, std::ostream& outIDUnmFile) {
        std::srand(time(0));

        // set headers
        outTimesHHFile << "# m x T /(n + m) log(n)" << std::endl;
        outTimesBHFile << "# m x T /(n + m) log(n)" << std::endl;
        outIDUnmFile << "# inserts, deletes, updates" << std::endl;

        const U32 MAX_I = 15;

        // fixed M
        U32 m = pow(2, MAX_I);

        for (U32 i = 11; i <= MAX_I; i++) {
            
            // define M
            U32 n = pow(2, i);
            U32 E = (n + m) * logBase(n, 2);

            // create and generate graphs
            HollowHeap::Graph hhg;
            hhg.setSize(n);
            generateGraph<HollowHeap::Graph>(hhg, n, m);
            U32 hhg_time = 0;
            
            BinaryHeap::Graph bhg;
            bhg.setSize(n);
            generateGraph<BinaryHeap::Graph>(bhg, n, m);
            U32 bhg_time = 0;

            // define search and time for elapsed time register
            U32 origin = -1;
            U32 dest = -1;
            
            // define max iteration
            U32 time_i_max = 30;

            for(U32 time_i = 0; time_i < time_i_max; time_i++) {

                // define origin and destiny to search into the graph
                while(origin == dest) {
                    origin = std::rand() % n;
                    dest = std::rand() % n;
                }

                // measure time spent on search shortest path
                U32 temp_time_measure = 0;
                MeasureMS(&temp_time_measure, {
                    bhg.dijkstra(origin, dest);
                });

                bhg_time += temp_time_measure;

                temp_time_measure = 0;
                MeasureMS(&temp_time_measure, {
                    hhg.dijkstra(origin, dest);
                });

                hhg_time += temp_time_measure;
            }

            // T /(n + m) log(n)
            double HHFT = (double)hhg_time / (double) time_i_max / (double) E;
            double BHFT = (double)bhg_time / (double) time_i_max / (double) E;

            // store into files
            outTimesHHFile << m << " " << HHFT << std::endl;
            outTimesBHFile << m << " " << BHFT << std::endl;
            outIDUnmFile << "HH " << bhg.getNumberOfInserts() << " " << bhg.getNumberOfDeletes() << " " << bhg.getNumberOfUpdates() << std::endl;
            outIDUnmFile << "BH " << hhg.getNumberOfInserts() << " " << hhg.getNumberOfDeletes() << " " << hhg.getNumberOfUpdates() << std::endl;
        }
    }

    template<typename Graph>
    static inline void generateGraph(Graph& g, U32 n, U32 m) {
        
        std::srand(time(0));

        for (U32 i = 1; i <= n; i++) {
            for (U32 j = 1; j <= n && j <= m + 1; j++) {
                if (i != j) g.set(i, j, std::rand() % 1000);
            }
        }
    }
 
    template<typename Graph>
    static inline void addConnectionsToGraph(Graph& g, U32 n, U32 oldM, U32 newM) {
        std::srand(time(0));

        U32 mem_start = memory_used(false);
        for (U32 i = 1; i <= n; i++) {
            for (U32 j = oldM; j <= n && j <= newM + 1; j++) {
                if (i != j) g.set(i, j, std::rand() % 1000);
            }
        }

        U32 mem_end = memory_used(false);
        std::cout << "Graph:" << std::endl;
        std::cout << "Memory Start: " << mem_start << std::endl;
        std::cout << "Memory End  : " << mem_end   << std::endl;
        std::cout << "Memory Used : " << MAX(mem_start, mem_end) - MIN(mem_start, mem_end) << std::endl;
    }
};

#endif /*DIJKSTRA_TEST*/