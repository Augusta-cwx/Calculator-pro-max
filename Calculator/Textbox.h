#pragma once
#include"���ú���.h"
class EasyTextBox
{
private:
	int left = 0, top = 0, right = 0, bottom = 0;	// �ؼ�����
	char* text = NULL;							// �ؼ�����
	size_t maxlen = 0;									// �ı���������ݳ���

public:
	void Create(int x1, int y1, int x2, int y2, int max)
	{
		maxlen = max;
		text = new char[maxlen];
		text[0] = 0;
		left = x1, top = y1, right = x2, bottom = y2;

		// �����û�����
		Show();
	}

	~EasyTextBox()
	{
		if (text != NULL)
			delete[] text;
	}

	char* Text()
	{
		return text;
	}

	bool Check(int x, int y)
	{
		return (left <= x && x <= right && top <= y && y <= bottom);
	}

	// ���ƽ���
	void Show()
	{
		// ���ݻ���ֵ
		int oldlinecolor = getlinecolor();
		int oldbkcolor = getbkcolor();
		int oldfillcolor = getfillcolor();

		setlinecolor(LIGHTGRAY);		// ���û�����ɫ
		setbkcolor(0xeeeeee);			// ���ñ�����ɫ
		setfillcolor(0xeeeeee);			// ���������ɫ
		fillrectangle(left, top, right, bottom);
		outtextxy(left + 10, top + 5, text);

		// �ָ�����ֵ
		setlinecolor(oldlinecolor);
		setbkcolor(oldbkcolor);
		setfillcolor(oldfillcolor);
	}

	double Get_double()
	{
		ExMessage msg;
		// ���ݻ���ֵ
		int oldlinecolor = getlinecolor();
		int oldbkcolor = getbkcolor();
		int oldfillcolor = getfillcolor();

		setlinecolor(BLACK);			// ���û�����ɫ
		setbkcolor(WHITE);				// ���ñ�����ɫ
		setfillcolor(WHITE);			// ���������ɫ
		fillrectangle(left, top, right, bottom);
		outtextxy(left + 10, top + 5, text);

		int width = textwidth(text);	// �ַ����ܿ��
		int counter = 0;				// �����˸������
		bool binput = true;				// �Ƿ�������


		//ExMessage msg;
		while (binput)
		{
			while (binput && peekmessage(&msg, EM_MOUSE | EM_CHAR, false))	// ��ȡ��Ϣ����������Ϣ�����ó�
			{
				if (msg.message == WM_LBUTTONDOWN)
				{
					// ���������ı������棬�����ı�����
					if (!Check(msg.x, msg.y))
					{
						binput = false;
						clearrectangle(left + 10 + width + 1, top + 3, left + 10 + width + 1, bottom - 3);
						return atof(text);
					}
				}
				else if (msg.message == WM_CHAR)
				{
					size_t len = strlen(text);
					switch (msg.ch)
					{
					case '\b':				// �û����˸����ɾ��һ���ַ�
						if (len > 0)
						{
							text[len - 1] = 0;
							width = textwidth(text);
							counter = 0;
							clearrectangle(left + 10 + width, top + 1, right - 1, bottom - 1);
						}
						break;
					case '\r':				// �û����س����������ı�����
					case '\n':
						binput = false;
						clearrectangle(left + 10 + width + 1, top + 3, left + 10 + width + 1, bottom - 3);
						return atof(text);
					case '0':case '1':case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9':case '.':
						if (len < maxlen - 1)
						{
							text[len++] = msg.ch;
							text[len] = 0;

							clearrectangle(left + 10 + width + 1, top + 3, left + 10 + width + 1, bottom - 3);	// ������Ĺ��
							width = textwidth(text);				// ���¼����ı�����
							counter = 0;
							outtextxy(left + 10, top + 5, text);		// ����µ��ַ���
						}break;
					}
				}
				peekmessage(NULL, EM_MOUSE | EM_CHAR);// ����Ϣ���������ոմ������һ����Ϣ
				output(peekmessage(NULL, EM_MOUSE, false), 50, 50);
				output("   ", 50, 50);
				//�۲��Ӱ����
			}

			// ���ƹ�꣨�����˸����Ϊ 20ms * 32��
			counter = (counter + 1) % 32;
			if (counter < 16)
				line(left + 10 + width + 1, top + 3, left + 10 + width + 1, bottom - 3);				// �����
			else
				clearrectangle(left + 10 + width + 1, top + 3, left + 10 + width + 1, bottom - 3);		// �����

			// ��ʱ 20ms
			Sleep(20);
		}

		clearrectangle(left + 10 + width + 1, top + 3, left + 10 + width + 1, bottom - 3);	// �����

		// �ָ�����ֵ
		setlinecolor(oldlinecolor);
		setbkcolor(oldbkcolor);
		setfillcolor(oldfillcolor);

		Show();
	}
	char* Get_string()
	{
		// ���ݻ���ֵ
		int oldlinecolor = getlinecolor();
		int oldbkcolor = getbkcolor();
		int oldfillcolor = getfillcolor();

		setlinecolor(BLACK);			// ���û�����ɫ
		setbkcolor(WHITE);				// ���ñ�����ɫ
		setfillcolor(WHITE);			// ���������ɫ
		fillrectangle(left, top, right, bottom);
		outtextxy(left + 10, top + 5, text);

		int width = textwidth(text);	// �ַ����ܿ��
		int counter = 0;				// �����˸������
		bool binput = true;				// �Ƿ�������


		ExMessage msg;
		while (binput)
		{
			while (binput && peekmessage(&msg, EM_MOUSE | EM_CHAR, false))	// ��ȡ��Ϣ����������Ϣ�����ó�
			{
				if (msg.message == WM_LBUTTONDOWN)
				{
					// ���������ı������棬�����ı�����
					if (!Check(msg.x, msg.y))
					{
						binput = false;
						clearrectangle(left + 10 + width + 1, top + 3, left + 10 + width + 1, bottom - 3);
						return text;
					}
				}
				else if (msg.message == WM_CHAR)
				{
					size_t len = strlen(text);
					switch (msg.ch)
					{
					case '\b':				// �û����˸����ɾ��һ���ַ�
						if (len > 0)
						{
							text[len - 1] = 0;
							width = textwidth(text);
							counter = 0;
							clearrectangle(left + 10 + width, top + 1, right - 1, bottom - 1);
						}
						break;
					case '\r':				// �û����س����������ı�����
					case '\n':
						binput = false;
						clearrectangle(left + 10 + width + 1, top + 3, left + 10 + width + 1, bottom - 3);
						return text;
					default:
						if (len < maxlen - 1)
						{
							text[len++] = msg.ch;
							text[len] = 0;

							clearrectangle(left + 10 + width + 1, top + 3, left + 10 + width + 1, bottom - 3);	// ������Ĺ��
							width = textwidth(text);				// ���¼����ı�����
							counter = 0;
							outtextxy(left + 10, top + 5, text);		// ����µ��ַ���
						}
					}
				}
				peekmessage(NULL, EM_MOUSE | EM_CHAR);				// ����Ϣ���������ոմ������һ����Ϣ
			}

			// ���ƹ�꣨�����˸����Ϊ 20ms * 32��
			counter = (counter + 1) % 32;
			if (counter < 16)
				line(left + 10 + width + 1, top + 3, left + 10 + width + 1, bottom - 3);				// �����
			else
				clearrectangle(left + 10 + width + 1, top + 3, left + 10 + width + 1, bottom - 3);		// �����

			// ��ʱ 20ms
			Sleep(20);
		}

		clearrectangle(left + 10 + width + 1, top + 3, left + 10 + width + 1, bottom - 3);	// �����

		// �ָ�����ֵ
		setlinecolor(oldlinecolor);
		setbkcolor(oldbkcolor);
		setfillcolor(oldfillcolor);

		Show();
	}
};