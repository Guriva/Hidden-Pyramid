#include "morse.h"

Morse::Morse(const char* name, const char* description, PType puzzleType, string answerCode) :
Puzzle(name,description,puzzleType) {

}

Morse::~Morse() {

}

void Morse::look() const {

}

bool Morse::checkCode(string code) {
	return (code == answerCode);
}