#pragma once


#include <iostream>

#include <vector>
#include <queue>
#include <cctype>
#include <algorithm>


#include "String.h"
#include "Resources.h"
#include "Graph.h"


typedef std::pair<int, int> Position;
typedef std::pair<String, Position> City;


class Map
{
private:
	int width;
	int height;
	char** map;

	int citiesCount;
	std::vector<String> citiesNames;

	int airConnectionsQuantity;
	AirConnection* airConnections;

	Graph* graph;

public:
	Map(char** map, int height, int width) : map(map), height(height), width(width) {
		findCities();
	}
	std::map<String, Position> cities;
	
	void findCities();
	bool isValidMove(int x, int y);
	std::vector<Position> findPath(const String& city1, const String& city2);


	Map(int width, int height);
	~Map();

	void readMap();
	void readAirConnections();

	void printMap();
	void printAirConnections();
	void printGraph();

	void createGraph();

	

	
	bool isPositionLetter(int x, int y);
	bool isPositionCity(int x, int y);

	String findCityName(int x, int y);


	int getCityIndex(String cityName);
	String getCityName(int cityIndex, int y);

	int getWidth() const;
	int getHeight() const;
	int getMapValue(int x, int y) const;
};

