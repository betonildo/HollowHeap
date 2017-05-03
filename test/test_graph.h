#ifndef DIJKSTRA_TEST
#define DIJKSTRA_TEST

#include "BinaryHeapGraph.h"
#include "HollowHeapGraph.h"
#include "utils.h"
#include "definitions.h"
#include "memory_used.h"
#include "read_dimacs.h"
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

        const U32 MAX_I = 20;
        // fixed N
        U32 n = pow(2, MAX_I);
        HollowHeap::Graph hhg;
        hhg.setSize(n);

        BinaryHeap::Graph bhg;
        bhg.setSize(n);

        U32 connectionsCounter = 0;

        for (U32 i = 1; i < MAX_I; i++) {
            
            // define M
            U32 m = pow(2, i);
            U32 E = (n + m) * logBase(n, 2);

            // create and generate graphs
            addConnectionsToGraph(hhg, n, connectionsCounter, m);
            U32 hhg_time = 0;
            
            addConnectionsToGraph(bhg, n, connectionsCounter, m);
            U32 bhg_time = 0;

            connectionsCounter = m;

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

    static inline void testDijkstraVaringNFixedM(std::ostream& outTimesHHFile, std::ostream& outTimesBHFile, std::ostream& outIDUnmFile) {
        std::srand(time(0));

        // set headers
        outTimesHHFile << "# n x T /(n + m) log(n)" << std::endl;
        outTimesBHFile << "# n x T /(n + m) log(n)" << std::endl;
        outIDUnmFile << "# inserts, deletes, updates" << std::endl;

        const U32 MAX_I = 24;

        // fixed M
        HollowHeap::Graph hhg;
        BinaryHeap::Graph bhg;
        U32 nodeCounter = 0;
        U32 m = pow(2, MAX_I);

        for (U32 i = 11; i < MAX_I; i++) {
            
            // define M
            U32 n = pow(2, i);
            U32 E = (n + m) * logBase(n, 2);

            // create and generate graphs
            addNodesToGraph(hhg, nodeCounter, n, m);
            U32 hhg_time = 0;

            addNodesToGraph(bhg, nodeCounter, n, m);
            U32 bhg_time = 0;

            nodeCounter = n;

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
            outTimesHHFile << n << " " << HHFT << std::endl;
            outTimesBHFile << n << " " << BHFT << std::endl;
            outIDUnmFile << "HH " << bhg.getNumberOfInserts() << " " << bhg.getNumberOfDeletes() << " " << bhg.getNumberOfUpdates() << std::endl;
            outIDUnmFile << "BH " << hhg.getNumberOfInserts() << " " << hhg.getNumberOfDeletes() << " " << hhg.getNumberOfUpdates() << std::endl;
        }
    }

    static inline void testNYandUSAgraphs(std::ostream& outFile, const char* NYgraphPath, const char* USAgraphPath) {
        


        std::srand(time(0));


        const U32 max_i = 30;

        {
            U32 time_sum = 0;
            U32 mem_sum = 0;
            HollowHeap::Graph hhg;
            FILE* f = fopen(NYgraphPath, "r");
            read_dimacs(f, hhg);
            fclose(f);

            U32 heighestVertice = hhg.m_getHeigherVertice();

            outFile << "# " << NYgraphPath << ": " << "time and memory" << std::endl;

            for(U32 i = 0; i < max_i; i++) {

                U32 timev = 0;
                U32 v1 = -1;
                U32 v2 = -1;

                while(v1 == v2) {
                    v1 = std::rand() % heighestVertice + 1;
                    v2 = std::rand() % heighestVertice + 1;
                }

                MeasureMS(&timev, {
                    U32 mem_start = memory_used(false);
                    std::cout << hhg.dijkstra(v1, v2) << std::endl;
                    U32 mem_end = memory_used(false);
                    mem_sum += MAX(mem_start, mem_end) - MIN(mem_end, mem_start);
                });

                time_sum += timev;
            }

            outFile << (double)time_sum/(double)max_i << " " << (double)mem_sum/(double)max_i << std::endl;
        }

        {
            U32 time_sum = 0;
            U32 mem_sum = 0;
            HollowHeap::Graph hhg;
            FILE* f = fopen(USAgraphPath, "r");
            read_dimacs(f, hhg);
            fclose(f);

            U32 heighestVertice = hhg.m_getHeigherVertice();

            outFile << "# " << USAgraphPath << ": " << "time and memory" << std::endl;

            for(U32 i = 0; i < max_i; i++) {

                U32 timev = 0;
                U32 v1 = -1;
                U32 v2 = -1;

                while(v1 == v2) {
                    v1 = std::rand() % heighestVertice + 1;
                    v2 = std::rand() % heighestVertice + 1;
                }

                MeasureMS(&timev, {
                    U32 mem_start = memory_used(false);
                    std::cout << hhg.dijkstra(v1, v2) << std::endl;
                    U32 mem_end = memory_used(false);
                    mem_sum += MAX(mem_start, mem_end) - MIN(mem_end, mem_start);
                });

                time_sum += timev;
            }

            outFile << (double)time_sum/(double)max_i << " " << (double)mem_sum/(double)max_i << std::endl;
        }
    }

    template<typename Graph>
    static inline void generateGraph(Graph& g, U32 n, U32 m) {
        
        std::srand(time(0));

        for (U32 i = 1, j = 1; i <= n && j <= m + 1; i++, j++) {
            if (i != j) g.set(i, j, std::rand() % 1000);
        }
    }
 
    template<typename Graph>
    static inline void addConnectionsToGraph(Graph& g, U32 n, U32 oldM, U32 newM) {
        std::srand(time(0));

        U32 Mrange = newM - oldM + 1;
        // U32 mem_start = memory_used(false);
        for (U32 i = 1, j = oldM; i <= n && j <= Mrange; i++, j++) {

            if (i != j) g.set(i, j, std::rand() % 1000);
            else g.set(i, j, 0);
        }

        // U32 mem_end = memory_used(false);
        // std::cout << "Graph:" << std::endl;
        // std::cout << "Memory Start: " << mem_start << std::endl;
        // std::cout << "Memory End  : " << mem_end   << std::endl;
        // std::cout << "Memory Used : " << MAX(mem_start, mem_end) - MIN(mem_start, mem_end) << std::endl;
    }

    template<typename Graph>
    static inline void addNodesToGraph(Graph& g, U32 oldN, U32 newN, U32 m) {
        std::srand(time(0));

        U32 Nrange = newN - oldN + 1;
        // U32 mem_start = memory_used(false);
        for (U32 i = 1, j = oldN; i <= Nrange && j <= m; i++, j++) {

            if (i != j) g.set(i, j, std::rand() % 1000);
            else g.set(i, j, 0);
        }

        // U32 mem_end = memory_used(false);
        // std::cout << "Graph:" << std::endl;
        // std::cout << "Memory Start: " << mem_start << std::endl;
        // std::cout << "Memory End  : " << mem_end   << std::endl;
        // std::cout << "Memory Used : " << MAX(mem_start, mem_end) - MIN(mem_start, mem_end) << std::endl;
    }
};

#endif /*DIJKSTRA_TEST*/