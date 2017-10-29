#include <iostream>
#include "snake.h"
#include "player.h"

Snake::Snake(const char* name, const char* description, Entity* entity, const bool& autoRespawn) :
	Creature(name, description, entity), autoRespawn(autoRespawn) {

	type = CREATURE;
	healthPoints = 5;
	maxHealth = 5;

	damage = 1;
	avoiding = false;
	cdAvoid = 15.f;
	cdAvoidLeft = 15.f;
	cdAvoidTime = 1.5f;
	cdAvoidTimeLeft = 1.5f;
	minCdAttack = 7.f;
	maxCdAttack = 8.f;
	cdAttack = minCdAttack + (((float)rand()) / (float)RAND_MAX) * (maxCdAttack - minCdAttack);
	cdAttackLeft = cdAttack;
	frameTime = 0.f;
}

Snake::~Snake() {

}

bool Snake::Update(const float& frameTime) {
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
				cout << "\nThe snake covers behind a rock, making it too dangerous to attack her right now" << endl;
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

void Snake::updateCds() {
	if (cdAvoidLeft > 0.f)
		cdAvoidLeft -= frameTime;
	if (avoiding && cdAvoidTimeLeft > 0.f)
		cdAvoidTimeLeft -= frameTime;
	if (cdAttackLeft > 0.f)
		cdAttackLeft -= frameTime;
}

void Snake::attack() const {
	if (((Player*)target)->avoiding == false) {
		target->healthPoints -= damage;
		cout << "\nThe snake bites you, ouch!" << endl;
	}
	else {
		cout << "\nThe snake tries to bite you, but you avoid the attack" << endl;
	}
}