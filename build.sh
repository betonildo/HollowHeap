#g++ -Wall -std=c++11 src/* -o dijkstra -I"include/"
g++ -O3 -Wall -std=c++11 src/HollowHeapGraph.cpp src/HollowHeap.cc src/main.cpp -o dijkstra -I"include/" -lm
g++ -O3 -Wall -std=c++11 src/memory_used.cpp src/HollowHeapGraph.cpp src/HollowHeap.cc test/execute_tests.cpp -o test/execute_tests -I"include/" -lm