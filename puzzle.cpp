#include <iostream>
#include "puzzle.h"
#include "entity.h"
#include "exit.h"
#include "item.h"

Puzzle::Puzzle(const char* name, const char* description, PType puzzleType) :
	Entity(name,description,nullptr), solved(false), puzzleType(puzzleType) {

	type = PUZZLE;
}

Puzzle::~Puzzle() {

}

void Puzzle::look() const {
	cout << name << endl;
	cout << description << endl;
}

bool Puzzle::isSolved() const {
	return solved;
}