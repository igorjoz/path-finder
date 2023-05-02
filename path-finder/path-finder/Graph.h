#pragma once


#include "List.h"
#include "String"


class Graph
{
private:
	List<int>* adjacencyList;
	int V;

public:
	Graph(int V);
	~Graph();
	void addEdge(int v, int w);
	List<int>* getAdjacencyList();
	int getV();
};
