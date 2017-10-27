#ifndef __Puzzle__
#define __Puzzle__

#include "entity.h"

class Room;

enum PType {
	REQUIREMENTS,
	MORSE
};

class Puzzle : public Entity {

public:
	Puzzle(const char* name, const char* description, PType puzzleType);
	~Puzzle();
	virtual void look() const;
	bool isSolved() const;

public:
	PType puzzleType;
	bool solved;
};

#endif //__Puzzle__