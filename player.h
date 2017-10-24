#ifndef __Player__
#define __Player__

#include "creature.h"

class Room;

class Player : public Creature {

public:
	Player(const char* name, const char* description, Room* room);
	~Player();
	void look() const;

private:

};

#endif //__Player__