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

	if (key != nullptr || (puzzle != nullptr && !puzzle->isSolved())) {
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

bool Exit::isClosed() {
	return locked;
}

bool Exit::hasPuzzle() {
	return (puzzle != nullptr);
}

bool Exit::puzzleSolved() {
	return (puzzle->isSolved());
}

void Exit::lookPuzzle() {
	puzzle->look();
}

bool Exit::needsKey() {
	return (key != nullptr);
}

bool Exit::isOneWay() {
	return onlyPassOnce;
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

string Exit::getExitName(const Room* room) const {
	return ((same(room->name, parent->name)) ? (name) : (secondRoomExit));
}

void Exit::setClosed(const bool b) {
	locked = b;
}