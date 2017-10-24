#ifndef __Item__
#define __Item__

#include "entity.h"

class Item : public Entity {

public:
	Item(const char* name, const char* description, Entity* entity);
	~Item();
	void look() const;
	Entity* GetParent() const;

private:
	Entity* entityContainedIn;
};

#endif //__Item__