#include "creature.h"
#include "room.h"

Creature::Creature(const char* name, const char* description, Room* room) :
	Entity(name, description), room(room) {

	type = CREATURE;
	healthPoints = 10;
}

Creature::~Creature() {

}

void Creature::Look() const {

}

Room* Creature::GetRoom() const {
	return room;
}

int Creature::GetHealth() const {
	return healthPoints;
}