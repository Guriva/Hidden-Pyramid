#include <iostream>
#include "entity.h"
#include "globals.h"

Entity::Entity(const char* name, const char* description, Entity* parent) :
	name(name),description(description),parent(parent) {

	if (parent != nullptr)
		parent->entitiesInside.push_back(this);

	type = ENTITY;
}

Entity::~Entity() {

}

bool Entity::Update(const float& frameTime) {
	return false;
}

void Entity::look() const {
	cout << "You see " << name << endl;
	cout << description << endl;
}

Entity* Entity::findInsideOf(Entity* e, const string& args) const {
	Entity* entity = nullptr;

	for (list<Entity*>::const_iterator it = e->entitiesInside.begin(); it != e->entitiesInside.cend(); ++it) {
		if (same((*it)->name, args))
			entity = (*it);
	}

	return entity;
}

void Entity::newParent(Entity* p) {
	if (parent != nullptr)
		parent->entitiesInside.remove(this);
	parent = p;
	if (p != nullptr) {
		parent->entitiesInside.push_back(this);
	}
}