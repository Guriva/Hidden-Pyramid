#include <iostream>
#include <algorithm>
#include "bottlePuzzle.h"
#include "globals.h"

BottlePuzzle::BottlePuzzle(const char* name, const char* description, const PType& puzzleType, int numberBottles, const int& chances) :
	Puzzle(name, description, puzzleType), orderBottles(orderBottles), chances(chances) {

	if (numberBottles > 6)
		numberBottles = 6;

	orderBottles.reserve(numberBottles+1);
	possibleBottles.reserve(7);
	possibleBottles.push_back("red");
	possibleBottles.push_back("blue");
	possibleBottles.push_back("yellow");
	possibleBottles.push_back("green");
	possibleBottles.push_back("purple");
	possibleBottles.push_back("brown");
	for (int i = 0; i < numberBottles; ++i) {
		orderBottles.push_back(possibleBottles[i]);
	}
	if (numberBottles > 1) {
		std::rotate(orderBottles.begin(), orderBottles.begin() + (rand() % (numberBottles - 1)), orderBottles.end());
		std::rotate(orderBottles.begin(), orderBottles.begin() + (rand() % (numberBottles - 1)), orderBottles.end());
		std::rotate(orderBottles.begin(), orderBottles.begin() + (rand() % (numberBottles - 1)), orderBottles.end());
	}
	counter = 0;
}

BottlePuzzle::~BottlePuzzle() {

}

void BottlePuzzle::look() const {
	cout << "It is locked by a puzzle: " << name << endl;
	cout << description << endl;
}

bool BottlePuzzle::checkAnswer(const vector<string>& args) {
	if (args.size() != orderBottles.size() || orderBottles.size() == 0) {
		cout << "It doesn't happened anything";
		return false;
	}

	int correctCounter = 0;

	for (unsigned int i = 0; i < args.size(); ++i) {
		if (validBottle(args[i]) == false) {
			cout << "You didn't put a correct input" << endl;
			return false;
		}
		if (same(args[i], orderBottles[i]) == true)
			++correctCounter;
	}

	if (correctCounter == orderBottles.size()) {
		cout << "You put the bottles in the correct order!" << endl;
		return true;
	}

	cout << "Nothing happened, but you hear something..." << endl;
	for (int i = 0; i < correctCounter; ++i)
		cout << "'tick' " << endl;
	++counter;
	if (counter == chances) {
		counter = 0;
		reorderBottles();
		cout << "You can hear a mechanism moving down the platforms, like something is changing" << endl;
	}
	return false;
}

void BottlePuzzle::unlockRules() const {
	if (orderBottles.size() == 0) {
		cout << "It doesn't have any bottles here and cannot be solved." << endl;
		return;
	}
	cout << "Here you can see " << orderBottles.size() << " bottles. A " << possibleBottles[0] << " bottle ";
	for (unsigned int i = 1; i < orderBottles.size(); ++i)
		cout << " a " << possibleBottles[i] << " bottle";
	cout << endl;
	cout << "Maybe if you put them into the platforms in some order something will happen..." << endl;
}

bool BottlePuzzle::validBottle(const string& bottle) const {
	for (unsigned int i = 0; i < orderBottles.size(); ++i) {
		if (same(orderBottles[i], bottle))
			return true;
	}
	return false;
}

void BottlePuzzle::reorderBottles() {
	//It could be changed to random position instead, so it's less predictable.
	if (orderBottles.size() > 2)
		std::rotate(orderBottles.begin(),orderBottles.begin()+1,orderBottles.end());
}