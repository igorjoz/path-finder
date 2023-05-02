#include "Map.h"


Map::Map(int width, int height) :
	width{ width },
	height{ height },
	airConnectionsQuantity{ 0 } {
    //graph{ new Graph } {
	
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
	delete[] this->airConnections;
	delete[] this->map;
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
		std::cerr << this->airConnections[i].source << " " << this->airConnections[i].destination << " " << this->airConnections[i].distance << "\n";
	}
}


void Map::createGraph() {
    std::vector<Vertex> graph;

    int dr[4] = { 0, 0, -1, 1 }; // Delta row values for neighbors
    int dc[4] = { -1, 1, 0, 0 }; // Delta column values for neighbors
    std::queue<int> queue;

    //Add vertices for all cells that are not walls or cities; cell name
    for (int i = 0; i < height; i++) {
        std::string label = "";

        for (int j = 0; j < width; j++) {
            char letter = map[i][j];

            if ((letter >= 'a' and letter <= 'z') or (letter >= 'A' and letter <= 'Z')) {
                label += letter;
            }

            if ((letter == '#' or letter == '.' or letter == '*' or letter == '\n' or j + 1 == width) and label.size() > 0) {
                Vertex vertex = { label, i, j, std::vector<int>() };
                //std::cerr << vertex.label << " " << vertex.row << " " << vertex.column << "\n";
                label = "";
                graph.push_back(vertex);
            }
        }
    }

    //Add edges for neighboring cells and cities
    for (int i = 0; i < graph.size(); i++) {
        Vertex& vertex = graph[i];
        queue.push(i);

        while (!queue.empty()) {
            int u_idx = queue.front();
            queue.pop();
            Vertex& u = graph[u_idx];

            for (int k = 0; k < 4; k++) {
                int nr = u.row + dr[k];
                int nc = u.column + dc[k];

                if (nr >= 0 && nr < height && nc >= 0 && nc < width) {
                    //String label = "";
                    std::string label = "";
                    label += map[nr][nc];

                    if (label != "#" && label != ".") {
                        // Add an undirected edge to neighboring cells
                        for (int j = 0; j < graph.size(); j++) {
                            if (graph[j].row == nr && graph[j].column == nc) {
                                u.adj.push_back(j);
                                graph[j].adj.push_back(u_idx);
                            }
                        }
                    }
                    if (label != "." && label != "*") {
                        // Add a directed edge to cities
                        for (int j = 0; j < graph.size(); j++) {
                            if (graph[j].label == label) {
                                u.adj.push_back(j);
                                break;
                            }
                        }
                    }
                }
            }
        }
    }

    // print graph
    std::cerr << "\nGraph:\n";

    for (int i = 0; i < graph.size(); i++) {
        std::cerr << graph[i].label << " " << graph[i].row << " " << graph[i].column << " ";

        for (int j = 0; j < graph[i].adj.size(); j++) {
            std::cerr << graph[i].adj[j] << " ";
        }

        std::cerr << "\n";
    }
}
