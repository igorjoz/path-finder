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
	char label;      // Label of the cell
	int row, col;    // Row and column indices of the cell
	std::vector<int> adj; // Indices of neighboring cells
};
