#ifndef __Puzzle__
#define __Puzzle__

#include "entity.h"

class Room;

class Puzzle : public Entity {

public:
	Puzzle(const char* name, const char* description);
	~Puzzle();
	void look() const;

private:
	Room* room;
	bool solved;
};

#endif //__Puzzle__