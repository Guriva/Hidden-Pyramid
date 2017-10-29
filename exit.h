#ifndef __Exit__
#define __Exit__

#include "entity.h"

class Room;
class Puzzle;

struct exitData {
	Entity* key = nullptr;
	Puzzle* puzzle = nullptr;
	bool onlyPassOnce = false;		//When player goes through, exit is closed
	bool ignoreDestination = false;	//You can't see the exit from the destination room
};

class Exit : public Entity {

public:
	Exit(const char* name, const char* secondRoomExit, const char* description, const char* secondDescr, Room* source, Room* destination, const exitData& eData);
	~Exit();
	void look(const Room* room) const;
	string getExitName(const Room* room) const;
	
public:
	bool locked;
	bool onlyPassOnce;
	string secondRoomExit;
	string secondDescription;
	Room* destination = nullptr;
	Entity* key = nullptr;
	Puzzle* puzzle = nullptr;
};

#endif //__Exit__