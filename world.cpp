#include "world.h"
#include "room.h"
#include "exit.h"
#include "creature.h"
#include "player.h"
#include "globals.h"

World::World() {
	Room* room1 = new Room("Outside", "You are outside. You can see the big pyramid in front of you.");
	Room* room2 = new Room("Inside", "Your are inside the pyramid. The walls are decorated with strange symbols.");
	Exit* exit1 = new Exit("east", "west", "Small structure of stones that leads inside the pyramid to the east",
		"Small structure of stones that leads outside of the pyramid to the west",room1,room2,BOTH);
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
			if (same(args[0],"look") || same(args[0], "l")) {
				ret = player->look(args);
			}
			else if (same(args[0], "north") || same(args[0], "n")) {
				player->move(args);
			}
			else if (same(args[0], "south") || same(args[0], "s")) {
				player->move(args);
			}
			else if (same(args[0], "east") || same(args[0], "e")) {
				player->move(args);
			}
			else if (same(args[0], "west") || same(args[0], "w")) {
				player->move(args);
			}
			else if (same(args[0], "up") || same(args[0], "u")) {
				player->move(args);
			}
			else if (same(args[0], "down") || same(args[0], "d")) {
				player->move(args);
			}
			else if (same(args[0], "status") || same(args[0], "st")) {

			}
			else if (same(args[0], "inventory") || same(args[0], "i")) {

			}
		}
		case 2:
		{
			if (same(args[0], "look") || same(args[0], "l")) {
				ret = player->look(args);
			}
			else if (same(args[0], "use")) {

			}
			else if (same(args[0], "attack") || same(args[0], "at")) {

			}
			else if (same(args[0], "drop") || same(args[0], "dp")) {

			}
			else if (same(args[0], "take") || same(args[0], "tk")) {

			}
			else if (same(args[0], "open") || same(args[0], "op")) {

			}
		}
		case 4:
		{
			if (same(args[0], "attack") || same(args[0], "at")) {

			}
			if (same(args[0], "use")) {

			}
			if (same(args[0], "put") || same(args[0], "pt")) {

			}
		}
	}

	return ret;
}