#include "Graph.h"


Graph::Graph(int V) {
	this->V = V;
	adjacencyList = new List<int>[V];
}


Graph::~Graph() {
	delete[] adjacencyList;
}


void Graph::addEdge(int v, int w) {
	adjacencyList[v].append(w);
}


List<int>* Graph::getAdjacencyList() {
	return adjacencyList;
}


int Graph::getV() {
	return V;
}
