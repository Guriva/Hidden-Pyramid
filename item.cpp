#include <iostream>
#include "item.h"
#include "puzzle.h"
#include "creature.h"

Item::Item(const char* name, const char* description, Entity* entity, Entity* key, Puzzle* puzzle, IType itemType, const bool carriable) :
	Entity(name,description, (Entity*)entity), key(key), puzzle(puzzle), locked(false), itemType(itemType), carriable(carriable) {

	type = ITEM;
	if (key != nullptr || (puzzle != nullptr && !puzzle->isSolved())) {
		locked = true;
	}
}

Item::~Item() {

}
void Item::look() const {

	cout << "You see a " << name << endl;
	cout << description << endl;

	if (itemType == CONTAINER) {
		cout << "It may contains something inside" << endl;
	}

	/*This below needs to go when an item can be opened and it's opened*/

	/*if (entitiesInside.size() > 0 && !locked) {
		//Check for monsters inside items. If found one alive, it attacks the player
		for (list<Entity*>::const_iterator it = entitiesInside.begin(); it != entitiesInside.cend(); ++it) {
			if ((*it)->type == CREATURE && (Creature*)(*it)->enemy && !(Creature*)(*it)->inCombat) {

			}
			//TODO: check first if there is a creature. If true, the first creature attacks the player
		}
	}*/
}

Entity* Item::containedIn() const {
	return parent;
}

bool Item::isLocked() const {
	return locked;
}

void Item::setPuzzle(Puzzle* p) {
	puzzle = p;
	if (puzzle->isSolved() == false && locked == false)
		locked = true;
}