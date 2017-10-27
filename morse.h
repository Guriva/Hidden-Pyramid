#ifndef __Morse__
#define __Morse__

#include "puzzle.h"

class Morse : public Puzzle {

public:
	Morse(const char* name, const char* description, PType puzzleType, string answerCode);
	~Morse();
	void look() const;
	bool checkAnswer(const vector<string>& args);
	void unlockRules();

private:
	string answerCode;
};

#endif //__Morse__