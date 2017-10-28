#ifndef __Scorpion__
#define __Scorpion__

#include "creature.h"

class Scorpion : public Creature {

public:
	Scorpion(const char* name, const char* description, Entity* entity, bool autoRespawn = false);
	~Scorpion();
	bool Update(float frameTime);
	void updateCds();
	void attack();

private:
	int damage;
	bool autoRespawn;
	float cdAvoid, cdAvoidLeft, cdAvoidTime, cdAvoidTimeLeft;
	float cdAttack, minCdAttack, maxCdAttack, cdAttackLeft;
	float frameTime;
};

#endif //__Scorpion__