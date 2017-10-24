#include "globals.h"
#include <iostream>

bool same(const string& a, const string& b) {
	return _stricmp(a.c_str(),b.c_str()) == 0;
}

bool same(const char* a, const string& b) {
	return _stricmp(a, b.c_str()) == 0;
}

bool same(const string& a, const char* b) {
	return _stricmp(a.c_str(), b) == 0;
}

void tokenize(const string& input, vector<string>& args) {
	string aux = "";
	for (int i = 0; i < input.length() + 1; ++i) {
		if (input[i] != ' ' && input[i] != '\0') {
			aux += input[i];
		}
		else {
			args.push_back(aux);
			aux = "";
		}
	}
}