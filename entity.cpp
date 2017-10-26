#include <iostream>
#include "entity.h"

Entity::Entity(const char* name, const char* description, Entity* parent) :
	name(name),description(description),parent(parent) {

	if (parent != nullptr)
		parent->entitiesInside.push_back(this);

	type = ENTITY;
}

Entity::~Entity() {

}

void Entity::Update() {

}

void Entity::look() const {
	cout << "You see " << name << endl;
	cout << description << endl;
}

void Entity::newParent(Entity* p) {
	if (parent != nullptr)
		parent->entitiesInside.remove(this);
	parent = p;
	if (p != nullptr) {
		parent->entitiesInside.push_back(this);
	}
}