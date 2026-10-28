all:
	g++ -Wall -g Graph.cpp GraphTests.cpp -o graph-tests
	g++ -Wall -g Graph.cpp BetterPriorityQueue.cpp BPQTests.cpp -o bpq-tests
	g++ -Wall -g Graph.cpp BetterPriorityQueue.cpp Dijkstra.cpp DijkstraTests.cpp -o dijkstra

clean:
	rm -f graph-tests bpq-tests dijkstra *.o

.PHONY: all clean
