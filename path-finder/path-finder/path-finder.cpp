#include <iostream>


#include "Map.h"
#include "QueriesController.h"


int main()
{
    int mapWidth = 0;
    int mapHeight = 0;

    std::cin >> mapWidth >> mapHeight;

    Map map = Map(mapWidth, mapHeight);
    QueriesController queriesController = QueriesController(&map);

    map.readMap();
    map.readAirConnections();
    queriesController.readQueries();
    
    //map.printMap();
    //map.printAirConnections();
    //queriesController.printQueries();

    map.createGraph();
	map.printGraph();

    //queriesController.executeQueries();

    return 0;
}
