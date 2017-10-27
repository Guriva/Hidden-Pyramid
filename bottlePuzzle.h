#ifndef __BottlePuzzle__
#define __BottlePuzzle__

#include "puzzle.h"

class BottlePuzzle : public Puzzle {

public:
	BottlePuzzle(const char* name, const char* description, PType puzzleType, int numberBottles, int chances);
	~BottlePuzzle();
	void look() const;
	bool checkAnswer(const vector<string>& args);
	void unlockRules();
	bool validBottle(const string& bottle);
	void reorderBottles();

private:
	int counter, chances;
	vector<string> orderBottles;
	vector<string> possibleBottles;
};

#endif //__BottlePuzzle__