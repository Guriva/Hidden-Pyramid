#ifndef __Player__
#define __Player__

#include "creature.h"

class Room;
class Puzzle;

enum PState {
	WAITING,
	SOLVING
};

class Player : public Creature {

public:
	Player(const char* name, const char* description, Room* room);
	~Player();
	void Update();
	bool look(const vector<string>& args) const override;
	bool move(const vector<string>& args);
	bool use(const vector<string>& args);
	bool attack(const vector<string>& args);
	bool drop(const vector<string>& args);
	bool take(const vector<string>& args);
	bool put(const vector<string>& args);
	bool unlock(const vector<string>& args);
	void status() const;
	void inventory() const;
	bool examine(const vector<string>& args) const;
	bool moveItem(const vector<string>& args);
	PState getState() const;
	void setState(const PState state);
	bool checkPuzzle(Puzzle* puzzle);

private:
	unsigned int maxInventory;
	PState statePlayer;
};

#endif //__Player__