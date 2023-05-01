#pragma once


#include <iostream>


class Map
{
private:
	int width;
	int height;
	char** map;

	public:
		Map(int width, int height);
		~Map();

		void printMap();
		void readMap();

		int getWidth();
		int getHeight();
		int getMapValue(int x, int y);
};

