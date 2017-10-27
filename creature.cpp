#include <iostream>
#include "creature.h"
#include "room.h"

Creature::Creature(const char* name, const char* description, Room* room) :
	Entity(name, description, (Entity*)room) {

	type = CREATURE;
	healthPoints = 10;
	maxHealth = 20;
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

bool Creature::isEnemy() const {
	return enemy;
}