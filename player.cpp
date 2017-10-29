#include <iostream>
#include <algorithm>
#include "player.h"
#include "room.h"
#include "exit.h"
#include "item.h"
#include "puzzle.h"
#include "requirements.h"
#include "morse.h"
#include "bottlePuzzle.h"
#include "mummy.h"
#include "globals.h"

Player::Player(const char* name, const char* description, Room* room) :
	Creature(name,description,room){

	type = PLAYER;
	statePlayer = WAITING;
	healthPoints = 10;
	maxHealth = 10;
	maxInventory = 3;
	cdAvoid = 6.f;
	cdAvoidLeft = 6.f;
	cdAvoidTime = 2.f;
	cdAvoidTimeLeft = 2.f;
}

Player::~Player() {

}

bool Player::Update(const float& frameTime) {
	if (inCombat) {
		if (cdAvoidLeft > 0.f)
			cdAvoidLeft -= frameTime;
		if (avoiding && cdAvoidTimeLeft > 0.f)
			cdAvoidTimeLeft -= frameTime;
		if (cdAvoidTimeLeft <= 0.f) {
			avoiding = false;
			cdAvoidTimeLeft = cdAvoidTime;
			cout << "\nYou lose your focus to avoid the next attack" << endl;
			return true;
		}
	}

	if (isAlive() == false) {
		statePlayer = DEAD;
	}
	return false;
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
		Entity* entity = nullptr;
		entity = findInInventory(args[1]);

		if (entity != nullptr) {
			entity->look();
			return true;
		}
		entity = findInsideOf(parent,args[1]);

		if (entity != nullptr) {
			if (entity->type == EXIT) {
				((Exit*)entity)->look((Room*)parent);
				return true;
			}
			else {
				entity->look();
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
			e = ((Room*)parent)->getExit(args[0]);
			exitName = args[0];
			break;
		}
		
		case 2: {
			e = ((Room*)parent)->getExit(args[1]);
			exitName = args[1];
			break;
		}
	}

	if (e == nullptr) {
		cout << "You cannot go that way" << endl;
		return false;
	}

	if (e->locked == true) {
		if (e->key != nullptr) {
			cout << "It seems the exit needs some kind of key to be opened..." << endl;
			return false;
		}
		else if (e->puzzle != nullptr && e->puzzle->solved == false) {
			if (checkPuzzle(e->puzzle) == false)
				return false;
			else {
				e->puzzle = nullptr;
				e->locked = false;
			}
		}
		else {
			cout << "The exit is blocked and you cannot go through it anymore." << endl;
			return false;
		}
	}

	cout << "You go to the " << exitName << endl;
	Room* r;
	(same(e->parent->name,parent->name)) ? r = e->destination : r = (Room*)e->parent;
	newParent(r);

	if (e->onlyPassOnce)
		e->locked = true;

	parent->look();
	
	return true;
}

bool Player::use(const vector<string>& args) {
	bool ret = false;
	Entity* entity = nullptr;
	entity = findInInventory(args[1]);

	if (entity != nullptr && entity->type == ITEM) {
		ret = true;
		if (((Item*)entity)->useItem(this)) {
			entity->newParent(nullptr);
			return true;
		}
	}

	if (ret == false) {
		cout << "You don't have that object in your inventory" << endl;
	}
	return false;
}

bool Player::attack(const vector<string>& args) {

	if (args.size() == 4 && same(args[2], "with")) {

		Entity* item = nullptr;
		Creature* creature = nullptr;
		item = findInInventory(args[3]);

		if (item == nullptr || (item->type == ITEM && ((Item*)item)->itemType != WEAPON)) {
			cout << "You don't have that item!" << endl;
			return false;
		}

		for (list<Entity*>::const_iterator it = parent->entitiesInside.begin(); it != parent->entitiesInside.cend() && creature == nullptr; ++it) {
			if ((*it)->type == CREATURE && same(args[1], (*it)->name))
				creature = (Creature*)(*it);
		}

		if (creature == nullptr) {
			cout << "You can't see such a creature around here" << endl;
			return false;
		}
		if (creature->isAlive() == false) {
			cout << "That creature is dead" << endl;
			return false;
		}
		else {
			if (target->inCombat == false) {
				target = creature;
				target->inCombat = true;
				inCombat = true;
				target->target = this;
			}
			if (target->avoiding == true) {
				cout << "You cannot reach the target to attack it!" << endl;
				return false;
			}
			if (same(item->name, "lantern") && same(target->name, "mummy") && ((Mummy*)target)->blind == false) {
				((Mummy*)target)->increaseMinCdAttack();
				((Mummy*)target)->blind = true;
				cout << "You use the lantern against the mummy, and it makes their attacks more predictable" << endl;
			}
			else if (same(item->name, "knife")) {
				target->healthPoints -= 2;
				cout << "You attack " << target->name << " with a knife dealing some damage" << endl;
			}
			else if (same(item->name, "stick")) {
				target->healthPoints -= 1;
				cout << "You attack " << target->name << " with a stick, dealing minor damage" << endl;
			}
			else {
				cout << "You cannot attack with this item to this creature!" << endl;
				return false;
			}
			if (target->isAlive() == false) {
				cout << "You killed the " << target->name << endl;
				target = nullptr;
				inCombat = false;
			}
			return true;
		}
	}
	return false;
}

bool Player::avoid(const vector<string>& args) {
	if (inCombat == true) {
		if (cdAvoidLeft <= 0.f && avoiding == false) {
			avoiding = true;
			cdAvoidLeft = cdAvoid;
			cout << "You prepare to avoid the next attack" << endl;
			return true;
		}
		else {
			if (avoiding == true) {
				cout << "You are already prepared to avoid" << endl;
				return false;
			}
			else {
				cout << "You must relax before preparing to avoid an attack" << endl;
				return false;
			}
		}
	}
	cout << "You are not in combat" << endl;
	return false;
}

bool Player::drop(const vector<string>& args) const {
	Entity* entity = nullptr;
	entity = findInInventory(args[1]);
	
	if (entity == nullptr || entity->type != ITEM) {
		cout << "You don't have that item in your inventory" << endl;
		return false;
	}

	cout << "You dropped " << entity->name << endl;
	entity->newParent(parent);

	return true;
}

bool Player::take(const vector<string>& args) {
	if (args.size() == 2)
	{
		Entity* item = nullptr;
		item = findInsideOf(parent,args[1]);

		if (item == nullptr || item->type != ITEM) {
			cout << "You can't find such an item" << endl;
			return false;
		}

		if (((Item*)item)->carriable == false) {
			cout << "You cannot take that item with you." << endl;
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
			if (same(item->name, "Treasure"))
				statePlayer = WIN;
		}
	}
	else if (args.size() == 4)
	{
		Entity* itemContainer = nullptr;
		Entity* item = nullptr;
		if (same(args[3], "inventory")) {
			cout << "That doesn't make any sense..." << endl;
			return false;
		}
		itemContainer = findInsideOf(parent,args[3]);

		if (itemContainer == nullptr || itemContainer->type != ITEM || (itemContainer->type == ITEM && ((Item*)itemContainer)->itemType != CONTAINER)) {
			cout << "You cannot find any " << args[3] << endl;
			return false;
		}
		if (((Item*)itemContainer)->locked == true) {
			cout << "The " << itemContainer->name << " seems locked" << endl;
			return false;
		}
		item = findInsideOf(itemContainer,args[1]);

		if (item == nullptr || item->type != ITEM || (item->type == ITEM && ((Item*)item)->carriable == false)) {
			cout << "You can't find such an item from " << itemContainer->name << endl;
			return false;
		}

		// If you don't have space, look for a container in your inventory
		if (entitiesInside.size() >= maxInventory) {
			for (list<Entity*>::const_iterator it = entitiesInside.begin(); it != entitiesInside.cend(); ++it) {
				if ((*it)->type == ITEM && ((Item*)(*it))->itemType == CONTAINER) {
					cout << "You have taken " << item->name << " and put it inside the " << (*it)->name << endl;
					item->newParent((*it));
					if (same(item->name, "Treasure"))
						statePlayer = WIN;
					return true;
				}
			}
			cout << "You don't have space in your inventory" << endl;
			return false;
		}
		else {
			cout << "You have taken " << item->name << endl;
			if (same(item->name, "Treasure"))
				statePlayer = WIN;
			item->newParent(this);
		}
	}

	return true;
}

bool Player::put(const vector<string>& args) const {
	Entity* item = nullptr;
	Entity* entity = nullptr;
	item = findInInventory(args[1]);

	if (item == nullptr || item->type != ITEM) {
		cout << "You don't have that item in your inventory" << endl;
		return false;
	}
	entity = findInsideOf(parent,args[3]);

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
	for (list<Entity*>::const_iterator it = parent->entitiesInside.begin(); it != parent->entitiesInside.cend(); ++it) {

		if (same(args[1], (*it)->name) && (*it)->type == ITEM && ((Item*)(*it))->locked) {
			if (((Item*)(*it))->key != nullptr) {
				return unlockItemKey((Item*)(*it));
			}
			else if (((Item*)(*it))->puzzle != nullptr && ((Item*)(*it))->puzzle->solved == false) {
				if (checkPuzzle(((Item*)(*it))->puzzle)) {
					cout << "You meet the requirements to pass through." << endl;
					return true;
				}
				statePlayer = SOLVING;
				entityUnlocking = ((Item*)(*it));
				((Item*)(*it))->puzzle->unlockRules();
				return true;
				//change player state to solving and waiting for an answer
				
			}
			else {
				cout << "This item cannot be unlocked." << endl;
				return false;
			}
		}

		if (same(args[1], (*it)->name) && (*it)->type == EXIT && ((Exit*)(*it))->locked) {
			if (((Exit*)(*it))->key != nullptr) {
				return unlockExitKey((Exit*)(*it));
			}
			else if (((Exit*)(*it))->puzzle != nullptr && ((Exit*)(*it))->puzzle->solved == false) {
				if (checkPuzzle(((Exit*)(*it))->puzzle)) {
					cout << "You meet the requirements to pass through." << endl;
					return true;
				}
				statePlayer = SOLVING;
				entityUnlocking = ((Exit*)(*it));
				((Exit*)(*it))->puzzle->unlockRules();
				return true;
			}
			else {
				cout << "This exit cannot be unlocked." << endl;
				return false;
			}
		}
	}

	cout << "You don't find such a thing to unlock" << endl;
	return false;
}

bool Player::unlockExitKey(Exit* exit) const {
	for (list<Entity*>::const_iterator it = entitiesInside.begin(); it != entitiesInside.cend(); ++it) {
		if ((*it)->type == ITEM && exit->key == (*it)) {
			cout << "You use the key " << (*it)->name << " on " << exit->name << endl;
			exit->key = nullptr;
			(*it)->newParent(nullptr);
			if (exit->puzzle == nullptr)
				exit->locked = false;
			return true;
		}
		else if ((*it)->type == ITEM && ((Item*)(*it))->itemType == CONTAINER) {
			for (list<Entity*>::const_iterator it2 = (*it)->entitiesInside.begin(); it2 != (*it)->entitiesInside.cend(); ++it2) {
				if ((*it2)->type == ITEM && exit->key == (*it2)) {
					cout << "You use the key " << (*it2)->name << " on " << exit->name << endl;
					exit->key = nullptr;
					(*it2)->newParent(nullptr);
					if (exit->puzzle == nullptr)
						exit->locked = false;
					return true;
				}
			}
		}
	}

	cout << "You don't have the key to unlock the exit" << endl;
	return false;
}

bool Player::unlockItemKey(Item* item) const {
	for (list<Entity*>::const_iterator it = entitiesInside.begin(); it != entitiesInside.cend(); ++it) {
		if ((*it)->type == ITEM && item->key == (*it)) {
			cout << "You use the key " << (*it)->name << " on " << item->name << endl;
			item->key = nullptr;
			(*it)->newParent(nullptr);
			if (item->puzzle == nullptr)
				item->locked = false;
			return true;
		}
		else if ((*it)->type == ITEM && ((Item*)(*it))->itemType == CONTAINER) {
			for (list<Entity*>::const_iterator it2 = (*it)->entitiesInside.begin(); it2 != (*it)->entitiesInside.cend(); ++it2) {
				if ((*it2)->type == ITEM && item->key == (*it2)) {
					cout << "You use the key " << (*it2)->name << " on " << item->name << endl;
					item->key = nullptr;
					(*it2)->newParent(nullptr);
					if (item->puzzle == nullptr)
						item->locked = false;
					return true;
				}
			}
		}
	}

	cout << "You don't have the key to unlock the item" << endl;
	return false;
}

void Player::status() const {
	if (healthPoints == 10) {
		cout << "You don't have any injuries. You are completely fine." << endl;
		return;
	}
	if (healthPoints > 6) {
		cout << "You only have some scratches, but nothing important" << endl;
		return;
	}
	if (healthPoints > 3) {
		cout << "You have some injuries, take care." << endl;
		return;
	}
	if (healthPoints > 0) {
		cout << "You almost cannot stand it, you need some bandaje right now!" << endl;
		return;
	}
}

bool Player::solve(const vector<string>& args) {
	statePlayer = WAITING;
	if (entityUnlocking == nullptr)
		return false;

	if (entityUnlocking->type == EXIT) {
		if (((Exit*)entityUnlocking)->puzzle->checkAnswer(args)) {
			((Exit*)entityUnlocking)->puzzle = nullptr;
			((Exit*)entityUnlocking)->locked = false;
			return true;
		}
	}
	else if (entityUnlocking->type == ITEM) {
		if (((Item*)entityUnlocking)->puzzle->checkAnswer(args)) {
			((Item*)entityUnlocking)->puzzle = nullptr;
			((Item*)entityUnlocking)->locked = false;
			return true;
		}
	}
	return false;
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
	if (same(args[1], "room")) {
		parent->look();
		return true;
	}
	Entity* entity = nullptr;
	entity = findInsideOf(parent,args[1]);
	if (entity == nullptr)
		entity = findInInventory(args[1]);

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
				else {
					cout << "This item is locked completely and cannot be opened" << endl;
					return false;
				}
			}
			else if (((Item*)entity)->itemType == CONTAINER) {
				if (((Item*)entity)->entitiesInside.size() > 0) {
					cout << "It contains: " << endl;
					for (list<Entity*>::const_iterator it = ((Item*)entity)->entitiesInside.begin(); it != ((Item*)entity)->entitiesInside.cend(); ++it) {
						cout << (*it)->name << endl;
					}
				}
				else {
					cout << "But there's nothing inside" << endl;
				}
			}
			break;
		}
		case EXIT: {
			if (((Exit*)entity)->locked == true) {
				if (((Exit*)entity)->key != nullptr) {
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

bool Player::moveItem(const vector<string>& args) const {

	if (inCombat) {
		cout << "You are being attacked right now, watch your back!" << endl;
		return false;
	}

	Entity* item = nullptr;
	item = findInsideOf(parent,args[1]);

	if (item == nullptr || item->type != ITEM || (item->type == ITEM && ((Item*)item)->itemType != MOVABLE)) {
		cout << "You can't find such a thing" << endl;
		return false;
	}
	((Item*)item)->effectMovable();
	return true;
}

bool Player::checkPuzzle(const Puzzle* puzzle) const {
	switch (puzzle->puzzleType) {
		case REQUIREMENTS: {
			// check if player has every object that requirements asks for
			for (unsigned int i = 0; i < ((Requirements*)puzzle)->entitiesReq.size(); ++i) {
				if (itContains(((Requirements*)puzzle)->entitiesReq[i]) == false) {
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

bool Player::itContains(const Entity* entity) const {
	for (list<Entity*>::const_iterator it = entitiesInside.begin(); it != entitiesInside.cend(); ++it) {
		if (same((*it)->name, entity->name))
			return true;
		if ((*it)->type == ITEM && ((Item*)(*it))->itemType == CONTAINER) {
			for (list<Entity*>::const_iterator it2 = (*it)->entitiesInside.begin(); it2 != (*it)->entitiesInside.cend(); ++it2) {
				if (same((*it2)->name, entity->name))
					return true;
			}
		}
	}
	return false;
}

Entity* Player::findInInventory(const string& args) const {
	Entity* entity = nullptr;

	for (list<Entity*>::const_iterator it = entitiesInside.begin(); it != entitiesInside.cend(); ++it) {
		if (same((*it)->name, args))
			entity = (*it);
		if ((*it)->type == ITEM && ((Item*)(*it))->itemType == CONTAINER) {
			for (list<Entity*>::const_iterator it2 = (*it)->entitiesInside.begin(); it2 != (*it)->entitiesInside.cend(); ++it2) {
				if (same((*it2)->name, args))
					entity = (*it2);
			}
		}
	}

	return entity;
}