#pragma once
#include"基本运算.h"
#include"Button.h"
#include"Textbox.h"
#include <direct.h>
#define FOR(x,y,z) for(int x=y,x##_=(int)z;x<x##_;x++)
#define FOO(x,y) for(int x=0,x##_=(int)y.size();x<x##_;x++)
int getwidth(const Val& v) {
	char str[20];
	if (v.t == '0') {
		if (isint(v.v)) sprintf_s(str, 20, "%d", beint(v.v));
		else sprintf_s(str, 20, "%lf", v.v);
		return strlen(str);
	}return 1;
}
struct Font {
	double Scale;
	int depth;
	int U[7][10],D[7][10],H[7][10];
	int UP[7][10], DP[7][10], WP[7][10];
	Font() {
		Scale = 0.8;
		depth = 3;
		UP[0][0] = U[0][0]=10;
		DP[0][0] = D[0][0]=5;
		WP[0][0] = 35;
		H[0][0] = U[0][0]+D[0][0];

		UP[1][0]=UP[2][0] = DP[1][0] =DP[2][0] = 0;
		WP[1][0] =WP[2][0] = 30;
		U[1][0]=U[2][0]=D[1][0]=D[2][0]=15;
		H[1][0] = U[1][0]+D[1][0];
		H[2][0] = U[2][0] + D[2][0];


		UP[3][0] = H[3][0]= - 10;
		DP[3][0] = 0;
		WP[3][0] = 5;

		UP[4][0] = DP[4][0] = 30;
		WP[4][0] = 30;
		H[4][0] =UP[4][0]+DP[4][0];

		UP[5][0] = 0;
		DP[5][0] = 0;
		WP[5][0] = 15;
		H[5][0] = 0;

		U[6][0] = D[6][0]=30;
		WP[6][0] = 30;
		FOR(i, 0, 6)FOR(j, 1, 10) {
			UP[i][j] = ceil(UP[i][j - 1] * Scale);
			DP[i][j] = ceil(DP[i][j - 1] * Scale);
			WP[i][j] = ceil(WP[i][j - 1] * Scale);
			U[i][j] = ceil(U[i][j - 1] * Scale);
			D[i][j] = ceil(D[i][j - 1] * Scale);
			H[i][j] = ceil(H[i][j - 1] * Scale);
		}
	}
	void operator()(int Type, int level, int& u, int& d, int& w)const {
		u += UP[Type][level];
		d += DP[Type][level];
		w += WP[Type][level];
	}
	void operator()(Val v, int level, int& u, int& d, int& w)const {
		LOGFONT old;
		gettextstyle(&old);
		LOGFONT* now = new LOGFONT;
		*now = old;
		now->lfHeight = H[4][level];
		now->lfWidth = WP[4][level];
		settextstyle(now);
		char* str = v.getstr();
		w += textwidth(str);
		u += textheight(str)>>1;
		d += textheight(str)>>1;
		free(str);
		settextstyle(&old);
	}
	void Show(char t, int left, int top, int w, int h) {
		IMAGE img;
		switch (t) {
		case '/': {
			loadimage(&img, _T("分号.jpg"), w, h);
			break;
		}
		case '-':{
			loadimage(&img, _T("减号.jpg"),w,h);
			break;
		}
		case '+': {
			loadimage(&img, _T("加号.jpg"),w,h);
			break;
		}
		case '*': {
			loadimage(&img, _T("点.jpg"), w, h);
			break;
		}
		case '(': {
			loadimage(&img, _T("括号（.jpg"), w, h);
			break;
		}
		case ')': {
			loadimage(&img, _T("括号）.jpg"), w, h);
			break;
		}
		case '#': {
			setlinecolor(BLUE);
			fillrectangle(left, top, left + w-1, top + h-1);
			return;
		}
		}
		putimage(left, top, &img);
	}
	bool Check(int left, int top, int w, int h, int x, int y) {
		return left <= x && x < left + w && top <= y && y < top + h;
	}
	void Show(Val v,int level,int left,int top) {
		LOGFONT old;
		gettextstyle(&old);
		LOGFONT* now=new LOGFONT;
		*now = old;
		now->lfHeight = H[4][level];
		now->lfWidth = WP[4][level];
		settextstyle(now);
		char* str = v.getstr();
		settextcolor(WHITE);
		outtextxy(left, top, str);
		free(str);
		settextstyle(&old);
	}
}font;
//- + * ^ 0 ()
struct Exp {
	Exp* f;
	vector<Exp*>a;
	Val v;
	int u, d, w, level;
	char Type;
	bool negative;
	int left, top;
	Exp() {
		f = NULL;
		u = d = w = level =left=top= 0;
		negative= 0;
	}
	void Add_brackets() {
		Exp* nw = new Exp;
		*nw = *this;
		nw->f = this;
		a.clear();
		a.push_back(nw);
		w += font.WP[5][level] << 1;
		Type = '(';
		negative = 0;
		nw->left += font.WP[5][level];
	}
	void debrackets() {
		if (Type == '(') {
			*this = *a[0];
			w -= font.WP[5][level] << 1;
		}
	}
	~Exp() {
	}
	Exp(Expression& s) {
		f = NULL;
		u = d = w = level = left = top = 0;
		negative = 0;
		Create(&s, NULL, 2,0);
		debrackets();
	}
	Exp(Expression* s) {
		f = NULL;
		u = d = w = level = left = top = 0;
		negative =  0;
		Create(s, NULL, 2,0);
		debrackets();
	}
	void Create(Expression* s, Exp* fa, int b,bool l) {
		v = s->v;
		if (f = fa) {
			f->a.push_back(this);
			level = f->level+l;
		}
		switch (s->Type) {
		case '/': {
			Type = '/';
			Exp *ls=new Exp,*rs = new Exp;
			ls->Create(s->a[0], this, 0,1);
			rs->Create(s->a[1], this, 0,1);
			u = ls->Height();
			d = rs->Height();
			w = max(ls->w, rs->w);
			font(0, level, u, d, w);
			if (b == 2)Add_brackets();
			break;
		}
		case '+': {
			Type = '+';
			FOO(i, s->a) {
				Exp* son = new Exp;
				son->Create(s->a[i], this, 0,0);
				tomax(u, son->u);
				tomax(d, son->d);
				w += son->w;
				if (i && !son->negative)font(1, level, u, d, w);
			}
			if (b)Add_brackets();
			break;
		}
		case '*': {
			if (s->a[0]->isnum() && equ(s->a[0]->v.v, -1)) {
				if (s->size() == 2) {
					if (f)f->a.erase(f->a.end() - 1, f->a.end());
					Create(s->a[1], fa, 0,0);
				}else{
					Type = '*';
					FOR(i, 2, s->size()) {
						Exp* son = new Exp;
						son->Create(s->a[i], this, 1,0);
						tomax(u, son->u);
						tomax(v, son->v);
						w += son->w;
						if(i>2)font(2, level, u, d, w);
					}
				}
				negative = 1;
				font(1, level, u, d, w);
			}else if (s->a[0]->isnum() && s->a[0]->v < 0) {
				negative = 1;
				font(1, level, u, d, w);
				Type = '*';
				*s->a[0] *= -1;
				FOO(i, s->a) {
					Exp* son = new Exp;
					son->Create(s->a[i], this, 1,0);
					tomax(u, son->u);
					tomax(d, son->d);
					w += son->w;
					if (i)font(2, level, u, d, w);
				}
				*s->a[0] *= -1;
			}else {
				Type = '*';
				FOO(i, s->a) {
					Exp* son = new Exp;
					son->Create(s->a[i], this, 1,0);
					tomax(u, son->u);
					tomax(d, son->d);
					w += son->w;
					if (i)font(2, level, u, d, w);
				}
			}
			if (b)Add_brackets();
			break;
		}
		case '^': {
			Type = '^';
			Exp *ls = new Exp,*rs = new Exp;
			ls->Create(s->a[0], this, 2,0);
			rs->Create(s->a[1], this, 0,1);
			u = ls->u + rs->Height();
			d = ls->d;
			w = ls->w + rs->w;
			font(Type, level, u, d, w);
			if (b == 2)Add_brackets();
			break;
		}
		case '0': {
			Type = '0';
			if (!b && s->v.t == '0' && s->v.v < 0) {
				negative = 1;
				font(1, level, u, d, w);
				v = -v;
			}
			font(v, level, u, d, w);
			break;
		}
		case '#': {
			Type = '#';
			font(6, level, u, d, w);
			break;
		}
		}
	}
	void Show(int Left, int Top){
		left = Left, top = Top;
		int W=w;
		int mid = top + u;
		int cur = left;
		if (negative) {
			font.Show('-', cur, mid - font.U[1][level], font.WP[1][level], font.H[1][level]);
			cur += font.WP[1][level];
			W -= font.WP[1][level];
		}
		switch (Type) {
		case '/': {
			a[0]->Show(cur + (W - a[0]->w) / 2, top);
			a[1]->Show(cur + (W - a[1]->w) / 2, mid + font.D[0][level]);
			font.Show('/', cur, top + a[0]->Height(), W, font.H[0][level]);
			break;
		}
		case '+': {
			FOO(i, a) {
				if (i && !a[i]->negative) {
					font.Show('+', cur, mid - font.U[1][level], font.WP[1][level], font.H[1][level]);
					cur += font.WP[1][level];
				}
				a[i]->Show(cur, mid - a[i]->u);
				cur += a[i]->w;
			}
			break;
		}
		case '*': {
			FOO(i, a) {
				if (i) {
					font.Show('*', cur, mid - font.U[2][level], font.WP[2][level], font.H[2][level]);
					cur += font.WP[2][level];
				}
				a[i]->Show(cur, mid - a[i]->u);
				cur += a[i]->w;
			}
			break;
		}
		case '^': {
			a[0]->Show(cur, mid - a[0]->u);
			a[1]->Show(cur + a[0]->w + font.WP[3][level], mid - a[0]->u - a[1]->Height() - font.UP[3][level]);
			break;
		}
		case '0': {
			font.Show(v, level, cur, top);
			break;
		}
		case '#': {
			font.Show('#', level, cur, top);
			break;
		}
		case '(': {
			font.Show('(', cur, top, font.WP[5][level], Height());
			font.Show(')', cur + W - font.WP[5][level], top, font.WP[5][level], Height());
			a[0]->Show(cur + font.WP[5][level], top);
			break;
		}
		}
	}
	Val Value()const { return v; }
	int Height()const { return u + d; }
	int Width()const { return w; }
	int size()const { return a.size(); }
	Exp* Head() { return a.empty() ? this : a[0]->Head(); }
	Exp* End() { return a.empty() ? this : a[0]->End(); }
	Exp(Exp* fa, int l, bool n) {
		f = fa;
		level = l;
		v = '#';
		Type = 6;
	}
	Expression* Calc() {
		Expression* nw = new Expression;
		bool flag = 0;
		switch (Type) {
		case '/': {
			Expression *ls = a[0]->Calc(), * rs = a[1]->Calc();
			if (ls && rs) *nw = *ls / *rs;
			else flag = 1;
			break;
		}
		case '+': {
			*nw = 0;
			FOO(i, a) {
				Expression* son = a[i]->Calc();
				if (son) *nw += *son;
				else {
					flag = 1;
					break;
				}
			}
			break;
		}
		case '*': {
			*nw = 1;
			FOO(i, a) {
				Expression* son = a[i]->Calc();
				if (son)*nw *= *son;
				else {
					flag = 1;
					break;
				}
			}
			break;
		}
		case '^': {
			Expression* ls = a[0]->Calc(), * rs = a[1]->Calc();
			if (ls && rs) *nw = *ls ^ *rs;
			else flag = 1;
			break;
		}
		case '0': {
			*nw = v;
			break;
		}
		case '#': {
			flag = 1;
			setlinecolor(RED);
			fillrectangle(left, top, left + w-1, top + Height()-1);
			break;
		}
		case '(': {
			nw = a[0]->Calc();
			break;
		}
		}
		if (flag) {
			free(nw);
			return NULL;
		}
		if (negative)*nw = -*nw;
		return nw;
	}
	/*
	bool Check(int x, int y,Exp* cur,int& pos) {
		if (x >= left && x < left + w && y >= top && y < top + Height()) {
			int W = w;
			int mid = top + u;
			int cur = left;
			if (negative) {
				font.Check('-', cur, mid - font.U[1][level], font.WP[1][level], font.H[1][level]);
				cur += font.WP[1][level];
				W -= font.WP[1][level];
			}
			switch (Type) {
			case '/': {
				a[0]->Check(cur + (W - a[0]->w) / 2, top);
				a[1]->Check(cur + (W - a[1]->w) / 2, mid + font.D[0][level]);
				font.Check('/', cur, top + a[0]->Height(), W, font.H[0][level]);
				break;
			}
			case '+': {
				FOO(i, a) {
					if (i && !a[i]->negative) {
						font.Check('+', cur, mid - font.U[1][level], font.WP[1][level], font.H[1][level]);
						cur += font.WP[1][level];
					}
					a[i]->Check(cur, mid - a[i]->u);
					cur += a[i]->w;
				}
				break;
			}
			case '*': {
				FOO(i, a) {
					if (i) {
						font.Check('*', cur, mid - font.U[2][level], font.WP[2][level], font.H[2][level]);
						cur += font.WP[2][level];
					}
					a[i]->Check(cur, mid - a[i]->u);
					cur += a[i]->w;
				}
				break;
			}
			case '^': {
				a[0]->Check(cur, mid - a[0]->u);
				a[1]->Check(cur + a[0]->w + font.WP[3][level], mid - a[0]->u - a[1]->Height() - font.UP[3][level]);
				break;
			}
			case '0': {
				font.Check(v, level, cur, top);
				break;
			}
			case '#': {
				font.Check('#', level, cur, top);
				break;
			}
			case '(': {
				if (font.Check(left, top, font.WP[5][level], Height(), x, y)) {
				}
				font.Check(')', left + w - font.WP[5][level], top, font.WP[5][level], Height());
				cur += font.WP[5][level];
				W -= font.WP[5][level] << 1;
			}
			}
		}
	}
	*/
};
void Show(Expression* p, int left, int top) {
	Exp res(p);
	res.Show(left, top);
}
void Show(Expression& p, int left, int top) {
	Exp res(p);
	res.Show(left, top);
}
/*
void Work() {
	Exp* p = new Exp(50,50);
	Exp* cur = p;
	int pos=0;
	EasyButton OK(1200,50,1300,100,"OK");
	while(1){
		ExMessage msg;
		getmessage(&msg, WM_LBUTTONDOWN|EM_CHAR);
		if (msg.message == WM_LBUTTONDOWN) {
			if (OK.Check(msg.x, msg.y)) {
				Expression* ans=p->Calc();
				if (ans) Show(ans,50, 250);
			}
			else if (p->Check(msg.x,msg.y,cur,pos)){

			}
		}
		else {

		}
	}
}
*/