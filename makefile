make: dijkstra
dijkstra:
	g++ main.cpp util.cpp graph.cpp heap.cpp -std=c++11 -o dijkstra

