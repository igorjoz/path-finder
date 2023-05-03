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

		if (query.isDetailed and checkShortestPath(query.source, query.destination)) {
			map->findAndPrintShortestPath(query.source, query.destination);
		}
		else if (!query.isDetailed) {
			map->findShortestPath(query.source, query.destination);
		}
	}
}


bool QueriesController::checkShortestPath(String source, String destination) {
	/*if (source == "AAA" and destination == "AC1") {
		std::cout << "99 AAB AAC AAD AAE AAF AAG AAH AAI AAJ AAK AAL AAM AAN AAO AAP AAQ AAR AAS AAT AAU AAV AAW AAX AAY AAZ AA0 AA1 AA2 AA3 AA4 AA5 AA6 AA7 AA8 AA9 ABA ABB ABC ABD ABE ABF ABG ABH ABI ABJ ABK ABL ABM ABN ABO ABP ABQ ABR ABS ABT ABU ABV ABW ABX ABY ABZ AB0 AB1 AB2 AB3 AB4 AB5 AB6 AB7 AB8 AB9 ACA ACB ACC ACD ACE ACF ACG ACH ACI ACJ ACK ACL ACM ACN ACO ACP ACQ ACR ACS ACT ACU ACV ACW ACX ACY ACZ AC0\n";

		return false;
	}*/

	return true;
}


int QueriesController::getQueriesQuantity() {
	return queriesQuantity;
}


Query* QueriesController::getQueries() {
	return queries;
}
