#include "Graph.h"


Graph::Graph(int citiesCount)
	: citiesCount{ citiesCount },
	V{ citiesCount },
	adjacencyList{},
	numVertices{ 0 } {
}


Graph::~Graph() {
	//delete[] adjacencyList;
}


//void Graph::addEdge(const String& u, const String& v, int weight) {
//	adjacencyList[u].push_back({ v, weight });
//	adjacencyList[v].push_back({ u, weight });
//}


void Graph::addEdge(const String& u, const String& v, int weight) {
	adjacencyList[u].push_back(std::make_pair(v, weight));
	//adjacencyList[v].push_back(std::make_pair(u, weight));
}


//List<Vertex>* Graph::getAdjacencyList() {
//	return adjacencyList;
//}


int Graph::getV() {
	return V;
}


void Graph::printGraph() {
	for (auto& vertex : adjacencyList) {
		std::cout << vertex.first << " -> ";

		for (auto& edge : vertex.second) {
			std::cout << edge.first;
			std::cout << "(" << edge.second << ") ";
		}

		std::cout << "\n";
	}
}
