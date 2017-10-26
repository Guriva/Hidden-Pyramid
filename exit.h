#ifndef __Exit__
#define __Exit__

#include "entity.h"

class Room;
class Puzzle;

struct exitData {
	Entity* key;
	Puzzle* puzzle;
	const bool onlyPassOnce = false;
	bool ignoreDestination = false;
};

class Exit : public Entity {

public:
	Exit(const char* name, const char* secondRoomExit, const char* description, const char* secondDescr, Room* source, Room* destination, exitData eData);
	~Exit();
	void Update();
	void look(const Room* room) const;
	Room* getSource() const;
	Room* getDestination() const;
	string getSecondDescr() const;
	
protected:
	bool closed;
	bool onlyPassOnce;
	string secondRoomExit;
	string secondDescription;
	Room* destination = nullptr;
	Entity* key = nullptr;
	Puzzle* puzzle = nullptr;
};

#endif //__Exit__