#include<iostream>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<easyx.h>
#include<conio.h>
#include<Windows.h>
#include"menu.h"
#include"Button.h"
#include"Data.h"
#include"Textbox.h"
#include"test.h"
using namespace std;
char*  double2str(double data)
{
	char str[256];
	sprintf_s(str, "%.6lf\t", data); //%.6lf\n  d=lf
	return str;
}

void lr(){
	Data *d=new Data;
	EasyButton *btnOK=new EasyButton;//
	int ch = menu1();
	int  i;
	switch (ch)
	{
	case 0:
		break;
	default:
		cleardevice();
		EasyTextBox* txtn = new EasyTextBox[1];
		outtextxy(250 ,100, "请输入数据组数：");
		txtn[0].Create(250, 150,350, 200, 10);
		cleardevice();
		int n = (int)txtn[0].Get_double();
		cleardevice();
		EasyTextBox* txtx = new EasyTextBox[n];
		double* x1 = new double[n];
		EasyTextBox* txty = new EasyTextBox[n];
		double* y1 = new double[n];
		btnOK[0].Create(420, 150, 500, 175, "OK", NULL);
		outtextxy(200, 75, "x"); outtextxy(320, 75, "y");
		
		for (i = 0; i < n; i++)
		{
			txtx[i].Create(150, 110 + 30 * i, 250, 130 + 30 * i, 10);
			txty[i].Create(270, 110 + 30 * i, 370, 130 + 30 * i, 10);
		}
		ExMessage msg;
		while (true)
		{
			msg = getmessage(EM_MOUSE);			// 获取消息输入
			if (msg.message == WM_LBUTTONDOWN)
			{
				for (i = 0; i < n; i++) {
				// 判断控件
					if (txtx[i].Check(msg.x, msg.y))     x1[i] = txtx[i].Get_double();
					else if (txty[i].Check(msg.x, msg.y))     y1[i] = txty[i].Get_double();
					else if (btnOK[0].Check(msg.x, msg.y)) {
						btnOK[0].OnMessage();
						d[0].read(n, x1, y1);
						switch (ch)
						{
						case 1:d[0].F1(); break;
						case 2:d[0].lnx(); d[0].F1(); break;//y=a+blnx
						case 3:d[0].lny(); d[0].F2(); break;//lny=lna+bx//a=pow(e,a);???
						case 4:d[0].lny(); d[0].F3(); break;//lny=lna+xlnb//a=pow(e,a);b=pow(e,b);???
						case 5:d[0].lnx(); d[0].lny(); d[0].F2(); break;//	lny=lna+blnx//a=pow(e,a);???
						case 6:d[0].recx(); d[0].F1(); break;//y=a+b/x
						}
					}
				}
			}
		}
		break;
	}
}
int main()
{
	//基本运算光标测试
 test();
	//return 0;

	// 创建图形窗口
	initgraph(640, 480);

	// 简单绘制界面
	setbkcolor(0xeeeeee);
	settextcolor(BLACK);
	cleardevice();
	int m = menu0();
	while (1)
	{
		switch (m)
		{
		case 1:lr();
			break;
		case 2:
			break;
		case 3:
		default:
			break;
		}
	}
	closegraph();
	return 0;
}