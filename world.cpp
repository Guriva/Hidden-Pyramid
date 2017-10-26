#include <iostream>
#include "world.h"
#include "room.h"
#include "exit.h"
#include "creature.h"
#include "player.h"
#include "item.h"
#include "requirements.h"
#include "morse.h"
#include "globals.h"

World::World() {

	/*** Rooms ***/
	Room* home = new Room("Bedroom","This is your room. It looks very tidy and decorated with some old gadgets");
	Room* outside = new Room("Outside", "You are outside. You can see the big pyramid in front of you.");
	entities.push_back(home);
	entities.push_back(outside);


	/*** Containers ***/
	Item* backpack = new Item("Backpack", "A traditional backpack, you should know its purpose...", home, nullptr, nullptr, CONTAINER);
	Item* drawer = new Item("Drawer", "A drawer to store items",home,nullptr,nullptr,CONTAINER,false);
	Item* shelf = new Item("Shelf", "You can see some books here, examine it closely to see it's content",home,nullptr,nullptr,CONTAINER,false);
	entities.push_back(backpack);
	entities.push_back(drawer);
	entities.push_back(shelf);

	/*** Usables ***/
	Item* lantern = new Item("Lantern", "A lantern on the desk. It has a limited duration, be careful when to use it.",home,nullptr,nullptr,USABLE);
	Item* bandaje = new Item("Bandaje", "A short bandaje which you can use to heal yourself..., or use it as a pirate patch.",drawer,nullptr,nullptr,USABLE);
	Item* book = new Item("Book", "In the title it says \"Morse Code\". You can see some letters here: C-·-·, E·, L·-··, P·--·, R·-·, S···, T-, U··-, Z--··",shelf,nullptr,nullptr,USABLE);
	entities.push_back(lantern);
	entities.push_back(bandaje);
	entities.push_back(book);

	/*** Weapons ***/
	Item* knife = new Item("Knife", "A small knife, mostly used to kill enem... ehem, to shave the beard.", drawer, nullptr, nullptr, WEAPON);
	entities.push_back(knife);

	/*** Puzzles ***/
	Requirements* req1 = new Requirements("Some kind of puzzle","You are not ready to go to the pyramid yet, you must take all your equipment, at least a backpack and a lantern",REQUIREMENTS);
	req1->addRequirement(backpack);
	req1->addRequirement(lantern);
	entities.push_back(req1);
	Morse* morse1 = new Morse("A strange code","It says: ·--·|··-|--··|--··|·-··|·",MORSE,"puzzle");
	drawer->setPuzzle(morse1);

	/*** Exits ***/
	exitData eDataEx1;
	eDataEx1.key = nullptr;
	eDataEx1.puzzle = req1;
	Exit* exit1 = new Exit("west", "west", "Exit of your room on the west", "This path leads to your house, but you don't wanna go home right now",home,outside,eDataEx1);
	entities.push_back(exit1);
	/*** Enemies ***/
	
	//Room* room2 = new Room("Inside", "You are inside the pyramid. The walls are decorated with strange symbols.");
	/*Exit* exit1 = new Exit("east", "west", "Small structure of stones that leads inside the pyramid to the east",
		"Small structure of stones that leads outside of the pyramid to the west",room1,room2,BOTH);*/

	/*** Player ***/
	player = new Player("Player","",home);
	entities.push_back(player);
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
	if (player->getState() == WAITING) {
		switch (args.size()) {
			case 1:
			{
				if (same(args[0], "look") || same(args[0], "l")) {
					ret = player->look(args);
				}
				else if (same(args[0], "north") || same(args[0], "n")) {
					ret = player->move(args);
				}
				else if (same(args[0], "south") || same(args[0], "s")) {
					ret = player->move(args);
				}
				else if (same(args[0], "east") || same(args[0], "e")) {
					ret = player->move(args);
				}
				else if (same(args[0], "west") || same(args[0], "w")) {
					ret = player->move(args);
				}
				else if (same(args[0], "up") || same(args[0], "u")) {
					ret = player->move(args);
				}
				else if (same(args[0], "down") || same(args[0], "d")) {
					ret = player->move(args);
				}
				else if (same(args[0], "status") || same(args[0], "st")) {
					player->status();
				}
				else if (same(args[0], "inventory") || same(args[0], "i")) {
					player->inventory();
				}
				else
					ret = false;
				break;
			}
			case 2:
			{
				if (same(args[0], "look") || same(args[0], "l")) {
					ret = player->look(args);
				}
				else if (same(args[0], "examine") || same(args[0], "ex")) {
					ret = player->examine(args);
				}
				else if (same(args[0], "go")) {
					ret = player->move(args);
				}
				else if (same(args[0], "use")) {
					ret = player->use(args);
				}
				else if (same(args[0], "attack") || same(args[0], "at")) {
					ret = player->attack(args);
				}
				else if (same(args[0], "drop") || same(args[0], "dp")) {
					ret = player->drop(args);
				}
				else if (same(args[0], "take") || same(args[0], "tk")) {
					ret = player->take(args);
				}
				else if (same(args[0], "open") || same(args[0], "op")) {
					ret = player->examine(args);
				}
				else
					ret = false;
				break;
			}
			case 4:
			{
				if (same(args[0], "attack") || same(args[0], "at")) {
					ret = player->attack(args);
				}
				else if (same(args[0], "put") || same(args[0], "pt")) {
					ret = player->put(args);
				}
				else if (same(args[0], "take") || same(args[0], "tk")) {
					player->take(args);
				}
				else if (same(args[0], "unlock") || same(args[0], "ulk")) {
					ret = player->unlock(args);
				}
				else if (same(args[0], "solve") || same(args[0], "sl")) {
					ret = player->solve(args);
				}
				else
					ret = false;
				break;
			}
		}
	}

	if (player->getState() == SOLVING) {

	}

	return ret;
}