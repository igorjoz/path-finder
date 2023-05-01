#pragma once


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