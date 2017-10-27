#ifndef __Requirements__
#define __Requirements__

#include "puzzle.h"

class Requirements : public Puzzle {

public:
	Requirements(const char* name, const char* description, PType puzzleType);
	~Requirements();
	void look() const;
	void addRequirement(Entity* entity);

public:
	vector<Entity*> entitiesReq;
};

#endif //__Requirements__