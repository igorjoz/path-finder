#include "Map.h"


Map::Map(int width, int height) : width(width), height(height) {
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
	delete[] this->map;
}


void Map::printMap() {
	for (int i = 0; i < this->height; i++) {
		for (int j = 0; j < this->width; j++) {
			std::cerr << this->map[i][j];
		}

		std::cerr << "\n";
	}
}


void Map::readMap() {
	// input looks like this:
	//......
	//.A** B.
	//......

	// go character by character
	// use getchar


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
