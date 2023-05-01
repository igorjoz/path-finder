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

		int getQueriesQuantity();
		Query* getQueries();
};

