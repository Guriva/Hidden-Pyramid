#include <iostream>
#include <algorithm>
#include "player.h"
#include "room.h"
#include "exit.h"
#include "item.h"
#include "puzzle.h"
#include "requirements.h"
#include "globals.h"

Player::Player(const char* name, const char* description, Room* room) :
	Creature(name,description,room){

	type = PLAYER;
	statePlayer = WAITING;
	healthPoints = 10;
	maxHealth = 10;
	maxInventory = 3;
	enemy = false;
}

Player::~Player() {

}

void Player::Update() {

}

bool Player::look(const vector<string>& args) const {
	if (args.size() > 1) {
		if (same(args[1], "me")) {
			cout << "You see yourself, you are an archaeologist" << endl;
			cout << description << endl;
			return true;
		}
		if (same(args[1], "inventory")) {
			inventory();
			return true;
		}
		
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
		cout << "There's nothing like that around" << endl;
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
		cout << "You cannot go that way" << endl;
		return false;
	}

	if (e->isClosed()) {
		if (e->needsKey()) {
			cout << "It seems the exit needs some kind of key to be opened..." << endl;
			return false;
		}
		else if (e->puzzle != nullptr && !e->puzzle->solved) {
			if (checkPuzzle(e->puzzle) == false)
				return false;
			else {
				e->puzzle = nullptr;
				e->closed = false;
			}
		}
		else {
			cout << "The exit is blocked and you cannot go through it anymore." << endl;
			return false;
		}
	}

	cout << "You go to the " << exitName << endl;
	Room* r;
	(same(e->parent->name,parent->name)) ? r = e->getDestination() : r = e->getSource();
	newParent(r);

	if (e->onlyPassOnce)
		e->closed = true;

	parent->look();
	
	return true;
}

bool Player::use(const vector<string>& args) {
	bool ret = false;
	for (list<Entity*>::const_iterator it = entitiesInside.begin(); it != entitiesInside.cend(); ++it) {
		if ((*it)->type == ITEM && ((Item*)(*it))->itemType == USABLE && same(args[1],(*it)->name)) {
			ret = true;
			if (((Item*)(*it))->useItem(this))
				(*it)->newParent(nullptr);
		}

		// Look in your backpack too
		else if ((*it)->type == CONTAINER) {
			for (list<Entity*>::const_iterator it2 = (*it)->entitiesInside.begin(); it2 != (*it)->entitiesInside.cend(); ++it2) {
				if ((*it2)->type == ITEM && ((Item*)(*it2))->itemType == USABLE && same(args[1], (*it2)->name)) {
					ret = true;
					if (((Item*)(*it2))->useItem(this))
						(*it2)->newParent(nullptr);
				}
			}
		}
	}

	if (ret == false) {
		cout << "You don't have that object in your inventory" << endl;
	}
	return false;
}

bool Player::attack(const vector<string>& args) {
	return false;
}

bool Player::drop(const vector<string>& args) {
	Item* item = nullptr;
	for (list<Entity*>::const_iterator it = entitiesInside.begin(); it != entitiesInside.cend(); ++it) {
		if ((*it)->type == ITEM && same((*it)->name, args[1]))
			item = (Item*)(*it);
	}

	if (item == nullptr) {
		cout << "You don't have that item in your inventory";
		return false;
	}

	cout << "You dropped " << item->name << endl;
	item->newParent(parent);

	return true;
}

bool Player::take(const vector<string>& args) {
	if (args.size() == 2)
	{
		Item* item = nullptr;
		for (list<Entity*>::const_iterator it = parent->entitiesInside.begin(); it != parent->entitiesInside.cend(); ++it) {
			if ((*it)->type == ITEM && ((Item*)(*it))->carriable && same((*it)->name, args[1]))
				item = (Item*)(*it);
		}

		if (item == nullptr) {
			cout << "You can't find such an item";
			return false;
		}

		// If you don't have space, look for a container in your inventory
		if (entitiesInside.size() >= maxInventory) {
			for (list<Entity*>::const_iterator it = entitiesInside.begin(); it != entitiesInside.cend(); ++it) {
				if ((*it)->type == ITEM && ((Item*)(*it))->itemType == CONTAINER) {
					cout << "You have taken " << item->name << " and put it inside the " << (*it)->name << endl;
					item->newParent((*it));
					return true;
				}
			}
			cout << "You don't have space in your inventory" << endl;
			return false;
		}
		else {
			cout << "You have taken " << item->name << endl;
			item->newParent(this);
		}
	}
	else if (args.size() == 4)
	{
		Item* itemContainer = nullptr;
		Item* item = nullptr;
		if (same(args[3], "inventory")) {
			cout << "That doesn't make any sense..." << endl;
			return false;
		}
		bool found = false;
		for (list<Entity*>::const_iterator it = parent->entitiesInside.begin(); it != parent->entitiesInside.cend() && !found; ++it) {
			if ((*it)->type == ITEM && ((Item*)(*it))->itemType == CONTAINER && same((*it)->name, args[3])) {
				itemContainer = (Item*)(*it);
				found = true;
			}
		}

		if (found == false) {
			cout << "You cannot find any " << args[3] << endl;
			return false;
		}

		if (itemContainer->locked) {
			cout << "The " << itemContainer->name << " seems locked" << endl;
			return false;
		}

		for (list<Entity*>::const_iterator it = itemContainer->entitiesInside.begin(); it != itemContainer->entitiesInside.cend(); ++it) {
			if ((*it)->type == ITEM && ((Item*)(*it))->carriable && same((*it)->name, args[1]))
				item = (Item*)(*it);
		}

		if (item == nullptr) {
			cout << "You can't find such an item from " << itemContainer->name << endl;
			return false;
		}

		// If you don't have space, look for a container in your inventory
		if (entitiesInside.size() >= maxInventory) {
			for (list<Entity*>::const_iterator it = entitiesInside.begin(); it != entitiesInside.cend(); ++it) {
				if ((*it)->type == ITEM && ((Item*)(*it))->itemType == CONTAINER) {
					cout << "You have taken " << item->name << " and put it inside the " << (*it)->name << endl;
					item->newParent((*it));
					return true;
				}
			}
			cout << "You don't have space in your inventory" << endl;
			return false;
		}
		else {
			cout << "You have taken " << item->name << endl;
			item->newParent(this);
		}
	}

	return true;
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
	if (entitiesInside.size() == 0) {
		cout << "You don't have any item";
		return;
	}

	cout << "You have:" << endl;
	for (list<Entity*>::const_iterator it = entitiesInside.begin(); it != entitiesInside.cend(); ++it) {
		cout << (*it)->name << endl;
		if ((*it)->type == ITEM && ((Item*)(*it))->itemType == CONTAINER) {
			for (list<Entity*>::const_iterator it2 = (*it)->entitiesInside.begin(); it2 != (*it)->entitiesInside.cend(); ++it2) {
				cout << (*it2)->name << " (inside " << (*it)->name << ")" << endl;
			}
		}
	}
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

bool Player::checkPuzzle(Puzzle* puzzle) {
	switch (puzzle->puzzleType) {
		case REQUIREMENTS: {
			// check if player has every object that requirements asks for
			for (unsigned int i = 0; i < ((Requirements*)puzzle)->entitiesReq.size(); ++i) {
				if (find(entitiesInside.begin(), entitiesInside.end(), ((Requirements*)puzzle)->entitiesReq[i]) != entitiesInside.end() == false) {
					puzzle->look();
					return false;
				}
			}
			return true;
			break;
		}
		default: {
			puzzle->look();
			break;
		}
	}
	return false;
}