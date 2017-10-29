#ifndef __Requirements__
#define __Requirements__

#include "puzzle.h"

class Requirements : public Puzzle {

public:
	Requirements(const char* name, const char* description, const PType& puzzleType);
	~Requirements();
	void look() const override;
	void addRequirement(Entity* entity);

public:
	vector<Entity*> entitiesReq;
};

#endif //__Requirements__