#ifndef __Item__
#define __Item__

#include "entity.h"

class Puzzle;

enum IType {
	WEAPON,
	USABLE,
	CONTAINER,

};

class Item : public Entity {

public:
	Item(const char* name, const char* description, Entity* entity, const bool carriable = true, Entity* key = nullptr, Puzzle* puzzle = nullptr);
	~Item();
	void look() const override;
	Entity* containedIn() const;
	bool isLocked() const;

private:
	bool locked;
	bool carriable;
	Entity* key;
	Puzzle* puzzle;
};

#endif //__Item__