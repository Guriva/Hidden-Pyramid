#include <iostream>
#include "room.h"

using namespace std;

Room::Room(const char* name, const char* description) :
	Entity(name, description) {

	type = ROOM;
}

Room::~Room() {

}

void Room::look() const {
	cout << "a" << endl;
}