#pragma once
#include"Const.h"
struct Val {
	double v;
	char t;
	Val() { v = 0; t = '0'; }
	Val(int V) { v = V; t = '0'; }
	Val(double V) { v = V; t = '0'; }
	Val(char c);
	bool operator <(const Val& _)const { return v < _.v; }
	bool operator <(const double& _)const { return v < _; }
	bool operator <(const int& _)const { return v < _; }
	bool operator <=(const Val& _)const { return v <= _.v; }
	bool operator <=(const double& _)const { return v <= _; }
	bool operator <=(const int& _)const { return v <= _; }

	bool operator >(const Val& _)const { return v > _.v; }
	bool operator >(const double& _)const { return v > _; }
	bool operator >(const int& _)const { return v > _; }
	bool operator >=(const Val& _)const { return v >= _.v; }
	bool operator >=(const double& _)const { return v >= _; }
	bool operator >=(const int& _)const { return v >= _; }

	bool operator ==(const Val& _)const { return iszero(v - _.v); }
	bool operator ==(const double& _)const { return iszero(v - _); }
	bool operator ==(const int& _)const { return iszero(v - _); }

	bool operator !=(const Val& _)const { return !(*this == _); }
	bool operator !=(const double& _)const { return !(*this == _); }
	bool operator !=(const int& _)const { return !(*this == _); }

	Val operator -()const { return Val(-v); }
	Val operator +(const Val& _)const { return Val(v + _.v); }
	Val operator -(const Val& _)const { return Val(v - _.v); }
	Val operator *(const Val& _)const { return Val(v * _.v); }
	Val operator ^(const Val& _)const { return Val(pow(v, _.v)); }
	Val operator ^(const int& _)const { return Val(pow(v, _)); }
	Val operator /(const Val& _)const {
		if (iszero(_.v))error("divided by 0");
		return Val(v / _.v);
	}
	Val operator /(const int& _)const {
		if (iszero(_))error("divided by 0");
		return Val(v / _);
	}
	Val operator /(const double& _)const {
		if (iszero(_))error("divided by 0");
		return Val(v / _);
	}
	Val operator %(const Val& _)const {
		if (iszero(_.v))error("mod by 0");
		return Val(beint(v) % beint(_.v));
	}//????
	Val operator %(const int& _)const {
		if (iszero(_))error("mod by 0");
		return Val(beint(v) % _);
	}
	Val& operator +=(const Val& _) { return *this = *this + _; }
	Val& operator -=(const Val& _) { return *this = *this - _; }
	Val& operator *=(const Val& _) { return *this = *this * _; }
	Val& operator /=(const Val& _) { return *this = *this / _; }
	Val& operator /=(const int& _) { return *this = *this / _; }
	Val& operator /=(const double& _) { return *this = *this / _; }
	Val& operator %=(const Val& _) { return *this = *this % _; }
	Val& operator %=(const int& _) { return *this = *this % _; }
	Val& operator ^=(const Val& _) { return *this = *this ^ _; }
	Val& operator ^=(const int& _) { return *this = *this ^ _; }
	Val& operator =(const char& _) { return *this = Val(_); }
	Val& operator =(const int& _) { return *this = Val(_); }
	void operator()(const char& c, const Val& _) {
		switch (c) {
		case '+':v += _.v; break;
		case '*':v *= _.v; break;
		}
		t = '0';
	}
	void operator()(const char& c, const Val& x, const Val& y) {
		switch (c) {
		case '/': {
			if (iszero(y.v))error("divided by 0");
			v = x.v / y.v;
			break;
		}
		case '^': {
			if (iszero(x.v) && iszero(y.v))error("0^0");
			if (x.v < 0 && !isint(y.v))error("-^irrational");
			v = pow(x.v, y.v);
			break;
		}
		}
		t = '0';
	}
	char* getstr()const {
		char* str = new char[20];
		if (t == '0') {
			if (isint(v)) sprintf_s(str, 20, "%d", beint(v));
			else sprintf_s(str, 20, "%lf", v);
		}
		else  sprintf_s(str, 20, "%c", t);
		return str;
	}
	int getlen()const {
		char* str = getstr();
		//output(str, 100, 400);
		int l = strlen(str);
		//output(l, 100, 420);
		free(str);
		return l;
	}
};