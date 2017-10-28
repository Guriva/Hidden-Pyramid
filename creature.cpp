#include <iostream>
#include "creature.h"
#include "room.h"

Creature::Creature(const char* name, const char* description, Entity* room) :
	Entity(name, description, (Entity*)room) {

	type = CREATURE;
	healthPoints = 10;
	maxHealth = 20;
	inCombat = false;
}

Creature::~Creature() {

}

bool Creature::Update(float frameTime) {
	return false;
}

bool Creature::look(const vector<string>& args) const {
	if (isAlive()) {
		cout << "You see a " << name << endl;
		cout << description << endl;
	}
	else {
		cout << "You see a " << name << endl;
		cout << "It is dead" << endl;
	}
	return true;
}

bool Creature::move(const vector<string>& args) {
	return false;
}

bool Creature::use(const vector<string>& args) {
	return false;
}

bool Creature::attack(const vector<string>& args) {
	return false;
}

bool Creature::drop(const vector<string>& args) {
	return false;
}

bool Creature::take(const vector<string>& args) {
	return false;
}

bool Creature::put(const vector<string>& args) {
	return false;
}

bool Creature::unlock(const vector<string>& args) {
	return false;
}

void Creature::status() const {
	if (isAlive()) {
		cout << description << endl;
	}
	else {
		cout << "It is dead" << endl;
	}
}

void Creature::inventory() const {

}

Room* Creature::getRoom() const {
	return (Room*)parent;
}

int Creature::getHealth() const {
	return healthPoints;
}

bool Creature::isAlive() const {
	return healthPoints > 0;
}

Creature* Creature::findPlayer(Entity* entity) {
	Creature* creature = nullptr;
	for (list<Entity*>::const_iterator it = entity->entitiesInside.begin(); it != entity->entitiesInside.cend() && creature == nullptr; ++it) {
		if ((*it)->type == PLAYER) {
			creature = (Creature*)(*it);
		}
	}
	return creature;
}