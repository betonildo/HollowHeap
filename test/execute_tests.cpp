
#include <fstream>
#include "test_graph.h"
#include "test_heap.h"
#include <iostream>

int main(int argc, char** argv) {
    std::string arg;
    arg.assign(argv[1]);

    if (arg == "h_insert") {
        std::ofstream insert_swaps("output/heaps_insert_comparison_swaps.dat");
        std::ofstream insert_times("output/heaps_insert_comparison_times.dat");
        NHeapTest::testInsert(insert_swaps, insert_times);
    }

    if (arg == "h_update") {
        std::ofstream update_swaps("output/heaps_update_comparison_swaps.dat");
        std::ofstream update_times("output/heaps_update_comparison_times.dat");
        NHeapTest::testUpdate(update_swaps, update_times);
    }

    if (arg == "h_deletemin") {
        std::ofstream deletemin_swaps("output/heaps_deletemin_comparison_swaps.dat");
        std::ofstream deletemin_times("output/heaps_deletemin_comparison_times.dat");
        NHeapTest::testDeletemin(deletemin_swaps, deletemin_times);
    }

    if (arg == "dijkstra") {
        std::ofstream dijkstra_timeshh_m("output/dijkstra_timeshh_m.dat");
        std::ofstream dijkstra_timesbh_m("output/dijkstra_timesbh_m.dat");
        std::ofstream dijkstra_IDUnm_m("output/dijkstra_IDUnm_m.dat");
        DijkstraTest::testDijkstraFixedNVaringM(dijkstra_timeshh_m, dijkstra_timesbh_m, dijkstra_IDUnm_m);

        std::ofstream dijkstra_timeshh_n("output/dijkstra_timeshh_n.dat");
        std::ofstream dijkstra_timesbh_n("output/dijkstra_timesbh_n.dat");
        std::ofstream dijkstra_IDUnm_n("output/dijkstra_IDUnm_n.dat");
        DijkstraTest::testDijkstraVaringNFixedM(dijkstra_timeshh_n, dijkstra_timesbh_n, dijkstra_IDUnm_m);
    }

    return 0;
}