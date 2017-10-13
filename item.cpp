#include "item.h"

Item::Item(const char* name, const char* description, Entity* entity) :
	Entity(name,description), entityContainedIn(entity){

	type = ITEM;
}

Item::~Item() {

}
void Item::Look() const {

}

Entity* Item::GetParent() const {
	return entityContainedIn;
}