#pragma once
#include"³£ÓÃº¯Êý.h"
using namespace std;
const double esp=1e-7; 
bool equ(const double& x, const int& y) { return fabs(x - y) < esp; }
bool iszero(int x) { return !x; }
bool iszero(double x) { return fabs(x) < esp; }
bool isint(const double& x) { return iszero(x - floor(x)) || iszero(x - ceil(x)); }
void error(const string& s) {
	cerr << "!!:" << s << endl;
	exit(0);
}
void error(const string& s, char c) {
	cerr << "!!:" << s << c << endl;
	exit(0);
}
void error(const string& s, char c, char d) {
	cerr << "!!:" << s << c << d << endl;
	exit(0);
}
void output(const char* s, int left = 50, int top = 50) {
	settextcolor(WHITE);
	outtextxy(left, top, s);
	Sleep(600);
}
void output(int x, int left = 50, int top = 50) {
	settextcolor(WHITE);
	char s[20];
	sprintf_s(s, 20, "%d", x);
	outtextxy(left, top, s);
	Sleep(600);
}
void output(double x, int left = 50, int top = 50) {
	settextcolor(WHITE);
	char s[20];
	sprintf_s(s, 20, "%lf", x);
	outtextxy(left, top, s);
	Sleep(600);
}
double rand_double() {//[10,110]
	return (double)(rand() * rand() % 1000000000 + 100000000) / 10000000 * (rand() % 2 ? 1 : -1);
}