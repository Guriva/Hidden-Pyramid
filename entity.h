#ifndef __Entity__
#define __Entity__

#include <string>
#include <list>

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
	Entity(const char* name, const char* description);
	virtual ~Entity();
	virtual void Update();
	virtual void look() const = 0;
	EType GetType() const;
	string GetName() const;
	string GetDescription() const;

protected:
	EType type;
	string name;
	string description;
	list<Entity*> entitiesInside;		//(Possible change to vector, depending on the future use)
};

#endif //__Entity__