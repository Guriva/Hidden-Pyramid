#include <iostream>
#include "entity.h"

Entity::Entity(const char* name, const char* description) :
	name(name),description(description) {

	type = ENTITY;
}

Entity::~Entity() {

}

void Entity::Update() {

}

EType Entity::GetType() const {
	return type;
}

string Entity::GetName() const {
	return name;
}

string Entity::GetDescription() const {
	return description;
}

