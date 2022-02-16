#pragma once
#define e 2.718
struct Data {
	int n;
	double x[maxn], y[maxn];
	double sum_x, sum_y, sum_xx, sum_xy, sum_yy;
	double avg_x, avg_y;
	double var_x, var_y, var_xy;
	Data() {}
	void Init() {
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
	template<class T>Data(int nn, T* xx, T* yy) :n(nn), x(xx), y(yy) { Init(); }
	void read(int n, double txtx[], double txty[]) {

		for (int i = 0; i < n; i++) {
			x[i] = txtx[i];
			y[i] = txty[i];
		}

	}
	void lnx() {//新增 
		for (int i = 0; i < n; i++) {
			x[i] = log(x[i]);
		}
		Init();
	}
	void lny() { //新增 
		for (int i = 0; i < n; i++) {
			y[i] = log(y[i]);
		}
		Init();
	}
	void recx()//新增 
	{
		for (int i = 0; i < n; i++) {
			x[i] = 1 / x[i];
		}
		Init();
	}
	void F1() {//y=ax+b
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
	void F2() {//y=ax+b
		double r = var_xy / sqrt(var_x * var_y);
		double a = (n * sum_xy - sum_x * sum_y) / (n * sum_xx - sum_x * sum_x);
		double b = (sum_y * sum_xx - sum_x * sum_xy) / (n * sum_xx - sum_x * sum_x);
		char* a1 = (char*)malloc(sizeof(pow(e, a)));
		char* b1 = (char*)malloc(sizeof(b));
		char* r1 = (char*)malloc(sizeof(r));
		sprintf_s(a1, 60, "%.2lf", a);
		sprintf_s(b1, 60, "%.2lf", b);
		sprintf_s(r1, 60, "%.2lf", r);
		outtextxy(0, 0, "a=");
		outtextxy(2 + textwidth("a="), 0, a1);
		outtextxy(0, 20, "b=");
		outtextxy(2 + textwidth("a="), 20, b1);
		outtextxy(0, 40, "r=");
		outtextxy(2 + textwidth("a="), 40, r1);

	}
	void F3() {//y=ax+b
		double r = var_xy / sqrt(var_x * var_y);
		double a = (n * sum_xy - sum_x * sum_y) / (n * sum_xx - sum_x * sum_x);
		double b = (sum_y * sum_xx - sum_x * sum_xy) / (n * sum_xx - sum_x * sum_x);
		char* a1 = (char*)malloc(sizeof(pow(e, a)));
		char* b1 = (char*)malloc(sizeof(pow(e, b)));
		char* r1 = (char*)malloc(sizeof(r));
		sprintf_s(a1, 60, "%.2lf", a);
		sprintf_s(b1, 60, "%.2lf", b);
		sprintf_s(r1, 60, "%.2lf", r);
		outtextxy(0, 0, "a=");
		outtextxy(2 + textwidth("a="), 0, a1);
		outtextxy(0, 20, "b=");
		outtextxy(2 + textwidth("a="), 20, b1);
		outtextxy(0, 40, "r=");
		outtextxy(2 + textwidth("a="), 40, r1);
	}
};
#undef e