#include "QueriesController.h"


QueriesController::QueriesController(Map* map) :
	map(map) {
	queriesQuantity = 0;
	queries = nullptr;
}


QueriesController::~QueriesController() {
	delete[] queries;
}


void QueriesController::readQueries() {
	std::cin >> queriesQuantity;

	queries = new Query[queriesQuantity];

	for (int i = 0; i < queriesQuantity; i++) {
		std::cin >> queries[i].source >> queries[i].destination >> queries[i].isDetailed;
	}
}


void QueriesController::printQueries() {
	std::cerr << "\nQueries:\n";

	for (int i = 0; i < queriesQuantity; i++) {
		Query query = queries[i];

		std::cerr << query.source << " " << query.destination << " " << query.isDetailed << "\n";
	}
}


void QueriesController::executeQueries() {
	for (int i = 0; i < queriesQuantity; i++) {
		Query query = queries[i];

		if (query.isDetailed) {
			map->findAndPrintShortestPath(query.source, query.destination);
		}
		else {
			map->findShortestPath(query.source, query.destination);
		}
	}
}


int QueriesController::getQueriesQuantity() {
	return queriesQuantity;
}


Query* QueriesController::getQueries() {
	return queries;
}
