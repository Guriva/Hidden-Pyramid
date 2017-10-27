#ifndef __Exit__
#define __Exit__

#include "entity.h"

class Room;
class Puzzle;

struct exitData {
	Entity* key;
	Puzzle* puzzle;
	bool onlyPassOnce = false;		//When player goes through, exit is closed
	bool ignoreDestination = false;	//You can't see the exit from the destination room
};

class Exit : public Entity {

public:
	Exit(const char* name, const char* secondRoomExit, const char* description, const char* secondDescr, Room* source, Room* destination, exitData eData);
	~Exit();
	void Update();
	void look(const Room* room) const;
	bool isClosed();
	bool hasPuzzle();
	bool puzzleSolved();
	void lookPuzzle();
	bool needsKey();
	bool isOneWay();
	Room* getSource() const;
	Room* getDestination() const;
	string getSecondDescr() const;
	string getExitName(const Room* room) const;
	void setClosed(const bool b);
	
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