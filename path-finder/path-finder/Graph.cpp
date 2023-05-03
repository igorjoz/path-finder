#include "Graph.h"


Graph::Graph(int citiesCount)
	: citiesCount{ citiesCount },
	V{ citiesCount },
	adjacencyList{},
	numVertices{ 0 } {
}


Graph::~Graph() {
	//delete[] adjacencyList;
}


void Graph::addEdge(const String& u, const String& v, int weight) {
	adjacencyList[u].push_back(std::make_pair(v, weight));
	//adjacencyList[v].push_back(std::make_pair(u, weight));
}


//List<Vertex>* Graph::getAdjacencyList() {
//	return adjacencyList;
//}


int Graph::getV() {
	return V;
}


void Graph::printGraph() {
	for (auto& vertex : adjacencyList) {
		std::cerr << vertex.first << " -> ";

		for (auto& edge : vertex.second) {
			std::cerr << edge.first;
			std::cerr << "(" << edge.second << ") ";
		}

		std::cerr << "\n";
	}
}


std::pair<int, std::unordered_map<String, String, StringHash>> Graph::findShortestPath(const String& source, const String& destination) {
    std::unordered_map<String, int, StringHash> distances;
    std::unordered_map<String, String, StringHash> previous;
    std::priority_queue<std::pair<int, String>, std::vector<std::pair<int, String>>, std::greater<std::pair<int, String>>> pq;

    for (const auto& entry : adjacencyList) {
        distances[entry.first] = std::numeric_limits<int>::max();
    }

    distances[source] = 0;
    pq.push({ 0, source });

    while (!pq.empty()) {
        String currentCity = pq.top().second;
        int currentDistance = pq.top().first;
        pq.pop();

        if (currentDistance > distances[currentCity]) {
            continue;
        }

        for (const auto& neighbor : adjacencyList[currentCity]) {
            String neighborCity = neighbor.first;
            int edgeWeight = neighbor.second;
            int newDistance = currentDistance + edgeWeight;

            if (newDistance < distances[neighborCity]) {
                distances[neighborCity] = newDistance;
                previous[neighborCity] = currentCity;
                pq.push({ newDistance, neighborCity });
            }
        }
    }

    if (previous.find(destination) == previous.end()) {
        //std::cout << "No path found from " << source << " to " << destination << std::endl;
		return { 0, previous };
    }

    //std::cout << "Total distance between " << source << " and " << destination << ": " << distances[destination] << std::endl;
    //std::cout << distances[destination] << "\n";
    return { distances[destination], previous };
}

void Graph::findAndPrintShortestPath(const String& source, const String& destination) {
    std::pair<int, std::unordered_map<String, String, StringHash>> result = findShortestPath(source, destination);

    int distance = result.first;
    std::unordered_map<String, String, StringHash> previous = result.second;

    if (distance == 0) {
        std::cout << "0\n";
        return;
    }

    if (previous.find(destination) == previous.end()) {
        std::cout << "0\n";
        return;
    }

    std::vector<String> path;
    String currentCity = destination;

    while (currentCity != source) {
        path.push_back(currentCity);
        currentCity = previous.at(currentCity);
    }

    path.push_back(source);
    std::reverse(path.begin(), path.end());

    //std::cout << "Shortest path from " << source << " to " << destination << " with distance " << distance << ": ";

    std::cout << distance;

	if (path.size() > 2) {
		std::cout << " ";
	}

    for (size_t i = 1; i < path.size() - 1; i++) {
        std::cout << path[i];

		if (i < path.size() - 2) {
			std::cout << " ";
		}
    }
    std::cout << "\n";
}
