#pragma once


#include <map>
#include <unordered_map>
#include <functional> // for std::hash


#include "List.h"
#include "String"
#include "Resources.h"


class Graph
{
public:
	//List<Vertex>* adjacencyList;
	//std::vector<Vertex> adjacencyList;

	//List<Vertex>* adjacencyList;

	int citiesCount;
	int numVertices;
	std::unordered_map<String, std::vector<std::pair<String, int>>, StringHash> adjacencyList;
	
	int V;

//public:
	Graph(int citiesCount);
	~Graph();
	void addEdge(const String& u, const String& v, int weight);
	//List<Vertex>* getAdjacencyList();
	int getV();

	void printGraph();
};
