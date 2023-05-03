#include "Graph.h"


using namespace std;


Graph::Graph(int citiesCount)
	: citiesCount{ citiesCount },
	V{ citiesCount },
	adjacencyList{},
	numVertices{ 0 } {
}


Graph::~Graph() {
}


void Graph::addEdge(const String& u, const String& v, int weight) {
	adjacencyList[u].push_back(make_pair(v, weight));
}


int Graph::getV() {
	return V;
}


void Graph::printGraph() {
	for (auto& vertex : adjacencyList) {
		cerr << vertex.first << " -> ";

		for (auto& edge : vertex.second) {
			cerr << edge.first;
			cerr << "(" << edge.second << ") ";
		}

		cerr << "\n";
	}
}


pair<int, unordered_map<String, String, StringHash>> Graph::findShortestPath(const String& source, const String& destination) {
    unordered_map<String, int, StringHash> distances;
    unordered_map<String, String, StringHash> previous;
    priority_queue<pair<int, String>, vector<pair<int, String>>, greater<pair<int, String>>> priorityQueue;

    for (const auto& entry : adjacencyList) {
        distances[entry.first] = numeric_limits<int>::max();
    }

    distances[source] = 0;
    priorityQueue.push({ 0, source });

    while (!priorityQueue.empty()) {
        String currentCity = priorityQueue.top().second;
        int currentDistance = priorityQueue.top().first;
        priorityQueue.pop();

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
                priorityQueue.push({ newDistance, neighborCity });
            }
        }
    }

    if (previous.find(destination) == previous.end()) {
        cerr << "No path found from " << source << " to " << destination << endl;
        return { 0, previous };
    }

    return { distances[destination], previous };
}


void Graph::findAndPrintShortestPath(const String& source, const String& destination) {
    pair<int, unordered_map<String, String, StringHash>> result = findShortestPath(source, destination);

    int distance = result.first;
    unordered_map<String, String, StringHash> previous = result.second;

    if (distance == 0) {
        cout << "0\n";
        return;
    }

    if (previous.find(destination) == previous.end()) {
        cout << "0\n";
        return;
    }

    vector<String> path;
    String currentCity = destination;

    while (currentCity != source) {
        path.push_back(currentCity);
        currentCity = previous.at(currentCity);
    }

    path.push_back(source);
    reverse(path.begin(), path.end());

    cout << distance;

    if (path.size() > 2) {
        cout << " ";
    }

    for (size_t i = 1; i < path.size() - 1; i++) {
        cout << path[i];

		if (i < path.size() - 2) {
			cout << " ";
		}
    }
    
    cout << "\n";
}


void Graph::addAirConnection(const String& u, const String& v, int weight) {
    if (weight > 1) {
        adjacencyList[u].push_back(make_pair(v, weight));
    }
    else {
        adjacencyList[u].push_back(make_pair(v, weight));
        adjacencyList[v].push_back(make_pair(u, weight));
    }
}
