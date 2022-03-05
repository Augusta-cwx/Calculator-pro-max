#pragma once
#include"常用函数.h"
void button(int x, int y, int w, int h, const char* text)
{
	//setbkmode(TRANSPARENT);
	setfillcolor(BROWN);
	fillroundrect(x, y, x + w, y + h, 10, 10);
	int tx, ty;
	char b[50] = "button";
	strcpy_s(b, strlen(text) + 1, text);
	tx = x + (w - textwidth(text)) / 2;
	ty = y + (h - textheight(text)) / 2;
	outtextxy(tx, ty, text);
}
int menu0()
{
	ExMessage msg;
	button(200, 200, 150, 20, "1.线性回归");
	button(200, 220, 150, 20, "2.矩阵运算");
	button(200, 240, 150, 20, "3.数值运算");
	while (true)
	{
		if (peekmessage(&msg, EM_MOUSE) && msg.message == WM_LBUTTONDOWN && 200 <= msg.x && msg.x <= 350)
		{
			return 1 + (msg.y - 200) / 20;
		}
	}
	return 0;
}
#include<cmath>
#define e 2.718
int menu1()
{
	ExMessage msg;
	button(200, 200, 200, 20, "0.return");
	button(200, 220, 200, 20, "1.y=a+bx");
	button(200, 240, 200, 20, "2.y=a+blnx");
	button(200, 260, 200, 20, "3.y=ae^(bx)");
	button(200, 280, 200, 20, "4.y=ab^(x)");
	button(200, 300, 200, 20, "5.y=ax^(b)");
	button(200, 320, 200, 20, "6.y=a+b/x");
	button(200, 340, 200, 20, "7.Single variable statistics");
	while (true)
	{
		if (peekmessage(&msg, EM_MOUSE) && msg.message == WM_LBUTTONDOWN && 200 <= msg.x && msg.x <= 400)
		{
			return (msg.y - 200) / 20;
		}
	}
	return 0;
}
#undef e