#ifndef __Puzzle__
#define __Puzzle__

#include "entity.h"

class Room;

class Puzzle : public Entity {

public:
	Puzzle(const char* name, const char* description, Room* room);
	~Puzzle();
	void look() const override;
	bool isSolved() const;

private:
	bool solved;
};

#endif //__Puzzle__