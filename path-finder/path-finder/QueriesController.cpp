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
		std::cin >> queries[i].source >> queries[i].destination;
	}
}


void QueriesController::printQueries() {
	std::cerr << "\nQueries:\n";

	for (int i = 0; i < queriesQuantity; i++) {
		std::cerr << queries[i].source << " " << queries[i].destination << "\n";
	}
}


int QueriesController::getQueriesQuantity() {
	return queriesQuantity;
}


Query* QueriesController::getQueries() {
	return queries;
}
