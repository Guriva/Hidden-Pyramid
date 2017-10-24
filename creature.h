#ifndef __Creature__
#define __Creature__

#include "entity.h"

class Room;

class Creature : public Entity {

public:
	Creature(const char* name, const char* description, Room* room);
	~Creature();
	void look() const;
	Room* GetRoom() const;
	int GetHealth() const;

protected:
	Room* room;
	int healthPoints;
};

#endif //__Creature__