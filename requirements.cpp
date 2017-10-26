#include "requirements.h"

Requirements::Requirements(const char* name, const char* description, PType puzzleType) :
	Puzzle(name,description,puzzleType) {

	entitiesReq.reserve(10);
}

Requirements::~Requirements() {

}

void Requirements::addRequirement(Entity* entity) {
	entitiesReq.push_back(entity);
}