#ifndef __BottlePuzzle__
#define __BottlePuzzle__

#include "puzzle.h"

class BottlePuzzle : public Puzzle {

public:
	BottlePuzzle(const char* name, const char* description, const PType& puzzleType, int numberBottles, const int& chances);
	~BottlePuzzle();
	void look() const override;
	bool checkAnswer(const vector<string>& args) override;
	void unlockRules() const override;

private:
	bool validBottle(const string& bottle) const;
	void reorderBottles();

private:
	int counter, chances;
	vector<string> orderBottles;
	vector<string> possibleBottles;
};

#endif //__BottlePuzzle__