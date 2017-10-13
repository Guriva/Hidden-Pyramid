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

}