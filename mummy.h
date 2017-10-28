#ifndef __Mummy__
#define __Mummy__

#include "creature.h"

class Mummy : public Creature {

public:
	Mummy(const char* name, const char* description, Entity* entity, bool autoRespawn = false);
	~Mummy();
	bool Update(float frameTime);
	void updateCds();
	void attack();
	void increaseMinCdAttack();

public:
	bool blind;

private:
	int damage;
	bool avoiding;
	bool autoRespawn;
	float cdAvoid, cdAvoidLeft, cdAvoidTime, cdAvoidTimeLeft;
	float cdAttack, minCdAttack, maxCdAttack, cdAttackLeft;
	float frameTime;
};

#endif //__Mummy__