#include <iostream>
#include "item.h"
#include "puzzle.h"
#include "creature.h"
#include "globals.h"

Item::Item(const char* name, const char* description, Entity* entity, Entity* key, Puzzle* puzzle, IType itemType, const bool carriable) :
	Entity(name,description, (Entity*)entity), key(key), puzzle(puzzle), locked(false), itemType(itemType), carriable(carriable) {

	type = ITEM;
	if (key != nullptr || (puzzle != nullptr && !puzzle->isSolved())) {
		locked = true;
	}
	moved = false;
}

Item::~Item() {

}
void Item::look() const {

	cout << "You see a " << name << endl;
	cout << description << endl;

	if (itemType == CONTAINER) {
		cout << "It may contains something inside" << endl;
	}
}

Entity* Item::containedIn() const {
	return parent;
}

void Item::setPuzzle(Puzzle* p) {
	puzzle = p;
	if (puzzle->isSolved() == false && locked == false)
		locked = true;
}

void Item::setKey(Item* item) {
	key = item;
	if (locked == false)
		locked = true;
}

bool Item::useItem(Creature* entity) {
	if (same(this->name, "bandaje")) {
		if (entity->healthPoints < entity->maxHealth) {
			entity->healthPoints += 1;
			cout << "You have used a bandaje and recovered a little.";
			return true;
		}
		else {
			cout << "You are already fine, no need to use a bandaje" << endl;
			return false;
		}
	}

	cout << "You cannot use this item on yourself" << endl;
	return false;
}

void Item::effectMovable() {
	if (same(name, "rock") && moved == false) {
		moved = true;
		cout << "You move the rock to a side..." << endl;
		if (entitiesInside.size() > 0) {
			cout << "You discover something under the rock:" << endl;
			for (list<Entity*>::const_iterator it = entitiesInside.begin(); it != entitiesInside.cend(); ++it) {
				if (parent != nullptr) {
					if ((*it)->type == CREATURE)
						cout << "A wild " << (*it)->name << " has appeared!" << endl;
					else
						cout << "a " << (*it)->name << endl;
					(*it)->parent = parent;
					parent->entitiesInside.push_back((*it));
				}
			}
			entitiesInside.clear();
		}
	}
	else
		cout << "You already moved that object." << endl;
}