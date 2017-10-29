#include <iostream>
#include "requirements.h"

Requirements::Requirements(const char* name, const char* description, const PType& puzzleType) :
	Puzzle(name,description,puzzleType) {

	entitiesReq.reserve(10);
}

Requirements::~Requirements() {

}

void Requirements::look() const {
	cout << description << endl;
	cout << "You need: " << endl;
	for (unsigned int i = 0; i < entitiesReq.size(); ++i) {
		cout << entitiesReq[i]->name << endl;
	}
}

void Requirements::addRequirement(Entity* entity) {
	entitiesReq.push_back(entity);
}