#ifndef __Creature__
#define __Creature__

#include "entity.h"

class Room;

class Creature : public Entity {

public:
	Creature(const char* name, const char* description, Room* room);
	~Creature();
	virtual void Update();
	virtual bool look(const vector<string>& args) const;
	virtual void move(const vector<string>& args);
	Room* getRoom() const;
	int getHealth() const;
	bool isAlive() const;
	bool isEnemy() const;

protected:
	int healthPoints;
	bool inCombat;
	bool enemy;
};

#endif //__Creature__