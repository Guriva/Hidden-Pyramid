#ifndef __Exit__
#define __Exit__

#include "entity.h"

class Room;

enum direction {
	ORIGIN,
	DESTINATION,
	BOTH
};

class Exit : public Entity{

public:
	Exit(const char* name, const char* description, Room* source, Room* destination, const direction dir);
	~Exit();
	void Look() const;
	Room* GetSource() const;
	Room* GetDestination() const;
	direction GetDirection() const;
	
private:
	Room* source;
	Room* destination;
	direction dir;
};

#endif __Exit__