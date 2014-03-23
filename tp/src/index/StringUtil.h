#ifndef __STRING_UTIL_H__
#define __STRING_UTIL_H__

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

string normalize(string&);
string trim(const string&, const string&);
string reduce(const string& str, const string& fill = " ", const string& whitespace = " \t");
char *latin9_to_utf8(const char *const);

 #endif /* __STRING_UTIL_H__ */