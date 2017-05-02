#include "definitions.h"
#include "memory_used.h"
#include "utils.h"
#include "NHeap.h"
#include "Edge.h"
#include "HollowHeap.h"
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <time.h>
#include <math.h>

#define TIMES_RUN_TESTS 10

using namespace std;

class NHeapTest {

public:


    static inline void testInsert(ostream& outSwapsFile, ostream& outTimesFile) {

        // insert headers on data files
        outSwapsFile << "#binary heap x hollow heap" << std::endl;
        outTimesFile << "#binary heap x hollow heap" << std::endl;

        // start random seed
        std::srand(time(0));

        for (U32 i = 0; i <= 23; i++) {

            // define n insertions
            U32 n = pow(2, i) - 1;

            // create hollow heap
            U32 hh_swaps = 0;
            U32 hh_times = 0;
            Node* hh = make_heap(make_element(0), 0);

            // create binary heap
            U32 bh_swaps = 0;
            U32 bh_times = 0;
            NHeap<Edge> bh(2);
            bh.setCapacity(n);

            // measure time insertion on hollow heap
            MeasureMS(&hh_times, {
                // insert elements in both heaps
                for (U32 keycount = n; keycount >=1; keycount--) {
                    // insert comparison key into hollow heap
                    hh = insert(make_element(keycount), (U32)std::rand(), hh, &hh_swaps);
                }
            });

            // measure time insertion on binary heap
            MeasureMS(&bh_times, {
                // insert elements in both heaps
                for (U32 keycount = n; keycount >=1; keycount--) {
                    // insert comparison key into binary heap
                    bh_swaps += bh.insert({keycount, (U32)std::rand()});
                }
            });

            // out put their swaps and times
            outSwapsFile << bh_swaps << " " << hh_swaps << std::endl;
            outTimesFile << bh_times << " " << hh_times << std::endl;
        }
    }

    static inline void testUpdate(ostream& outSwapsFile, ostream& outTimesFile) {

        // insert headers
        outSwapsFile << "#binary heap x hollow heap" << std::endl;
        outTimesFile << "#binary heap x hollow heap" << std::endl;

        std::srand(time(0));
        U32 max_i = 15;

        for (U32 i = 1; i <= max_i; i++) {

            // define first number of insertions
            U32 _2_p_i_m_1 = pow(2, i) - 1;
            U32 values1 = pow(2, i) + 1;

            // define second number of insertions
            U32 _2_p_i = pow(2, i);
            U32 values2 = pow(2, i) + 2;

            // define number of updates
            U32 updatevalue = pow(2, i) + 1 - i;
            // start key to update
            U32 keystartmark = _2_p_i_m_1;

            // create hollow heap
            U32 hh_swaps = 0;
            U32 hh_times = 0;
            Node* hh = make_heap(make_element(0), 0);

            // create binary heap
            U32 bh_swaps = 0;
            U32 bh_times = 0;
            NHeap<Edge> bh(2);
            bh.setCapacity(_2_p_i_m_1 + _2_p_i);


            // insert the first lotation
            for (U32 keycount = 1; keycount <= _2_p_i_m_1; keycount++) {
                bh.insert({keycount, values1});
                hh = insert(make_element(keycount), values1, hh);
            }

            // insert the second lotation
            for (U32 keycount = 1; keycount <= _2_p_i; keycount++) {
                bh.insert({keycount + keystartmark, values2});
                hh = insert(make_element(keycount + keystartmark), values2, hh);
            }

            // set count down value
            U32 valueCountDown = updatevalue;

            // measure time to decrease_key
            MeasureMS(&hh_times, {
                // update values
                for (U32 keycount = _2_p_i; keycount >= 1 ; keycount--) {
                    hh = decrease_key(make_element(keycount + keystartmark), valueCountDown, hh, &hh_swaps);
                    valueCountDown -= 1;
                }
            });

            // reset count down value
            valueCountDown = updatevalue;

            // measure time to update
            MeasureMS(&bh_times, {
                // update values
                for (U32 keycount = _2_p_i; keycount >= 1 ; keycount--) {
                    bh_swaps += bh.update({keycount + keystartmark, valueCountDown});
                    valueCountDown -= 1;
                }
            });
            
            // out put their swaps and times
            outSwapsFile << bh_swaps << " " << hh_swaps << std::endl;
            outTimesFile << bh_times << " " << hh_times << std::endl;
        }
    }

    static inline void testDeletemin(ostream& outSwapsFile, ostream& outTimesFile){

        // insert headers on data files
        outSwapsFile << "#binary heap x hollow heap" << std::endl;
        outTimesFile << "#binary heap x hollow heap" << std::endl;

        std::srand(time(0));
        U32 max_i = 20;

        for (U32 i = 1; i <= max_i; i++) {

            U32 n = pow(2, i) - 1;

            U32 n_deletes = pow(2, i - 1);

            // create hollow heap
            U32 hh_swaps = 0;
            U32 hh_times = 0;
            Node* hh = make_heap(make_element(0), 0);

            // create binary heap
            U32 bh_swaps = 0;
            U32 bh_times = 0;
            NHeap<Edge> bh(2);
            bh.setCapacity(n);

            // start inserting key and values to heaps
            for (U32 keycount = 1;keycount <= n; keycount++) {

                U32 key = std::rand();
                U32 value = std::rand();

                hh = insert(make_element(key), value, hh);
                bh.insert({key, value});
            }

            // delete min from hollow heap
            MeasureMS(&hh_swaps, {
                for (U32 keycount = 1; keycount <= n_deletes; keycount++) {
                    hh = delete_min(hh, &hh_swaps);
                }
            });

            // delete min from binary heap
            MeasureMS(&bh_swaps, {
                for (U32 keycount = 1; keycount <= n_deletes; keycount++) {
                    bh.getNext(bh_swaps);
                }
            });

            // out put their swaps and times
            outSwapsFile << bh_swaps << " " << hh_swaps << std::endl;
            outTimesFile << bh_times << " " << hh_times << std::endl;
        }
    }
};
