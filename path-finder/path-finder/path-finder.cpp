#include <iostream>


#include "Map.h"


int main()
{
    int mapWidth = 0;
    int mapHeight = 0;

    std::cin >> mapWidth >> mapHeight;

    Map map = Map(mapWidth, mapHeight);

    map.readMap();

    map.printMap();

    return 0;
}
