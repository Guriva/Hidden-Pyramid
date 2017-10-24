#ifndef __World__
#define __World__

#include <vector>
#include <string>

using namespace std;

class Entity;
class Player;

class World {

public:
	World();
	~World();
	bool Update(vector<string>& args);
	void entitiesUpdate();
	bool getInput(const vector<string>& args);
private:
	vector<Entity*> entities;
	Player* player;
};

#endif //__World__