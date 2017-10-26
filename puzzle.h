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
	void look() const override;
	bool isSolved() const;

private:
	PType puzzleType;
	bool solved;
};

#endif //__Puzzle__