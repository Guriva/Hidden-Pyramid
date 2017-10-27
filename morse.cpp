#include <iostream>
#include "morse.h"

Morse::Morse(const char* name, const char* description, PType puzzleType, string answerCode) :
Puzzle(name,description,puzzleType) {

}

Morse::~Morse() {

}

void Morse::look() const {
	cout << "It is locked by a puzzle: " << name << endl;
	cout << description << endl;
}

bool Morse::checkCode(string code) {
	return (code == answerCode);
}