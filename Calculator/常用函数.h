#pragma once
#include<cstdio>
#include<iostream>
#include<string>
#include<algorithm>
#include<map>
#include<set>
#include<vector>
#include<sstream>
#include<string.h>
#include<time.h>
#include<easyx.h>
using namespace std;
template<class T>bool tomax(T& x, const T& y) { return x < y ? x = y, 1 : 0; }
template<class T>bool tomin(T& x, const T& y) { return y < x ? x = y, 1 : 0; }
bool equ(const double& x, const int& y);
template<class T>int beint(const T& x) {
	if (equ(x, (int)x))return (int)x;
	if (equ(x, 1 + (int)x))return 1 + (int)x;
	return (int)x - 1;
}
bool iszero(int x);
bool iszero(double x);
bool isint(const double& x);
void error(const string& s);
void error(const string& s, char c);
void error(const string& s, char c, char d);
void output(const char* s, int left, int top);
void output(int x, int left, int top);
void output(double x, int left, int top);
double rand_double();