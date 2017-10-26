#ifndef __Entity__
#define __Entity__

#include <string>
#include <list>
#include <vector>

using namespace std;

enum EType {
	CREATURE,
	PLAYER,
	PUZZLE,
	EXIT,
	ROOM,
	ITEM,
	ENTITY
};

class Entity {

public:
	Entity(const char* name, const char* description, Entity* parent);
	virtual ~Entity();
	virtual void Update();
	virtual void look() const;

	void newParent(Entity* p);

public:
	EType type;
	string name;
	string description;
	list<Entity*> entitiesInside;		//(Possible change to vector, depending on the future use)
	Entity* parent = nullptr;
};

#endif //__Entity__