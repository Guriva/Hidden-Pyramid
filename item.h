#ifndef __Item__
#define __Item__

#include "entity.h"

class Puzzle;
class Creature;

enum IType {
	WEAPON,
	USABLE,
	CONTAINER,
	MOVABLE,
	STATIC
};

class Item : public Entity {

public:
	Item(const char* name, const char* description, Entity* entity, Entity* key, Puzzle* puzzle, IType itemType, const bool carriable = true);
	~Item();
	void look() const override;
	Entity* containedIn() const;
	void setPuzzle(Puzzle* p);
	bool useItem(Creature* entity);
	void effectMovable();

public:
	bool locked;
	bool carriable;
	bool moved;
	unsigned int durability;
	IType itemType;
	Entity* key = nullptr;
	Puzzle* puzzle = nullptr;
};

#endif //__Item__