#pragma once
#include"���ú���.h"
struct Bin {
	int operator[](const int& x)const {
		if (!x)error("bin");
		for (int i = 0;; i++)if (x >> i & 1)return i;
	}
	int operator()(const int& x)const { return x ^ (x & -x); }
};