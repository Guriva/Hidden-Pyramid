#include <iostream>
#include "player.h"
#include "room.h"
#include "exit.h"
#include "globals.h"

Player::Player(const char* name, const char* description, Room* room) :
	Creature(name,description,room){

	type = PLAYER;
	statePlayer = WAITING;
	healthPoints = 100;
	enemy = false;
}

Player::~Player() {

}

void Player::Update() {

}

bool Player::look(const vector<string>& args) const {
	if (args.size() > 2 && same(args[2],"in")) {
		
		//Look an item inside of another item
		for (list<Entity*>::const_iterator it = parent->entitiesInside.begin(); it != parent->entitiesInside.cend(); ++it) {
			if ((*it)->type == ITEM && same((*it)->name, args[3])) {
				for (list<Entity*>::const_iterator it2 = (*it)->entitiesInside.begin(); it2 != (*it)->entitiesInside.cend(); ++it2) {
					if ((*it2)->type == ITEM && same((*it2)->name, args[3])) {
						(*it2)->look();
						return true;
					}
				}
			}
		}
	}
	else if (args.size() > 1) {
		if (same(args[1], "me")) {
			cout << "You see yourself, you are an archaeologist" << endl;
			cout << description << endl;
			return true;
		}
		else {
			for (list<Entity*>::const_iterator it = parent->entitiesInside.begin(); it != parent->entitiesInside.cend(); ++it)
			{
				if ((*it)->type == EXIT && same((*it)->name, args[1])) {
					((Exit*)(*it))->look((Room*)parent);
					return true;
				}
				else if (same((*it)->name, args[1]))
				{
					(*it)->look();
					return true;
				}
			}
		}
	}
	else {
		parent->look();	//Look room where the player is
		return true;
	}

	return false;
}

bool Player::move(const vector<string>& args) {
	Exit* e = nullptr;
	string exitName = "";
	switch (args.size()) {
		case 1: {
			e = getRoom()->getExit(args[0]);
			exitName = args[0];
			break;
		}
		
		case 2: {
			e = getRoom()->getExit(args[1]);
			exitName = args[1];
			break;
		}
	}

	if (e == nullptr) {
		cout << "This exit doesn't exist " << endl;
		return false;
	}

	if (e->isClosed()) {
		if (e->hasPuzzle() && !e->puzzleSolved()) {
			cout << "You try to go through the " << exitName << ", but it's closed." << endl;
			e->lookPuzzle();
			return false;
		}
		else if (e->needsKey()) {
			cout << "It seems the exit needs some kind of key to be opened..." << endl;
			return false;
		}
		else {
			cout << "The exit is blocked and you cannot go through it anymore." << endl;
			return false;
		}
	}

	cout << "You go through the" << exitName << endl;
	Room* r;
	(e->name == parent->name) ? r = e->getDestination() : r = e->getSource();
	newParent(r);

	if (e->isOneWay())
		e->setClosed(true);

	parent->look();
	
	return true;
}

bool Player::use(const vector<string>& args) {
	return false;
}

bool Player::attack(const vector<string>& args) {
	return false;
}

bool Player::drop(const vector<string>& args) {
	return false;
}

bool Player::take(const vector<string>& args) {
	return false;
}

bool Player::put(const vector<string>& args) {
	return false;
}

bool Player::unlock(const vector<string>& args) {
	return false;
}

bool Player::solve(const vector<string>& args) {
	return false;
}

void Player::status() const {

}

void Player::inventory() const {

}

bool Player::examine(const vector<string>& args) const {
	return false;
}

PState Player::getState() const {
	return statePlayer;
}

void Player::setState(const PState state) {
	statePlayer = state;
}