#include <iostream>
#include <string>
#include <conio.h>
#include "world.h"
#include "globals.h"
using namespace std;


int main() {
	World world;
	char input;
	string concatenatedInput;
	vector<string> args;
	args.reserve(10);

	cout << "You are an archaeologist" << endl;
	cout << "You wake up in your room when someone knocked on the door." << endl;
	cout << "You open the door and you see the delivery man giving you a newspaper." << endl;
	cout << "As you read the newspaper, it appears that the earthquake which happened" << endl;
	cout << "yesterday night uncovered an ancient pyramid, but nobody has opened yet" << endl;
	cout << "the entrance, which remains closed." << endl;
	cout << "You decide to travel to the site and investigate what lies there..." << endl;
	cout << endl;

	args.push_back("look");

	while (1) {
		if (_kbhit() != 0) {
			input = _getch();
			if (input == '\b') {
				if (concatenatedInput.length() > 0) {
					concatenatedInput.pop_back();
					cout << '\b' << " " << '\b';
				}
			}
			else if (input != '\r') {
				concatenatedInput += input;
				cout << input;
			}
			
			else {
				cout << endl;
				tokenize(concatenatedInput,args);
			}
		}

		if (args.size() > 0 && same(args[0],"quit")) {
			break;
		}

		if (world.Update(args) == false)
			cout << "Sorry, what did you said?" << endl;
		
		if (args.size() > 0) {
			concatenatedInput = "";
			args.clear();
			cout << endl << "> ";
		}
	}
}