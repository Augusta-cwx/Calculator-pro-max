#pragma once
#include"标准化输出.h"
void test() {
	Expression E = Expression('E');
	Expression tmp;
	tmp.Read();
	tmp.Print();
	initgraph(1440, 640);
	setbkcolor(BLACK);
	settextcolor(BLACK);
	cleardevice();
	Show(&tmp,50, 50);
	while (1);
	setlinecolor(BLUE);
	setlinestyle(PS_SOLID, 10);
	int x = 300;
	IMAGE img1,img2;
	loadimage(&img1, _T("D:\\大学学习\\科学与社会\\项目代码\\可视化\\加号.jpg"), x, x);
	loadimage(&img2, _T("D:\\大学学习\\科学与社会\\项目代码\\可视化\\减号.jpg"), 900, 300);
	putimage(100, 200, &img1);
	putimage(400, 200, &img2);
	//line(100+x/2, 100, 100+x/2, 100+x);
	//line(100, 100+x/2, 100+x, 100+x/2);
	LOGFONT now;
	gettextstyle(&now);
	now.lfHeight = 100;
	now.lfWidth = 100;
	now.lfWeight = 100;
	settextstyle(&now);
	//outtextxy(100, 100, "ABCD");
	//outtextxy(100, 200, '+');
	/*
	EasyTextBox warning;
	fillrectangle(100, 100, 300, 200);
	fillrectangle(80, 212, 320, 218);
	fillrectangle(100, 230, 300, 330);
	*/
	while (1);
}
/*
+:
	3_50
	2_30
	1_10
*/