#pragma once
#define e 2.718
struct Data {
	int n;
	double *x, *y;
	double sum_x, sum_y, sum_xx, sum_xy, sum_yy;
	double avg_x, avg_y;
	double var_x, var_y, var_xy;
	Data() {}
	void Init();
	template<class T>Data(int nn, T* xx, T* yy) :n(nn), x(xx), y(yy) { Init(); }
	void read(int n, double txtx[], double txty[]);
	void lnx();
	void lny();
	void recx();
	void F1();
	void F2();
	void F3();
};
#undef e