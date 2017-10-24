#include "puzzle.h"
#include "entity.h"

Puzzle::Puzzle(const char* name, const char* description) :
	Entity(name,description) {

	type = PUZZLE;
	solved = false;
}

Puzzle::~Puzzle() {

}
void Puzzle::look() const {

}