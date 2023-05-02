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

    map.printMap();
    map.printAirConnections();

    queriesController.readQueries();
    queriesController.printQueries();

    map.createGraph();

    //queriesController.executeQueries();

    return 0;
}
