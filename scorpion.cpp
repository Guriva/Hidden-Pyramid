#include <iostream>
#include "scorpion.h"
#include "player.h"

Scorpion::Scorpion(const char* name, const char* description, Entity* entity, bool autoRespawn) :
	Creature(name, description, entity), autoRespawn(autoRespawn) {

	type = CREATURE;
	healthPoints = 15;
	maxHealth = 15;

	damage = 1;
	avoiding = false;
	cdAvoid = 10.f;
	cdAvoidLeft = 10.f;
	cdAvoidTime = 1.0f;
	cdAvoidTimeLeft = 1.0f;
	minCdAttack = 10.f;
	maxCdAttack = 12.f;
	cdAttack = minCdAttack + (((float)rand()) / (float)RAND_MAX) * (maxCdAttack - minCdAttack);
	cdAttackLeft = cdAttack;
	frameTime = 0.f;
}

Scorpion::~Scorpion() {

}

bool Scorpion::Update(float frameTime) {
	this->frameTime = frameTime;
	if (isAlive() == true) {
		target = findPlayer(parent);

		if (target == nullptr)
			return false;

		if (target->inCombat == false && target->isAlive()) {
			target->inCombat = true;
			inCombat = true;
			((Player*)target)->statePlayer = WAITING;
			((Player*)target)->target = this;
			cout << endl << "\nA " << name << " attacks you!" << endl;
			return true;
		}

		if (inCombat) {
			updateCds();
			if (cdAttackLeft <= 0.f && avoiding == false) {
				attack();
				cdAttack = minCdAttack + (((float)rand()) / (float)RAND_MAX) * (maxCdAttack - minCdAttack);
				cdAttackLeft = cdAttack;
				return true;
			}
			else if (cdAvoidLeft <= 0.f && avoiding == false) {
				avoiding = true;
				cdAvoidLeft = cdAvoid;
				cout << "\nThe scorpion covers behind a rock, making it too dangerous to attack him right now" << endl;
				return true;
			}
			else if (cdAvoidTimeLeft <= 0.f) {
				avoiding = false;
				cdAvoidTimeLeft = cdAvoidTime;
				cout << "\nIt comes back from behind the rock" << endl;
				return true;
			}
		}
	}
	else {
		target = nullptr;
		inCombat = false;
		if (autoRespawn) {
			if (findPlayer(parent) == nullptr) {
				healthPoints = maxHealth;
			}
		}
	}
	return false;
}

void Scorpion::updateCds() {
	if (cdAvoidLeft > 0.f)
		cdAvoidLeft -= frameTime;
	if (avoiding && cdAvoidTimeLeft > 0.f)
		cdAvoidTimeLeft -= frameTime;
	if (cdAttackLeft > 0.f)
		cdAttackLeft -= frameTime;
}

void Scorpion::attack() {
	if (((Player*)target)->avoiding == false) {
		target->healthPoints -= damage;
		cout << "\nThe scorpion hits you with his tail!" << endl;
	}
	else {
		cout << "\nThe tries to pick you with his tail, but you avoid the attack" << endl;
	}
}