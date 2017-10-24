#include "player.h"
#include "room.h"

Player::Player(const char* name, const char* description, Room* room) :
	Creature(name,description,room){

	type = PLAYER;
	healthPoints = 100;
}
Player::~Player() {

}
void Player::look() const {

}