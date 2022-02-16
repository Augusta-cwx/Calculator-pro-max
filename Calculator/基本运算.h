#pragma once
#include"常用函数.h"
#include"Val.h"
#include"Const.h"
#include"Bin.h"
#include"Prime.h"
#include"Brackets.h"
struct Expression {
	//优先级：分式，加，乘，指数，数值
	char Type;
	vector<Expression*>a;//Check 地址与值
	Val v;
	int size()const;
	bool isnum()const;
	bool empty();
	void Adjust();
	bool Negative(const Expression& x);
	bool Negative(Expression* x);
	bool Check(const vector<double>& V, vector<int>& X, int cur, double v, const double& res, int& mx, const vector<int>& p);
	bool Check(double v1, double v2);
	void Factorization(const vector<Expression>& t, const vector<double>& V, const vector<int>& p);
	bool Check(const vector<double>& V1, const vector<double>& V2, vector<int>& X, vector<int>& Y, int cur, double v1, double v2, const double& res, int& mx);
	void Factorization(const vector<Expression>& t1, const vector<double>& V1, const vector<Expression>& t2, const vector<double>& V2);
	bool Check(const vector<int>& X, const vector<int>& Y);
	bool Check(const vector<double>& V, vector<int>& X, vector<int>& Y, int cur, double v1, double v2, const double& res, int& mx);
	void Factorization(const vector<Expression>& t, const vector<double>& V);
	Expression(const vector<Expression>& t, const vector<int>& V);
	void Insert(vector<pair<Expression, int> >& s, const Expression& x);
	void Split(vector<pair<Expression, int> >& s);
	void Enum(const vector<pair<Expression, int> >& s, vector<int>& e, vector<Expression>& t, int cur);
	void Unique(vector<pair<Expression, int> >& s, vector<Expression>& t, vector<double>& V);
	void Unique(vector<pair<Expression, int> >& s, vector<Expression>& t1, vector<double>& V1, vector<Expression>& t2, vector<double>& V2);
	void Factorization(int n);
	Expression Factorization(const Expression& t);
	void Factorization(Expression& p, Expression& q);
	bool Radical();
	int count();
	bool Rationalization(Expression& p);
	void Init();
	int gcd_(int n, int m);
	bool gcd(Val& x, Val& y);
	bool Abbre_free();
	void Abbre_after();
	void Abbreviation();
	int Extract();
	bool operator |=(const Expression& _);
	bool operator &=(const Expression& _);
	void Insert(const Expression& x);
	void Add_(const Expression& x);
	void Add(const Expression& x);
	Expression* New(const Expression& x);
	Expression* New(Expression* x);
	Expression* New(const int& x);
	void Push_back(const Expression& x);
	void Push_back(Expression* x);
	void Push_back(const int& x);
	void Push_back(const Expression& x, const Expression& y);
	Expression();
	Expression(char t);
	Expression(Val x);
	Expression(int x);
	Expression(const Expression& x);
	Expression(char t, const vector<Expression*>& s);
	Expression(char t, const vector<Expression*>& s1, const vector<Expression*>s2);
	Expression(char t, const Expression& x);
	Expression(char t, const Expression& x, const Expression& y);
	Expression& operator=(const Expression& _);
	Expression& operator=(const int& _);
	bool operator <(const Expression& _)const;
	Expression operator +(const Expression& _)const;
	friend Expression operator +(const int& x, const Expression& y);
	friend Expression operator -(const int& x, const Expression& y);
	friend Expression operator *(const int& x, const Expression& y);
	friend Expression operator ^(const int& x, const Expression& y);
	friend Expression operator /(const int& x, const Expression& y);
	Expression operator +(const int& _)const;
	Expression operator -()const;
	Expression operator -(const Expression& _)const;
	Expression operator *(const Expression& _)const;
	Expression operator *(const int& _)const;
	Expression operator /(const Expression& _)const;
	Expression operator /(const int& _)const;
	Expression operator ^(const Expression& _)const;
	Expression operator ^(const int& _)const;
	bool operator ==(const Expression& _)const;
	bool operator ==(const int _)const;
	Expression& operator +=(const Expression& _);
	Expression& operator -=(const Expression& _);
	Expression& operator *=(const Expression& _);
	Expression& operator *=(const int& _);
	Expression& operator ^=(const Expression& _);
	Expression& operator ^=(const int& _);
	Expression& operator /=(const Expression& _);
	Expression& operator /=(const int& _);
	bool operator !=(const Expression& _)const;
	bool operator !=(const int _)const;
	void Print_()const;
	void Print()const;
	void Print(const string& s)const;
	void Union_Trans(char t, string& s, int l, int ml, int mr, int r, const vector<int>& nxt);
	void Trans(string& s, int l, int r, const vector<int>& nxt);
	void Union_Calc(char t, string& s, int l, int ml, int mr, int r, const vector<int>& nxt);
	void Calc(string& s, int l, int r, const vector<int>& nxt);
	void Read();
};