#pragma once

class EasyButton
{
private:
	int left,top,right,bottom;	// �ؼ�����
	char* text;							// �ؼ�����
	void (*userfunc)();						// �ؼ���Ϣ

public:
	EasyButton() {
		left = top = right = bottom = 0;
		text = NULL;
		userfunc = NULL;
	}
	EasyButton(int x1, int y1, int x2, int y2, const char* title, void (*func)()=NULL) {
		text = new char[strlen(title) + 1];
		strcpy_s(text, strlen(title) + 1, title);
		left = x1, top = y1, right = x2, bottom = y2;
		userfunc = func;
	}
	void Create(int x1, int y1, int x2, int y2, const char* title, void (*func)())
	{
		text = new char[strlen(title) + 1];
		strcpy_s(text, strlen(title) + 1, title);
		left = x1, top = y1, right = x2, bottom = y2;
		userfunc = func;

		// �����û�����
		Show();
	}

	~EasyButton()
	{
		if (text != NULL)
			delete[] text;
	}

	bool Check(int x, int y)
	{
		return (left <= x && x <= right && top <= y && y <= bottom);
	}

	// ���ƽ���
	void Show()
	{
		int oldlinecolor = getlinecolor();
		int oldbkcolor = getbkcolor();
		int oldfillcolor = getfillcolor();

		setlinecolor(BLACK);			// ���û�����ɫ
		setbkcolor(WHITE);				// ���ñ�����ɫ
		setfillcolor(WHITE);			// ���������ɫ
		fillrectangle(left, top, right, bottom);
		outtextxy(left + (right - left - textwidth(text) + 1) / 2, top + (bottom - top - textheight(text) + 1) / 2, text);

		setlinecolor(oldlinecolor);
		setbkcolor(oldbkcolor);
		setfillcolor(oldfillcolor);
	}

	void OnMessage()
	{
		if (userfunc != NULL)
			userfunc();
	}
};