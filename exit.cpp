#include <iostream>
#include "exit.h"
#include "room.h"
#include "puzzle.h"
#include "globals.h"

Exit::Exit(const char* name, const char* secondRoomExit, const char* description,const char* secondDescr, Room* source, Room* destination, exitData eData) :
	Entity(name, description, (Entity*)source), destination(destination), secondRoomExit(secondRoomExit),
	secondDescription(secondDescr), key(eData.key), puzzle(eData.puzzle), closed(false), onlyPassOnce(eData.onlyPassOnce) {

	type = EXIT;
	if (destination != nullptr && !eData.ignoreDestination) {
		destination->entitiesInside.push_back(this);
	}

	if (key != nullptr || (puzzle != nullptr && !puzzle->isSolved())) {
		closed = true;
	}
}
Exit::~Exit() {

}

void Exit::Update() {

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