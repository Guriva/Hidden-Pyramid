#include "exit.h"
#include "room.h"

Exit::Exit(const char* name, const char* description, Room* source, Room* destination, const direction dir) :
	Entity(name, description), source(source), destination(destination), dir(dir) {

	type = EXIT;
}
Exit::~Exit() {

}

void Exit::Look() const {

}

Room* Exit::GetSource() const {
	return source;
}

Room* Exit::GetDestination() const {
	return destination;
}

direction Exit::GetDirection() const {
	return dir;
}