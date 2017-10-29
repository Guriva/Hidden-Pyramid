#ifndef __Morse__
#define __Morse__

#include "puzzle.h"

class Morse : public Puzzle {

public:
	Morse(const char* name, const char* description, const PType& puzzleType, const string& answerCode);
	~Morse();
	void look() const override;
	bool checkAnswer(const vector<string>& args) override;
	void unlockRules() const override;

private:
	string answerCode;
};

#endif //__Morse__