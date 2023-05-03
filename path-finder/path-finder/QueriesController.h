#pragma once


#include <iostream>


#include "Map.h"
#include "String.h"
#include "Resources.h"


class QueriesController
{
private:
	int queriesQuantity;
	Query* queries;

	Map* map;

	public:
		QueriesController(Map* map);
		~QueriesController();

		void readQueries();

		void printQueries();

		void executeQueries();

		int getQueriesQuantity();
		Query* getQueries();

		bool checkShortestPath(String source, String destination);
};

