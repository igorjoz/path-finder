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

            //if (character == '*') {
                //int nameStartX = -1;
                //int nameStartY = -1;
                //// Check for city name in 8 directions from the city marker
                //for (int dx = -1; dx <= 1; ++dx) {
                //    for (int dy = -1; dy <= 1; ++dy) {
                //        // Skip the city marker itself
                //        if (dx == 0 and dy == 0) {
                //            continue;
                //        }

                //        int newX = j + dx;
                //        int newY = i + dy;

                //        // Check if the neighboring cell is within bounds and contains a letter
                //        if (newX >= 0 and newX < width and newY >= 0 and newY < height and isalpha(map[newY][newX])) {
                //            nameStartX = newX;
                //            nameStartY = newY;
                //            break;
                //        }
                //    }
                //    if (nameStartX != -1) {
                //        break;
                //    }
                //}

                // If the city name is found, store it in citiesNames
                //if (nameStartX != -1) {
                //    String cityName = "";
                //    while (isalpha(map[nameStartY][nameStartX])) {
                //        cityName += map[nameStartY][nameStartX];
                //        nameStartX += (nameStartX - j);
                //        nameStartY += (nameStartY - i);

                //        // Check if the next cell is within bounds
                //        if (nameStartX < 0 || nameStartX >= width || nameStartY < 0 || nameStartY >= height) break;
                //    }
                //    citiesNames.push_back(cityName);
                //    citiesCount++;
                //}
            //}
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
		std::cerr << this->airConnections[i].source << " " << this->airConnections[i].destination << " " << this->airConnections[i].distance << "\n";
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


std::vector<Position> Map::findPath(const String& city1, const String& city2) {
    if (cities.count(city1) == 0 || cities.count(city2) == 0) {
        return {}; // City not found
    }

    Position start = cities[city1];
    Position end = cities[city2];

    std::map<int, std::map<int, Position>> parent;
    std::queue<Position> queue;
    queue.push(start);
    Position current;

    std::vector<Position> directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

    while (!queue.empty()) {
        current = queue.front();
        queue.pop();

        if (current == end) {
            break;
        }

        for (const auto& dir : directions) {
            int newX = current.first + dir.first;
            int newY = current.second + dir.second;

            if (isValidMove(newX, newY) && parent[newX].count(newY) == 0) {
                parent[newX][newY] = current;
                queue.push({ newX, newY });
            }
        }
    }

    if (current != end) {
        return {}; // No path found
    }

    std::vector<Position> path;
    while (current != start) {
        path.push_back(current);
        current = parent[current.first][current.second];
    }
    std::reverse(path.begin(), path.end());
    return path;
}


String Map::getCityName(int x, int y) {
    String cityName = findCityName(x, y);
    
    return cityName;
}


void Map::createGraph() {
    findCities();

    graph = new Graph(citiesCount);

    std::vector<std::pair<int, int>> directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (isPositionCity(i, j)) {
                String cityName = findCityName(i, j);
                std::vector<std::pair<int, int>> namePositions = { {0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {-1, -1}, {1, -1}, {-1, 1} };

                std::map<String, bool> visited;
                std::queue<std::pair<int, int>> queue;
                queue.push({ i, j });

                while (!queue.empty()) {
                    auto current = queue.front();
                    queue.pop();

                    for (const auto& dir : directions) {
                        int newX = current.first + dir.first;
                        int newY = current.second + dir.second;

                        if (newX >= 0 and newX < height and newY >= 0 and newY < width and
                            map[newX][newY] != '.' and !visited[getCityName(newX, newY)]) {
                            if (map[newX][newY] == '*') {
                                String neighborCityName = "";
                                for (const auto& pos : namePositions) {
                                    int x = newX + pos.first;
                                    int y = newY + pos.second;
                                    if (x >= 0 && x < height && y >= 0 && y < width && isalpha(map[x][y])) {
                                        neighborCityName += map[x][y];
                                    }
                                }
                                graph->addEdge(cityName, neighborCityName, 0);
                            }
                            else if (map[newX][newY] == '#') {
                                queue.push({ newX, newY });
                            }
                            visited[getCityName(newX, newY)] = true;
                        }
                    }
                }
            }
        }
    }

    for (int i = 0; i < airConnectionsQuantity; i++) {
        graph->addEdge(airConnections[i].source, airConnections[i].destination, airConnections[i].distance);
    }
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
            y++;

            while (isPositionLetter(x, y)) {
                cityName += map[x][y];
                y++;
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