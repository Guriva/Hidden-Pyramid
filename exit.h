#ifndef __Exit__
#define __Exit__

#include "entity.h"

class Room;
class Puzzle;

class Exit : public Entity{

public:
	Exit(const char* name, const char* secondRoomExit, const char* description, const char* secondDescr, Room* source, Room* destination, Entity* key = nullptr, Puzzle* puzzle = nullptr);
	~Exit();
	void look(const Room* room) const;
	Room* getSource() const;
	Room* getDestination() const;
	string getSecondDescr() const;
	
protected:
	bool closed;
	string secondRoomExit;
	string secondDescription;
	Room* destination = nullptr;
	Entity* key;
	Puzzle* puzzle;
};

#endif //__Exit__