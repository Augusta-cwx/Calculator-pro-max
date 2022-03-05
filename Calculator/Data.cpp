#pragma once
#include"Data.h"
#include"常用函数.h"
#define e 2.718
void Data::Init() {
	sum_x = sum_y = sum_xx = sum_xy = sum_yy = 0;
	for (int i = 0; i < n; i++) {
		sum_x += x[i];
		sum_y += y[i];
		sum_xx += x[i] * x[i];
		sum_xy += x[i] * y[i];
		sum_yy += y[i] * y[i];
	}
	avg_x = sum_x / n;
	avg_y = sum_y / n;
	var_x = var_y = var_xy = 0;
	for (int i = 0; i < n; i++) {
		var_x += (x[i] - avg_x) * (x[i] - avg_x);
		var_y += (y[i] - avg_y) * (y[i] - avg_y);
		var_xy += (x[i] - avg_x) * (y[i] - avg_y);
	}
	var_x /= n;
	var_y /= n;
	var_xy /= n;
}
void Data::read(int N, double txtx[], double txty[]) {
	x = new double[N];
	y = new double[N];
	n = N;
	for (int i = 0; i < n; i++) {
		x[i] = txtx[i];
		y[i] = txty[i];
	}
	Init();

}
void Data::lnx() {//新增 
	for (int i = 0; i < n; i++) {
		x[i] = log(x[i]);
	}
	Init();
}
void Data::lny() { //新增 
	for (int i = 0; i < n; i++) {
		y[i] = log(y[i]);
	}
	Init();
}
void Data::recx()//新增 
{
	for (int i = 0; i < n; i++) {
		x[i] = 1 / x[i];
	}
	Init();
}
void Data::F1() {//y=ax+b
	double r = var_xy / sqrt(var_x * var_y);
	double a = (n * sum_xy - sum_x * sum_y) / (n * sum_xx - sum_x * sum_x);
	double b = (sum_y * sum_xx - sum_x * sum_xy) / (n * sum_xx - sum_x * sum_x);
	char a1[20];
	char b1[20];
	char r1[20];
	sprintf_s(a1, 20, "%.2lf", a);
	sprintf_s(b1, 20, "%.2lf", b);
	sprintf_s(r1, 20, "%.2lf", r);
	outtextxy(0, 0, "a=");
	outtextxy(2 + textwidth("a="), 0, a1);
	outtextxy(0, 20, "b=");
	outtextxy(2 + textwidth("a="), 20, b1);
	outtextxy(0, 40, "r=");
	outtextxy(2 + textwidth("a="), 40, r1);
}
void Data::F2() {//y=ax+b
	double r = var_xy / sqrt(var_x * var_y);
	double a = (n * sum_xy - sum_x * sum_y) / (n * sum_xx - sum_x * sum_x);
	double b = (sum_y * sum_xx - sum_x * sum_xy) / (n * sum_xx - sum_x * sum_x);
	char a1[20];
	char b1[20];
	char r1[20];
	sprintf_s(a1, 20, "%.2lf", a);
	sprintf_s(b1, 20, "%.2lf", b);
	sprintf_s(r1, 20, "%.2lf", r);
	outtextxy(0, 0, "a=");
	outtextxy(2 + textwidth("a="), 0, a1);
	outtextxy(0, 20, "b=");
	outtextxy(2 + textwidth("a="), 20, b1);
	outtextxy(0, 40, "r=");
	outtextxy(2 + textwidth("a="), 40, r1);

}
void Data::F3() {//y=ax+b
	double r = var_xy / sqrt(var_x * var_y);
	double a = (n * sum_xy - sum_x * sum_y) / (n * sum_xx - sum_x * sum_x);
	double b = (sum_y * sum_xx - sum_x * sum_xy) / (n * sum_xx - sum_x * sum_x);
	char a1[20];
	char b1[20];
	char r1[20];
	sprintf_s(a1, 20, "%.2lf", a);
	sprintf_s(b1, 20, "%.2lf", b);
	sprintf_s(r1, 20, "%.2lf", r);
	outtextxy(0, 0, "a=");
	outtextxy(2 + textwidth("a="), 0, a1);
	outtextxy(0, 20, "b=");
	outtextxy(2 + textwidth("a="), 20, b1);
	outtextxy(0, 40, "r=");
	outtextxy(2 + textwidth("a="), 40, r1);
}
#undef e