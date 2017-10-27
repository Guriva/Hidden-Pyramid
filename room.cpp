#include <iostream>
#include "room.h"
#include "exit.h"
#include "creature.h"
#include "item.h"
#include "globals.h"

using namespace std;

Room::Room(const char* name, const char* description) :
	Entity(name, description,nullptr) {

	type = ROOM;
}

Room::~Room() {

}

void Room::look() const {
	cout << name << endl;
	cout << description << endl;
	bool first = true;

	for (list<Entity*>::const_iterator it = entitiesInside.begin(); it != entitiesInside.cend(); ++it) {
		if ((*it)->type == EXIT) {
			if (first) {
				cout << "Exits here: ";
				lookThing((*it));
				first = false;
			}
			else {
				cout << ", ";
				lookThing((*it));
			}
		}
	}
	if (first == false) cout << endl;
	first = true;

	for (list<Entity*>::const_iterator it = entitiesInside.begin(); it != entitiesInside.cend(); ++it) {
		if ((*it)->type == ENEMY || (*it)->type == CREATURE) {
			if (first) {
				cout << "You see a ";
				lookThing((*it));
				first = false;
			}
			else {
				cout << ", ";
				lookThing((*it));
			}
		}
	}
	if (first == false) cout << endl;
	first = true;

	for (list<Entity*>::const_iterator it = entitiesInside.begin(); it != entitiesInside.cend(); ++it) {
		if ((*it)->type == ITEM) {
			if (first) {
				cout << "Items you can see: ";
				lookThing((*it));
				first = false;
			}
			else {
				cout << ", ";
				lookThing((*it));
			}
		}
	}
	if (first == false) cout << endl;
	cout << endl;
}

Exit* Room::getExit(const string& exit) const {
	for (list<Entity*>::const_iterator it = entitiesInside.begin(); it != entitiesInside.cend(); ++it) {
		if ((*it)->type == EXIT) {
			string exitName = ((Exit*)(*it))->getExitName(this);
			if (same(exitName, exit))
				return ((Exit*)(*it));
		}
	}

	return nullptr;
}

void Room::lookThing(const Entity* entity) const {
	switch (entity->type) {
		case EXIT:
		{
			if (same(((Exit*)entity)->getSource()->name, name))
				cout << ((Exit*)entity)->description;
			else
				cout << ((Exit*)entity)->getSecondDescr();
			break;
		}
		case CREATURE:
		{
			if (((Creature*)entity)->isAlive())
				cout << ((Creature*)entity)->name;
			else
				cout << "corpse of a " << ((Creature*)entity)->name;
			break;
		}
		case ITEM:
		{
			cout << ((Item*)entity)->name;
			break;
		}
	}
}