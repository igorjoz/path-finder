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
