#pragma once


#include <iostream>

#include <vector>
#include <queue>


#include "String.h"
#include "Resources.h"
#include "Graph.h"


class Map
{
private:
	int width;
	int height;
	char** map;

	int airConnectionsQuantity;
	AirConnection* airConnections;

	//Graph* graph;

public:
	Map(int width, int height);
	~Map();

	void readMap();
	void readAirConnections();

	void printMap();
	void printAirConnections();

	void createGraph();

	int getWidth();
	int getHeight();
	int getMapValue(int x, int y);
};

