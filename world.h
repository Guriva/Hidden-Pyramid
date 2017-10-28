#ifndef __World__
#define __World__

#include <vector>
#include <string>
#include <ctime>

using namespace std;

class Entity;
class Player;

class World {

public:
	World();
	~World();
	bool Update(vector<string>& args);
	bool entitiesUpdate();
	bool getInput(vector<string>& args);
	bool playerAlive();
	bool playerWon();
private:
	vector<Entity*> entities;
	Player* player = nullptr;
	clock_t prevTime;
};

#endif //__World__