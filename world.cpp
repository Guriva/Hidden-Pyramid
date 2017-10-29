#include <iostream>
#include <ctime>
#include "world.h"
#include "room.h"
#include "exit.h"
#include "creature.h"
#include "player.h"
#include "item.h"
#include "requirements.h"
#include "morse.h"
#include "bottlePuzzle.h"
#include "snake.h"
#include "scorpion.h"
#include "mummy.h"
#include "globals.h"

World::World() {

	prevTime = clock();

	/*** Rooms ***/
	Room* home = new Room("Bedroom","This is your room. It looks very tidy and decorated with some old gadgets");
	Room* entrance = new Room("Entrance", "You are outside. You can see the big pyramid in front of you. It seems there's an entrance over there.");
	Room* northPyramid = new Room("North Pyramid", "You are at the north side of the pyramid. Due to the earthquake you cannot pass through the pile of stones at east.");
	Room* southPyramid = new Room("South Pyramid", "You are at the south side of the pyramid. Due to the earthquake you cannot pass through the pile of stones at east.");
	Room* labyrinth1 = new Room("Room with Symbols", "You feel a strange presence here... It seems all the room is decorated with strange symbols.");
	Room* labyrinth2 = new Room("Room with Symbols", "You feel a strange presence here... It seems all the room is decorated with strange symbols, but it's like something has changed.");
	Room* labyrinth3 = new Room("Room with Symbols", "You feel a strange presence here... It seems all the room is decorated with strange symbols, but it's like something has changed.");
	Room* antechamber = new Room("Antechamber","This seems to be the antechamber to the pharaon tomb room, as far as you can deduce with your knowledge of pyramids");
	Room* pharaonroom = new Room("Pharaon Room", "You can see the pharaon tomb just right in front of you");
	entities.push_back(home);
	entities.push_back(entrance);
	entities.push_back(northPyramid);
	entities.push_back(southPyramid);
	entities.push_back(labyrinth1);
	entities.push_back(labyrinth2);
	entities.push_back(labyrinth3);
	entities.push_back(antechamber);
	entities.push_back(pharaonroom);

	/*** Containers ***/
	Item* backpack = new Item("Backpack", "A traditional backpack, you should know its purpose.", home, nullptr, nullptr, CONTAINER);
	Item* drawer = new Item("Drawer", "A drawer to store items.",home,nullptr,nullptr,CONTAINER,false);
	Item* shelf = new Item("Shelf", "You can see some books here, examine it closely to see it's content.",home,nullptr,nullptr,CONTAINER,false);
	Item* chest = new Item("Chest","A chest made of stones.",antechamber,nullptr,nullptr,CONTAINER,false);
	Item* treasureChest = new Item("Chest","A chest made of shining stones, maybe there's something valuable inside.",pharaonroom,nullptr,nullptr,CONTAINER,false);

	entities.push_back(backpack);
	entities.push_back(drawer);
	entities.push_back(shelf);
	entities.push_back(chest);
	entities.push_back(treasureChest);

	/*** Movables ***/
	Item* rock1 = new Item("Rock","A small rock. It seems it can be moved to a side",northPyramid,nullptr,nullptr,MOVABLE,false);
	Item* rock2 = new Item("Rock", "A small rock. It seems it can be moved to a side", southPyramid, nullptr, nullptr, MOVABLE, false);

	entities.push_back(rock1);
	entities.push_back(rock2);

	/*** Usables ***/
	Item* bandaje = new Item("Bandaje", "A short bandaje which you can use to heal yourself..., or use it as a pirate patch.", drawer, nullptr, nullptr, USABLE);
	Item* bandaje2 = new Item("Bandaje", "A short bandaje which you can use to heal yourself..., or use it as a pirate patch.", rock1, nullptr, nullptr, USABLE);
	Item* bandaje3 = new Item("Bandaje", "A short bandaje which you can use to heal yourself..., or use it as a pirate patch.", chest, nullptr, nullptr, USABLE);
	Item* bandaje4 = new Item("Bandaje", "A short bandaje which you can use to heal yourself..., or use it as a pirate patch.", chest, nullptr, nullptr, USABLE);
	Item* bandaje5 = new Item("Bandaje", "A short bandaje which you can use to heal yourself..., or use it as a pirate patch.", chest, nullptr, nullptr, USABLE);
	Item* book = new Item("Book", "In the title it says \"Morse Code\". You can see some letters here: C-.-., E., L.-.., P.--., R.-., S..., T-, U..-, Z--..",shelf,nullptr,nullptr,USABLE);
	Item* key1 = new Item("Key", "An old and rusty key", rock1, nullptr, nullptr, USABLE);
	Item* treasure = new Item("Treasure", "It's a treasure! It contains a lot of gems and money. You are rich!",treasureChest,nullptr,nullptr,USABLE);
	entities.push_back(bandaje);
	entities.push_back(bandaje2);
	entities.push_back(bandaje3);
	entities.push_back(bandaje4);
	entities.push_back(bandaje5);
	entities.push_back(book);
	entities.push_back(key1);
	entities.push_back(treasure);

	/*** Weapons ***/
	Item* lantern = new Item("Lantern", "A lantern on the desk. It could be useful for something,... or not.", home, nullptr, nullptr, WEAPON);
	Item* knife = new Item("Knife", "A small knife, mostly used to kill enem... ehem, to shave your beard.", drawer, nullptr, nullptr, WEAPON);
	Item* stick = new Item("Stick", "A stick..., maybe you can use it for self defense..., just maybe",entrance,nullptr,nullptr,WEAPON);
	entities.push_back(lantern);
	entities.push_back(knife);
	entities.push_back(stick);

	/*** Puzzles ***/
	Requirements* req1 = new Requirements("","You are not ready to go to the pyramid yet, you must take all your equipment: ",REQUIREMENTS);
	req1->addRequirement(backpack);
	req1->addRequirement(lantern);
	Morse* morse1 = new Morse("A strange code","It says: .--.|..-|--..|--..|.-..|.",MORSE,"puzzle");
	Morse* morse2 = new Morse("A strange code", "It says: ...|.|-.-.|.-.|.|-", MORSE, "secret");
	BottlePuzzle* bottleP1 = new BottlePuzzle("Some kind of platforms","There are some platforms and some bottles, they must serve for something.",BOTTLES,4,5);
	drawer->setPuzzle(morse1);
	chest->setPuzzle(morse2);

	entities.push_back(req1);
	entities.push_back(morse1);
	entities.push_back(morse2);
	entities.push_back(bottleP1);

	/*** Exits ***/
	exitData eData;
	eData.key = nullptr;
	eData.puzzle = req1;
	eData.onlyPassOnce = true;
	Exit* exit1 = new Exit("west", "west", "Exit of your room on the west", "This path to the west leads to your house but you don't wanna go home right now",home,entrance, eData);

	eData.puzzle = nullptr;
	eData.onlyPassOnce = false;
	Exit* exit2 = new Exit("north","west","Passage to the north side of the pyramid", "Passage to the west side of the pyramid",entrance,northPyramid, eData);
	Exit* exit3 = new Exit("south", "west", "Passage to the south side of the pyramid", "Passage to the west side of the pyramid", entrance, southPyramid, eData);
	
	eData.key = key1;
	Exit* exit4 = new Exit("east", "west", "Entrance to the east that leads inside the pyramid", "Above the door there's a human face engraved on the wall. His two eyes are very big.", entrance, labyrinth1, eData);

	eData.key = nullptr;
	eData.ignoreDestination = true;
	Exit* exit5 = new Exit("east","","Above the door to the east there's engraved: |||","",labyrinth1,labyrinth1,eData);
	Exit* exit6 = new Exit("south", "", "Above the door to the south there's engraved: ||", "", labyrinth1, labyrinth1, eData);
	Exit* exit7 = new Exit("north", "", "Above the door to the north there's engraved: ||||", "", labyrinth1, labyrinth2, eData);

	Exit* exit8 = new Exit("north", "", "Above the door to the north there's engraved: ||||", "", labyrinth2, labyrinth1, eData);
	Exit* exit9 = new Exit("east", "", "Above the door to the east there's engraved: |||", "", labyrinth2, labyrinth1, eData);
	Exit* exit10 = new Exit("south", "", "Above the door to the south there's engraved: ||", "", labyrinth2, labyrinth3, eData);
	Exit* exit11 = new Exit("west", "", "Above the door the west there's a human face engraved on the wall. His two eyes are very big, and the one in the left is shining.", "", labyrinth2, entrance, eData);

	Exit* exit12 = new Exit("north", "", "Above the door to the north there's engraved: ||||", "", labyrinth3, labyrinth1, eData);
	Exit* exit13 = new Exit("south", "", "Above the door to the south there's engraved: ||", "", labyrinth3, labyrinth1, eData);
	Exit* exit14 = new Exit("east", "", "Above the door to the east there's engraved: |||", "", labyrinth3, antechamber, eData);
	Exit* exit15 = new Exit("west", "", "Above the door to the west there's a human face engraved on the wall. His two eyes are very big, and the two eyes are shining.", "", labyrinth3, entrance, eData);

	Exit* exit16 = new Exit("west","","This passage to the west may lead to the first room of the pyramid, think before going back.","",antechamber,labyrinth1,eData);

	eData.puzzle = bottleP1;
	eData.ignoreDestination = false;
	Exit* exit17 = new Exit("east","west","This passage to the east leads to the pharaon tomb chamber","This passage leads to the antechamber room",antechamber,pharaonroom,eData);
	entities.push_back(exit1);
	entities.push_back(exit2);
	entities.push_back(exit3);
	entities.push_back(exit4);
	entities.push_back(exit5);
	entities.push_back(exit6);
	entities.push_back(exit7);
	entities.push_back(exit8);
	entities.push_back(exit9);
	entities.push_back(exit10);
	entities.push_back(exit11);
	entities.push_back(exit12);
	entities.push_back(exit13);
	entities.push_back(exit14);
	entities.push_back(exit15);
	entities.push_back(exit16);
	entities.push_back(exit17);

	/*** Enemies ***/
	Snake* snake = new Snake("Snake","It's a small snake, with green and yellow skin. Seems poisonous.",rock1);
	Snake* snake2 = new Snake("Snake", "It's a small snake, with green and yellow skin. Seems poisonous.", labyrinth1, true);
	Scorpion* scorpion = new Scorpion("Scorpion", "It's a scorpion, care with his tail, it could hurt you", rock2);
	Scorpion* scorpion2 = new Scorpion("Scorpion", "It's a scorpion, care with his tail, it could hurt you", antechamber);
	Mummy* mummy = new Mummy("Mummy","It's a living mummy! Well, a living dead mummmy... Never mind, just take care of it!",pharaonroom);
	entities.push_back(snake);
	entities.push_back(snake2);
	entities.push_back(scorpion);
	entities.push_back(scorpion2);
	entities.push_back(mummy);

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

bool World::entitiesUpdate() {
	clock_t time = clock();

	bool ret = false;

	for (unsigned int i = 0; i < entities.size(); ++i) {
		ret |= entities[i]->Update(((float)(time - prevTime)) / CLOCKS_PER_SEC);
	}

	prevTime = time;
	return ret;
}

bool World::getInput(vector<string>& args) {
	bool ret = true;
	if (player->statePlayer == WAITING) {
		switch (args.size()) {
			case 1:
			{
				if (same(args[0], "look") || same(args[0], "l")) {
					player->look(args);
				}
				else if (same(args[0], "north") || same(args[0], "n")) {
					if (same(args[0], "n")) args[0] = "north";
					player->move(args);
				}
				else if (same(args[0], "south") || same(args[0], "s")) {
					if (same(args[0], "s")) args[0] = "south";
					player->move(args);
				}
				else if (same(args[0], "east") || same(args[0], "e")) {
					if (same(args[0], "e")) args[0] = "east";
					player->move(args);
				}
				else if (same(args[0], "west") || same(args[0], "w")) {
					if (same(args[0], "w")) args[0] = "west";
					player->move(args);
				}
				else if (same(args[0], "up") || same(args[0], "u")) {
					if (same(args[0], "u")) args[0] = "up";
					player->move(args);
				}
				else if (same(args[0], "down") || same(args[0], "d")) {
					if (same(args[0], "d")) args[0] = "down";
					player->move(args);
				}
				else if (same(args[0], "status") || same(args[0], "st")) {
					player->status();
				}
				else if (same(args[0], "inventory") || same(args[0], "i")) {
					player->inventory();
				}
				else if (same(args[0],"avoid")) {
					player->avoid(args);
				}
				else
					ret = false;
				break;
			}
			case 2:
			{
				if (same(args[0], "look") || same(args[0], "l")) {
					player->look(args);
				}
				else if (same(args[0], "examine") || same(args[0], "ex")) {
					player->examine(args);
				}
				else if (same(args[0], "go")) {
					player->move(args);
				}
				else if (same(args[0], "use")) {
					player->use(args);
				}
				else if (same(args[0], "drop") || same(args[0], "dp")) {
					player->drop(args);
				}
				else if (same(args[0], "take") || same(args[0], "tk")) {
					player->take(args);
				}
				else if (same(args[0], "move") || same(args[0], "mv")) {
					player->moveItem(args);
				}
				else if (same(args[0], "unlock") || same(args[0], "ulk")) {
					player->unlock(args);
				}
				else
					ret = false;
				break;
			}
			case 4:
			{
				if (same(args[0], "attack")) {
					player->attack(args);
				}
				else if (same(args[0], "put") || same(args[0], "pt")) {
					player->put(args);
				}
				else if (same(args[0], "take") || same(args[0], "tk")) {
					player->take(args);
				}
				else
					ret = false;
				break;
			}
		}
	}

	else if (player->statePlayer == SOLVING) {
		player->solve(args);
	}

	return ret;
}

bool World::playerAlive() const {
	return (player->statePlayer != DEAD);
}

bool World::playerWon() const {
	return (player->statePlayer == WIN);
}