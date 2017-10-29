#ifndef __Creature__
#define __Creature__

#include "entity.h"

class Room;

class Creature : public Entity {

public:
	Creature(const char* name, const char* description, Entity* room);
	~Creature();
	virtual bool Update(const float& frameTime) override;
	virtual bool look(const vector<string>& args) const;
	virtual bool attack(const vector<string>& args);
	virtual void status() const;
	Creature* findPlayer(const Entity* entity) const;
	bool isAlive() const;

public:
	int healthPoints;
	int maxHealth;
	bool inCombat;
	bool avoiding;
	Creature* target = nullptr;
};

#endif //__Creature__