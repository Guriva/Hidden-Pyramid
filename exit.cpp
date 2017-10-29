#include <iostream>
#include "exit.h"
#include "room.h"
#include "puzzle.h"
#include "globals.h"

Exit::Exit(const char* name, const char* secondRoomExit, const char* description,const char* secondDescr, Room* source, Room* destination, const exitData& eData) :
	Entity(name, description, (Entity*)source), destination(destination), secondRoomExit(secondRoomExit),
	secondDescription(secondDescr), key(eData.key), puzzle(eData.puzzle), locked(false), onlyPassOnce(eData.onlyPassOnce) {

	type = EXIT;
	if (destination != nullptr && !eData.ignoreDestination) {
		destination->entitiesInside.push_back(this);
	}

	if (key != nullptr || (puzzle != nullptr && puzzle->solved == false)) {
		locked = true;
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

string Exit::getExitName(const Room* room) const {
	return ((same(room->name, parent->name)) ? (name) : (secondRoomExit));
}