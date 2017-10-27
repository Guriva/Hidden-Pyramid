#ifndef __Snake__
#define __Snake__

#include "creature.h"

class Snake : public Creature {

public:
	Snake(const char* name, const char* description, Room* room, bool autoRespawn = false);
	~Snake();
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

#endif //__Snake__