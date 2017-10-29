#ifndef __Player__
#define __Player__

#include "creature.h"

class Room;
class Puzzle;
class Item;
class Exit;

enum PState {
	WAITING,
	SOLVING,
	EVADING,
	DEAD,
	WIN
};

class Player : public Creature {

public:
	Player(const char* name, const char* description, Room* room);
	~Player();
	bool Update(const float& frameTime) override;
	bool look(const vector<string>& args) const override;
	bool move(const vector<string>& args);
	bool use(const vector<string>& args);
	bool attack(const vector<string>& args) override;
	bool avoid(const vector<string>& args);
	bool drop(const vector<string>& args) const;
	bool take(const vector<string>& args);
	bool put(const vector<string>& args) const;
	bool unlock(const vector<string>& args);
	bool unlockExitKey(Exit* exit) const;
	bool unlockItemKey(Item* item) const;
	void status() const override;
	bool solve(const vector<string>& args);
	void inventory() const;
	bool examine(const vector<string>& args) const;
	bool moveItem(const vector<string>& args) const;
	bool checkPuzzle(const Puzzle* puzzle) const;

private:
	bool itContains(const Entity* entity) const;
	Entity* findInInventory(const string& args) const;

public:
	bool avoiding;
	unsigned int maxInventory;
	PState statePlayer;
	Entity* entityUnlocking;
	float cdAvoid, cdAvoidLeft, cdAvoidTime, cdAvoidTimeLeft;
};

#endif //__Player__