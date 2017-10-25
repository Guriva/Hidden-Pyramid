#include <iostream>
#include "exit.h"
#include "room.h"
#include "puzzle.h"
#include "globals.h"

Exit::Exit(const char* name, const char* secondRoomExit, const char* description,const char* secondDescr, Room* source, Room* destination, Entity* key, Puzzle* puzzle) :
	Entity(name, description, (Entity*)source), destination(destination), secondRoomExit(secondRoomExit), secondDescription(secondDescr), key(key), puzzle(puzzle), closed(false) {

	type = EXIT;
	if (destination != nullptr) {
		destination->entitiesInside.push_back(this);
	}

	if (key != nullptr || (puzzle != nullptr && !puzzle->isSolved())) {
		closed = true;
	}
}
Exit::~Exit() {

}

void Exit::look(const Room* room) const {
	if (same(room->name, ((Room*)parent)->name)) {
		cout << "You see an exit: ";
		cout << description << endl;
	}
	else {
		cout << "You see an exit: ";
		cout << secondDescription << endl;
	}
}

Room* Exit::getSource() const {
	return (Room*)parent;
}

Room* Exit::getDestination() const {
	return destination;
}

string Exit::getSecondDescr() const {
	return secondDescription;
}