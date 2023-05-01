#pragma once


#include <iostream>


#include "String.h"
#include "Resources.h"


class Map
{
private:
	int width;
	int height;
	char** map;

	int airConnectionsQuantity;
	AirConnection* airConnections;


	public:
		Map(int width, int height);
		~Map();

		void readMap();
		void readAirConnections();

		void printMap();
		void printAirConnections();

		int getWidth();
		int getHeight();
		int getMapValue(int x, int y);
};

