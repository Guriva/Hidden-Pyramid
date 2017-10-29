#include <iostream>
#include "morse.h"
#include "globals.h"

Morse::Morse(const char* name, const char* description, const PType& puzzleType, const string& answerCode) :
Puzzle(name,description,puzzleType), answerCode(answerCode) {
	
}

Morse::~Morse() {

}

void Morse::look() const {
	cout << "It is locked by a puzzle: " << name << endl;
	cout << description << endl;
}

bool Morse::checkAnswer(const vector<string>& args) {
	if (args.size() == 0) {
		cout << "You have to put a code." << endl;
		return false;
	}
	string answer = "";
	for (unsigned int i = 0; i < args.size() - 1; ++i) {
		answer += args[i];
		answer += " ";
	}
	answer += args[args.size() - 1];

	if (same(answerCode, answer)) {
		cout << "You put the correct answer!" << endl;
		return true;
	}
	cout << "That's not a valid answer." << endl;
	return false;

}

void Morse::unlockRules() const {
	cout << "This code must mean something... Say the answer if you think you know it:" << endl;
}