#include <iostream>
#include "puzzle.h"
#include "entity.h"

Puzzle::Puzzle(const char* name, const char* description, Room* room) :
	Entity(name,description,(Entity*)room) {

	type = PUZZLE;
	solved = false;
}

Puzzle::~Puzzle() {

}
void Puzzle::look() const {
	cout << "You see some kind of puzzle here: " << name << endl;
	cout << description << endl;
}

bool Puzzle::isSolved() const {
	return solved;
}