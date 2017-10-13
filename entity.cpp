#include "entity.h"

Entity::Entity(const char* name, const char* description) :
	name(name),description(description) {

	type = ENTITY;
}

Entity::~Entity() {

}

void Entity::Update() {

}

void Entity::Look() const {

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

