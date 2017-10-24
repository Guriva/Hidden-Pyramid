#ifndef __Globals__
#define __Globals__

#include <string>
#include <vector>

using namespace std;

bool same(const string& a, const string& b);
bool same(const char* a, const string& b);
bool same(const string& a, const char* b);
void tokenize(const string& input, vector<string>& args);

#endif //__Globals__