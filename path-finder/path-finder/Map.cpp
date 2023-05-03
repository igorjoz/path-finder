#include "Map.h"


Map::Map(int width, int height) :
	width{ width },
	height{ height },
	airConnectionsQuantity{ 0 },
	citiesCount{ 0 },
	citiesNames{ std::vector<String>() },
    graph{ nullptr } {
	
    this->airConnections = nullptr;
    this->map = new char* [this->height];

	for (int i = 0; i < this->height; i++) {
		this->map[i] = new char[this->width];
	}

	for (int i = 0; i < this->height; i++) {
		for (int j = 0; j < this->width; j++) {
			this->map[i][j] = ' ';
		}
	}
}


Map::~Map() {
	for (int i = 0; i < this->height; i++) {
		delete[] this->map[i];
	}

	delete[] this->map;

	delete[] this->airConnections;
	delete this->graph;
}


void Map::readMap() {
    char character = getchar();

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            character = getchar();

            if (character == '\n') {
                character = getchar();
            }

            this->map[i][j] = character;
        }
    }
}


void Map::readAirConnections() {
	std::cin >> this->airConnectionsQuantity;

	this->airConnections = new AirConnection[this->airConnectionsQuantity];

	for (int i = 0; i < this->airConnectionsQuantity; i++) {
		std::cin >> this->airConnections[i].source >> this->airConnections[i].destination>> this->airConnections[i].distance;
	}
}


void Map::printMap() {
	std::cerr << "\nMap:\n";

	for (int i = 0; i < this->height; i++) {
		for (int j = 0; j < this->width; j++) {
			std::cerr << this->map[i][j];
		}

		std::cerr << "\n";
	}
}


void Map::printAirConnections() {
	std::cerr << "\nAir connections:\n";

	for (int i = 0; i < this->airConnectionsQuantity; i++) {
		AirConnection airConnection = this->airConnections[i];
        
		std::cerr << airConnection.source << " " << airConnection.destination << " " << airConnection.distance << "\n";
	}
}


void Map::printGraph() {
	std::cerr << "\nGraph:\n";

    graph->printGraph();
}


void Map::findCities() {
	citiesCount = 0;
    
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
			if (isPositionCity(i, j)) {
                String cityName(findCityName(i, j));
				citiesCount += 1;
				citiesNames.push_back(cityName);

				cities.push_back(City{ cityName, i, j });
            }
        }
    }

	std::cerr << "Cities count (findCities): " << citiesCount << "\n";
}


bool Map::isValidMove(int x, int y) {
    return x >= 0 && x < height&& y >= 0 && y < width&& map[x][y] != '.';
}


int Map::getCityIndex(String cityName) {
    for (int i = 0; i < citiesCount; i++) {
        if (citiesNames[i] == cityName) {
            return i;
        }
    }
    return -1;
}


//std::vector<Position> Map::findPath(const String& city1, const String& city2) {
//    if (cities.count(city1) == 0 || cities.count(city2) == 0) {
//        return {}; // City not found
//    }
//
//    Position start = cities[city1];
//    Position end = cities[city2];
//
//    std::map<int, std::map<int, Position>> parent;
//    std::queue<Position> queue;
//    queue.push(start);
//    Position current;
//
//    std::vector<Position> directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
//
//    while (!queue.empty()) {
//        current = queue.front();
//        queue.pop();
//
//        if (current == end) {
//            break;
//        }
//
//        for (const auto& dir : directions) {
//            int newX = current.first + dir.first;
//            int newY = current.second + dir.second;
//
//            if (isValidMove(newX, newY) && parent[newX].count(newY) == 0) {
//                parent[newX][newY] = current;
//                queue.push({ newX, newY });
//            }
//        }
//    }
//
//    if (current != end) {
//        return {}; // No path found
//    }
//
//    std::vector<Position> path;
//    while (current != start) {
//        path.push_back(current);
//        current = parent[current.first][current.second];
//    }
//    std::reverse(path.begin(), path.end());
//    return path;
//}


String Map::getCityName(int x, int y) {
	if (map[x][y] != '*') {
		return "";
	}
    
    String cityName = findCityName(x, y);
    
    return cityName;
}


void Map::createGraph() {
    findCities();

    graph = new Graph(citiesCount);

    std::vector<std::pair<int, int>> directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

    for (int i = 0; i < citiesCount; i++) {
        City city = cities[i];
        int x = city.x;
        int y = city.y;
        String cityName = city.name;

        std::queue<std::tuple<int, int, int>> queue;
        bool** visited = new bool* [height];

        for (int j = 0; j < height; j++) {
            visited[j] = new bool[width];

            for (int k = 0; k < width; k++) {
                visited[j][k] = false;
            }
        }

        queue.push({ x, y, 0 });
        visited[x][y] = true;

        while (!queue.empty()) {
            //auto [curX, curY, curDist] = queue.front();

			int curX = std::get<0>(queue.front());
			int curY = std::get<1>(queue.front());
			int curDist = std::get<2>(queue.front());

            queue.pop();

            for (const auto& dir : directions) {
                int newX = curX + dir.first;
                int newY = curY + dir.second;

                if (newX >= 0 and newX < height and newY >= 0 and newY < width and
                    map[newX][newY] != '.' and !isalpha(map[newX][newY]) and !visited[newX][newY])
                {
                    if (isPositionCity(newX, newY)) {
                        String neighborCityName = findCityName(newX, newY);

                        if (neighborCityName == cityName) {
                            continue;
                        }

                        graph->addEdge(cityName, neighborCityName, curDist + 1);
                    }

                    if (map[newX][newY] == '#' and !visited[newX][newY]) {
                        queue.push({ newX, newY, curDist + 1 });
                        visited[newX][newY] = true;
                    }
                }
            }
        }

        for (int j = 0; j < height; j++) {
            delete[] visited[j];
        }
        delete[] visited;
    }

    for (int i = 0; i < airConnectionsQuantity; i++) {
        graph->addEdge(airConnections[i].source, airConnections[i].destination, airConnections[i].distance);
    }
}


//void Map::findShortestPath(const String& source, const String& destination) {
//    std::pair<int, std::vector<String>> result = graph->findShortestPath(source, destination);
//    int distance = result.first;
//    std::vector<String> path = result.second;
//
//    std::cout << distance << "\n";
//    printShortestPath(path);
//}


//void Map::printShortestPath(const std::vector<String>& path) {
//    if (!path.empty()) {
//        for (size_t i = 0; i < path.size(); ++i) {
//            if (i != 0) {
//                std::cout << " -> ";
//            }
//            std::cout << path[i];
//        }
//        std::cout << std::endl;
//    }
//}


void Map::findShortestPath(const String& source, const String& destination) {
	//graph->findShortestPath(source, destination);

    int distance = graph->findShortestPath(source, destination).first;

	std::cout << distance << "\n";
}


void Map::findAndPrintShortestPath(const String& source, const String& destination) {
	graph->findAndPrintShortestPath(source, destination);
}


bool Map::isPositionLetter(int x, int y) {
    return x >= 0 and x < height and y >= 0 and y < width and isalpha(map[x][y]);
}


bool Map::isPositionCity(int x, int y) {
	return x >= 0 and x < height and y >= 0 and y < width and map[x][y] == '*';
}


String Map::findCityName(int i, int j) {
    std::vector<std::pair<int, int>> namePositions = { {0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {-1, -1}, {1, -1}, {-1, 1} };
    String cityName = "";

    for (const auto& position : namePositions) {
        int x = i + position.first;
        int y = j + position.second;

        if (isPositionLetter(x, y)) {
            cityName += map[x][y];

            if (isPositionLetter(x, y + 1)) {
                y++;

                while (isPositionLetter(x, y)) {
                    cityName += map[x][y];
                    y++;
                }
            }
            else {
                y--;
                
                while (isPositionLetter(x, y)) {
                    cityName += map[x][y];
					y--;
                }

				cityName.reverse();
            }

            std::cerr << "findCityName(" << x << ", " << y << "):" << cityName << "\n";

            break;
        }
    }

    return cityName;
}


int Map::getWidth() const {
	return width;
}


int Map::getHeight() const {
	return height;
}


int Map::getMapValue(int x, int y) const {
	return map[x][y];
}


City* Map::getCityByName(const String& name) {
	for (auto& city : cities) {
		if (city.name == name) {
			return &city;
		}
	}

	return nullptr;
}


bool Map::isCity(int x, int y) const {
	return map[x][y] == '*';
}