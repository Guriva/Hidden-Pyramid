#ifndef __Requirements__
#define __Requirements__

#include "puzzle.h"

class Requirements : public Puzzle {

public:
	Requirements(const char* name, const char* description, PType puzzleType);
	~Requirements();
	void addRequirement(Entity* entity);
	bool hasRequirements();
private:
	vector<Entity*> entitiesReq;
};

#endif //__Requirements__