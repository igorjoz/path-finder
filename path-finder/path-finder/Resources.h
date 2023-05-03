#pragma once


#include <vector>
#include <map>
#include <unordered_map>
#include <functional>
#include <algorithm>
#include <cctype>

#include <queue>
#include <limits>
#include <set>

#include <list>
#include <stdexcept>
#include <utility>
#include <iterator>


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
