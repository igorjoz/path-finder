#include "Map.h"


Map::Map(int width, int height) :
	width{ width },
	height{ height },
	airConnectionsQuantity{ 0 } {
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
	delete[] this->airConnections;
	delete[] this->map;
}


void Map::readMap() {
	char c = getchar();

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			c = getchar();

			if (c == '\n') {
				c = getchar();
			}

			this->map[i][j] = c;
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