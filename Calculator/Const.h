#pragma once
#include"³£ÓÃº¯Êý.h"
struct Const {
	map<char, double>mp;
	Const() {
		mp['E'] = 2.7182818284;
		mp['P'] = 3.1415926535;
		mp['x'] = 1.0757150757;
		mp['y'] = 1.7978507978;
		mp['z'] = 2.6971126971;
		mp['a'] = 1.9567129567;
		mp['b'] = 2.1749391749;
		mp['c'] = 1.1470551470;
	}
	double operator[](char c) { return mp[c]; }
};