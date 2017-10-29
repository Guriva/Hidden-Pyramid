#include <iostream>
#include "creature.h"
#include "room.h"

Creature::Creature(const char* name, const char* description, Entity* room) :
	Entity(name, description, room) {

	type = CREATURE;
	healthPoints = 10;
	maxHealth = 20;
	inCombat = false;
}

Creature::~Creature() {

}

bool Creature::Update(const float& frameTime) {
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

bool Creature::attack(const vector<string>& args) {
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

bool Creature::isAlive() const {
	return healthPoints > 0;
}

Creature* Creature::findPlayer(const Entity* entity) const {
	Creature* creature = nullptr;
	for (list<Entity*>::const_iterator it = entity->entitiesInside.begin(); it != entity->entitiesInside.cend() && creature == nullptr; ++it) {
		if ((*it)->type == PLAYER) {
			creature = (Creature*)(*it);
		}
	}
	return creature;
}