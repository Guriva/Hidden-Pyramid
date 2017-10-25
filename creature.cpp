#include <iostream>
#include "creature.h"
#include "room.h"

Creature::Creature(const char* name, const char* description, Room* room) :
	Entity(name, description, (Entity*)room) {

	type = CREATURE;
	healthPoints = 10;
	inCombat = false;
}

Creature::~Creature() {

}

void Creature::Update() {

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

void Creature::move(const vector<string>& args) {

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

bool Creature::isEnemy() const {
	return enemy;
}