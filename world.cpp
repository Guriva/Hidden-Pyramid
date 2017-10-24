#include "world.h"
#include "room.h"
#include "exit.h"
#include "creature.h"
#include "player.h"

World::World() {
	Room* room1 = new Room("Outside", "You are outside. You can see the big pyramid in front of you.");
	Room* room2 = new Room("Inside", "Your are inside the pyramid. The walls are decorated with strange symbols.");
	Exit* exit1 = new Exit("Main pyramid entrance","Small structure of stones that leads inside the pyramid",room1,room2,BOTH);
	player = new Player("Player","",room1);

	entities.push_back(room1);
	entities.push_back(room2);
	entities.push_back(exit1);
}

World::~World() {

	for (unsigned int i = 0; i < entities.size(); ++i)
		delete entities[i];

	entities.clear();
}

bool World::Update(vector<string>& args) {
	bool ret = true;

	if (args.size() > 0 && args[0].length() > 0)
		ret = getInput(args);

	entitiesUpdate();

	return ret;
}

void World::entitiesUpdate() {
	for (unsigned int i = 0; i < entities.size(); ++i) {
		entities[i]->Update();
	}
}

bool World::getInput(const vector<string>& args) {
	bool ret = true;

	switch (args.size()) {
		case 1:
		{
			/*if (stricmp(args[0].c_str(), "look") || stricmp(args[0].c_str(), "l")) {
				player->look(args);
			}

			else if (stricmp(args[0].c_str(), "north") || stricmp(args[0].c_str(), "n")) {
				player->move(args);
			}*/
		}
	}

	return ret;
}