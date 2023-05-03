#pragma once


#include <map>
#include <unordered_map>
#include <functional> // for std::hash


#include <queue>
#include <limits>
#include <set>


#include "List.h"
#include "String"
#include "Resources.h"


class Graph
{
public:
	int citiesCount;
	int numVertices;
	std::unordered_map<String, std::vector<std::pair<String, int>>, StringHash> adjacencyList;
	
	int V;

	Graph(int citiesCount);
	~Graph();
	void addEdge(const String& u, const String& v, int weight);
	int getV();

	void printGraph();

	std::pair<int, std::unordered_map<String, String, StringHash>> findShortestPath(const String& source, const String& destination);
	void findAndPrintShortestPath(const String& source, const String& destination);
};
