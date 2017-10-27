#ifndef __Puzzle__
#define __Puzzle__

#include "entity.h"

class Room;

enum PType {
	REQUIREMENTS,
	MORSE,
	BOTTLES
};

class Puzzle : public Entity {

public:
	Puzzle(const char* name, const char* description, PType puzzleType);
	~Puzzle();
	virtual void look() const;
	virtual bool checkAnswer(const vector<string>& args);
	virtual void unlockRules();
	bool isSolved() const;

public:
	PType puzzleType;
	bool solved = false;
};

#endif //__Puzzle__