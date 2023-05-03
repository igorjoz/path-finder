#include "Map.h"


using namespace std;


Map::Map(int width, int height) :
	width{ width },
	height{ height },
	airConnectionsQuantity{ 0 },
	citiesCount{ 0 },
	citiesNames{ vector<String>() },
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
	cin >> this->airConnectionsQuantity;

	this->airConnections = new AirConnection[this->airConnectionsQuantity];

	for (int i = 0; i < this->airConnectionsQuantity; i++) {
		cin >> this->airConnections[i].source >> this->airConnections[i].destination>> this->airConnections[i].distance;
	}
}


void Map::printMap() {
	cerr << "\nMap:\n";

	for (int i = 0; i < this->height; i++) {
		for (int j = 0; j < this->width; j++) {
			cerr << this->map[i][j];
		}

		cerr << "\n";
	}
}


void Map::printAirConnections() {
	cerr << "\nAir connections:\n";

	for (int i = 0; i < this->airConnectionsQuantity; i++) {
		AirConnection airConnection = this->airConnections[i];
        
		cerr << airConnection.source << " " << airConnection.destination << " " << airConnection.distance << "\n";
	}
}


void Map::printGraph() {
	cerr << "\nGraph:\n";

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

	cerr << "Cities count (findCities): " << citiesCount << "\n";
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

    vector<pair<int, int>> directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

    for (int i = 0; i < citiesCount; i++) {
        City city = cities[i];
        int x = city.x;
        int y = city.y;
        String cityName = city.name;

        queue<tuple<int, int, int>> queue;
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
			int curX = get<0>(queue.front());
			int curY = get<1>(queue.front());
			int curDist = get<2>(queue.front());

            queue.pop();

            for (const auto& dir : directions) {
                int newX = curX + dir.first;
                int newY = curY + dir.second;

                if (newX >= 0 and newX < height and newY >= 0 and newY < width and
                    map[newX][newY] != '.' and !isPositionLetter(newX, newY) and !visited[newX][newY])
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
		AirConnection airConnection = airConnections[i];

        graph->addEdge(airConnection.source, airConnection.destination, airConnection.distance);
    }
}


void Map::findShortestPath(const String& source, const String& destination) {
    int distance = graph->findShortestPath(source, destination).first;

	cout << distance << "\n";
}


void Map::findAndPrintShortestPath(const String& source, const String& destination) {
    graph->findAndPrintShortestPath(source, destination);
}


bool Map::isPositionLetter(int x, int y) {
    return x >= 0 and x < height and y >= 0 and y < width and map[x][y] != '.' and map[x][y] != '#' and map[x][y] != '*';
}


bool Map::isPositionCity(int x, int y) {
	return x >= 0 and x < height and y >= 0 and y < width and map[x][y] == '*';
}


String Map::findCityName(int i, int j) {
    vector<pair<int, int>> namePositions = { {0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {-1, -1}, {1, -1}, {-1, 1} };
    String cityName = "";

    for (const auto& position : namePositions) {
        int x = i + position.first;
        int y = j + position.second;

        if (isPositionLetter(x, y)) {
            if (isPositionLetter(x, y - 1)) {
                while (isPositionLetter(x, y)) {
                    y--;
                }
            }

            if (!isPositionLetter(x, y)) {
                y++;
            }
            
            cityName += map[x][y];
            
            if (isPositionLetter(x, y + 1)) {
                y++;

                while (isPositionLetter(x, y)) {
                    cityName += map[x][y];
                    y++;
                }
            }

            //cerr << "findCityName(" << x << ", " << y << "):" << cityName << "\n";

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