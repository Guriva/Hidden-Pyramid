#include <iostream>
#include "player.h"
#include "room.h"
#include "exit.h"
#include "globals.h"

Player::Player(const char* name, const char* description, Room* room) :
	Creature(name,description,room){

	type = PLAYER;
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
	return false;
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

void Player::status() const {

}

void Player::inventory() const {

}

bool Player::examine(const vector<string>& args) const {
	return false;
}