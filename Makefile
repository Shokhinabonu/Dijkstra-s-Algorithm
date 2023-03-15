
all: 
	g++ -Wall -g Graph.cpp GraphTests.cpp -std=c++14 -o graph-tests
	g++ -Wall -g Graph.cpp BetterPriorityQueue.cpp BPQTests.cpp -std=c++14 -o bpq-tests
	g++ -Wall -g Graph.cpp BetterPriorityQueue.cpp Dijkstra.cpp -std=c++14 -o dijkstra
run: 
	./dijkstra

try: all run