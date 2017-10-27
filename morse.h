#ifndef __Morse__
#define __Morse__

#include "puzzle.h"

class Morse : public Puzzle {

public:
	Morse(const char* name, const char* description, PType puzzleType, string answerCode);
	~Morse();
	void look() const;
	bool checkCode(string code);

private:
	string answerCode;
};

#endif //__Requirements__