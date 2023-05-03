#pragma once

#include "Vector.h"

#include "List.h"
#include "Node.h"

#include "Queue"
#include "PriorityQueue.h"

#include "Pair.h"

#include "String.h"


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

using namespace std;


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
		return hash<string>{}(str.getCString());
	}
};


struct City {
	String name;
	int x;
	int y;
};
