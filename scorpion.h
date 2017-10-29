#ifndef __Scorpion__
#define __Scorpion__

#include "creature.h"

class Scorpion : public Creature {

public:
	Scorpion(const char* name, const char* description, Entity* entity, const bool& autoRespawn = false);
	~Scorpion();
	bool Update(const float& frameTime) override;
	void updateCds();
	void attack() const;

private:
	int damage;
	bool autoRespawn;
	float cdAvoid, cdAvoidLeft, cdAvoidTime, cdAvoidTimeLeft;
	float cdAttack, minCdAttack, maxCdAttack, cdAttackLeft;
	float frameTime;
};

#endif //__Scorpion__