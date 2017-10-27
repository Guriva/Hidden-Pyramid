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

		// Look for the item in your inventory
		for (list<Entity*>::const_iterator it = entitiesInside.begin(); it != entitiesInside.cend(); ++it) {
			if (same((*it)->name, args[1])) {
				(*it)->look();
				return true;
			}
			if ((*it)->type == ITEM && ((Item*)(*it))->itemType == CONTAINER) {
				for (list<Entity*>::const_iterator it2 = (*it)->entitiesInside.begin(); it2 != (*it)->entitiesInside.cend(); ++it2) {
					if (same((*it2)->name, args[1])) {
						(*it2)->look();
						return true;
					}
				}
			}
		}
		
		// If not, look if it is in the room
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

	if (inCombat) {
		cout << "You are being attacked right now, watch your back!" << endl;
		return false;
	}

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
		else if (e->puzzle != nullptr && e->puzzle->solved == false) {
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

	// check if you carry the item or it is inside of another one
	for (list<Entity*>::const_iterator it = entitiesInside.begin(); it != entitiesInside.cend(); ++it) {
		if ((*it)->type == ITEM && same((*it)->name, args[1]))
			item = (Item*)(*it);
		else if ((*it)->type == ITEM && ((Item*)(*it))->itemType == CONTAINER) {
			for (list<Entity*>::const_iterator it2 = (*it)->entitiesInside.begin(); it2 != (*it)->entitiesInside.cend(); ++it2) {
				if ((*it2)->type == ITEM && same((*it2)->name, args[1]))
					item = (Item*)(*it2);
			}
		}
	}

	if (item == nullptr) {
		cout << "You don't have that item in your inventory" << endl;
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
			if (same((*it)->name, args[1]) && (*it)->type == ITEM) {
				if (((Item*)(*it))->carriable)
					item = (Item*)(*it);
				else {
					cout << "You cannot take that item with you." << endl;
					return false;
				}
			}
		}

		if (item == nullptr) {
			cout << "You can't find such an item" << endl;
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
	Item* item = nullptr;

	for (list<Entity*>::const_iterator it = entitiesInside.begin(); it != entitiesInside.cend(); ++it) {
		if ((*it)->type == ITEM && same((*it)->name, args[1]))
			item = (Item*)(*it);
		else if ((*it)->type == ITEM && ((Item*)(*it))->itemType == CONTAINER) {
			for (list<Entity*>::const_iterator it2 = (*it)->entitiesInside.begin(); it2 != (*it)->entitiesInside.cend(); ++it2) {
				if ((*it2)->type == ITEM && same((*it2)->name, args[1]))
					item = (Item*)(*it2);
			}
		}
	}

	if (item == nullptr) {
		cout << "You don't have that item in your inventory" << endl;
		return false;
	}

	Entity* entity = nullptr;

	for (list<Entity*>::const_iterator it = parent->entitiesInside.begin(); it != parent->entitiesInside.cend(); ++it) {
		if (same((*it)->name, args[3]))
			entity = (*it);
	}

	if (entity == nullptr) {
		cout << "You can't find anything like that to put in the " << args[1] << endl;
		return false;
	}

	if (entity->type == ITEM && ((Item*)entity)->itemType == CONTAINER && ((Item*)entity)->locked == false) {
		cout << "You have put " << args[1] << " inside the " << args[3] << endl;
		item->newParent(entity);
		return true;
	}

	cout << "You cannot put that into " << args[3] << endl;
	return false;
}

bool Player::unlock(const vector<string>& args) {
	return false;
}

void Player::status() const {
	if (healthPoints == 10) {
		cout << "You don't have any injuries. You are completely fine." << endl;
		return;
	}
	if (healthPoints > 7) {
		cout << "You only have some scratches, but nothing important" << endl;
		return;
	}
	if (healthPoints > 5) {
		cout << "You have some injuries, take care." << endl;
		return;
	}

	if (healthPoints < 3) {
		cout << "You almost cannot stand it, you need some bandaje right now!" << endl;
		return;
	}
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
	Entity* entity = nullptr;

	if (same(args[1], "room"))
		entity = parent;

	for (list<Entity*>::const_iterator it = parent->entitiesInside.begin(); it != parent->entitiesInside.cend() && entity == nullptr; ++it) {
		if (same((*it)->name, args[1]))
			entity = (*it);
	}

	for (list<Entity*>::const_iterator it = entitiesInside.begin(); it != entitiesInside.cend() && entity == nullptr; ++it) {
		if (same((*it)->name, args[1]))
			entity = (*it);
		else if ((*it)->type == ITEM && ((Item*)(*it))->itemType == CONTAINER) {
			for (list<Entity*>::const_iterator it2 = (*it)->entitiesInside.begin(); it2 != (*it)->entitiesInside.cend(); ++it2) {
				if (same((*it2)->name, args[1]))
					entity = (*it2);
			}
		}
	}

	if (entity == nullptr) {
		cout << "There's nothing like that in this room" << endl;
		return false;
	}

	switch (entity->type) {
		case CREATURE: {
			cout << "You look closely at " << ((Creature*)entity)->name << endl;
			((Creature*)entity)->status();
			break;
		}
		case ITEM: {
			((Item*)entity)->look();
			if (((Item*)entity)->locked) {
				if (((Item*)entity)->key != nullptr)
					cout << "It needs a key to be opened." << endl;
				else if (((Item*)entity)->puzzle != nullptr && ((Item*)entity)->puzzle->solved == false) {
					((Item*)entity)->puzzle->look();
				}
			}
			else if (((Item*)entity)->itemType == CONTAINER){
				cout << "It contains: " << endl;
				for (list<Entity*>::const_iterator it = ((Item*)entity)->entitiesInside.begin(); it != ((Item*)entity)->entitiesInside.cend(); ++it) {
					cout << (*it)->name << endl;
				}
			}
			break;
		}
		case EXIT: {
			if (((Exit*)entity)->isClosed()) {
				if (((Exit*)entity)->needsKey()) {
					cout << "It seems the exit needs some kind of key to be opened..." << endl;
					return false;
				}
				else if (((Exit*)entity)->puzzle != nullptr && ((Exit*)entity)->puzzle->solved == false) {
					((Exit*)entity)->puzzle->look();
				}
				else {
					cout << "The exit is blocked and you cannot go through it anymore." << endl;
					return false;
				}
			}
			else {
				((Exit*)entity)->look((Room*)parent);
			}
			break;
		}
		case ROOM: {
			((Room*)entity)->look();
			break;
		}
	}

	return true;
}

bool Player::moveItem(const vector<string>& args) {
	Item* item = nullptr;

	for (list<Entity*>::const_iterator it = parent->entitiesInside.begin(); it != parent->entitiesInside.cend() && item == nullptr; ++it) {
		if (same((*it)->name, args[1]) && (*it)->type == ITEM && ((Item*)(*it))->itemType == MOVABLE) {
			item = (Item*)(*it);
			item->effectMovable();
		}
	}

	if (item == nullptr) {
		cout << "You can't find such a thing" << endl;
		return false;
	}
	return true;
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