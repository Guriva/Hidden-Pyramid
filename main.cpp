#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>
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

	while (world.playerAlive() || world.playerWon() == false) {
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
		
		if (args.size() > 0) {
			if (world.Update(args) == false)
				cout << "Sorry, what did you said?" << endl;

			concatenatedInput = "";
			args.clear();
			cout << endl << "> ";
		}
		else {
			if (world.entitiesUpdate())
				cout << "> " << concatenatedInput;
		}
	}

	if (world.playerAlive() == false) {
		cout << "You have died before exploring all the pyramid :(" << endl;
	}

	else if (world.playerWon()) {
		cout << "You come back through all the rooms with the treasure in hand. Now you are rich and you can do whatever you want!" << endl;
	}

	cout << "Thanks for playing!" << endl;
	cout << "The window will close automatically after 10 seconds." << endl;
	Sleep(10000);
	return 0;
}