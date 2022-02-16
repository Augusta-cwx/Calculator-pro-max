#pragma once
#include"³£ÓÃº¯Êý.h"
struct Brackets {
	map<char, int>mp;
	Brackets() {
		mp['('] = mp[')'] = 0;
		mp['['] = mp[']'] = 1;
		mp['{'] = mp['}'] = 2;
	}
	int operator()(const char& c) { return mp[c]; }
	char operator[](const char& c) { return c + 1 + (c != '('); }
};