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
	virtual bool move(const vector<string>& args);
	virtual bool use(const vector<string>& args);
	virtual bool attack(const vector<string>& args);
	virtual bool drop(const vector<string>& args);
	virtual bool take(const vector<string>& args);
	virtual bool put(const vector<string>& args);
	virtual bool unlock(const vector<string>& args);
	virtual void status() const;
	virtual void inventory() const;
	Room* getRoom() const;
	int getHealth() const;
	bool isAlive() const;
	bool isEnemy() const;

public:
	int healthPoints;
	int maxHealth;
	bool inCombat;
	bool enemy;
};

#endif //__Creature__