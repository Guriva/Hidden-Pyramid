#ifndef __Mummy__
#define __Mummy__

#include "creature.h"

class Mummy : public Creature {

public:
	Mummy(const char* name, const char* description, Entity* entity, const bool& autoRespawn = false);
	~Mummy();
	bool Update(const float& frameTime) override;
	void updateCds();
	void attack() const;
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