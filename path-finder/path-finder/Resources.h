#pragma once


#include <vector>


#include "String.h"


struct AirConnection {
	String source;
	String destination;
	int distance;
};


struct Query {
	String source;
	String destination;
	bool isDetailed;
};


struct Vertex {
	//String label;      // Label of the cell
	std::string label;      // Label of the cell
	int row;
	int column;    // Row and column indices of the cell
	std::vector<int> adj; // Indices of neighboring cells
};


struct StringHash {
	size_t operator()(const String& str) const {
		return std::hash<std::string>{}(str.getCString());
	}
};


struct City {
	String name;
	int x;
	int y;
};
