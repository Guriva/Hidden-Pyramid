#ifndef __Room__
#define __Room__

#include "entity.h"

class Room : public Entity {

public:
	Room(const char* name, const char* description);
	~Room();
	void look() const override;

private:
	void lookThing(const Entity* entity) const;

private:
};

#endif //__Room__