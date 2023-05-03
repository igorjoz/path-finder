#pragma once


#include "UnorderedMap.h"


#include "List.h"
#include "String"
#include "Resources.h"


using namespace std;


class Graph
{
public:
	int citiesCount;
	int numVertices;
	unordered_map<String, vector<pair<String, int>>, StringHash> adjacencyList;
	
	int V;

	Graph(int citiesCount);
	~Graph();
	void addEdge(const String& u, const String& v, int weight);
	int getV();

	void printGraph();

	pair<int, unordered_map<String, String, StringHash>> findShortestPath(const String& source, const String& destination);
	void findAndPrintShortestPath(const String& source, const String& destination);
};
