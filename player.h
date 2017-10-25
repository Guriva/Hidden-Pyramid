#ifndef __Player__
#define __Player__

#include "creature.h"

class Room;

class Player : public Creature {

public:
	Player(const char* name, const char* description, Room* room);
	~Player();
	void Update();
	bool look(const vector<string>& args) const override;
	void move(const vector<string>& args) override;

private:

};

#endif //__Player__