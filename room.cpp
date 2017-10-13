#include "room.h"

Room::Room(const char* name, const char* description) :
	Entity(name, description) {

	type = ROOM;
}

Room::~Room() {

}

void Room::Look() {

}