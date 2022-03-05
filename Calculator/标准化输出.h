#pragma once
#include"基本运算.h"
#include"Button.h"
#include"Textbox.h"
#include <direct.h>
#define FOR(x,y,z) for(int x=y,x##_=(int)z;x<x##_;x++)
#define FOO(x,y) for(int x=0,x##_=(int)y.size();x<x##_;x++)
int getlen(const Val& v) {
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
	int U[7][10],D[7][10],H[7][10], W[7][10];
	int UP[7][10], DP[7][10];
	Font() {
		Scale = 0.8;
		depth = 3;
		UP[0][0] = U[0][0]=10;
		DP[0][0] = D[0][0]=5;
		W[0][0] = 35;
		H[0][0] = U[0][0]+D[0][0];

		UP[1][0]=UP[2][0] = DP[1][0] =DP[2][0] = 0;
		W[1][0] =W[2][0] = 30;
		U[1][0]=U[2][0]=D[1][0]=D[2][0]=15;
		H[1][0] = U[1][0]+D[1][0];
		H[2][0] = U[2][0] + D[2][0];


		UP[3][0] = H[3][0]= - 10;
		DP[3][0] = 0;
		W[3][0] = 5;

		UP[4][0] = DP[4][0] = 30;
		W[4][0] = 30;
		H[4][0] =UP[4][0]+DP[4][0];

		UP[5][0] = 0;
		DP[5][0] = 0;
		W[5][0] = 15;
		H[5][0] = 0;

		U[6][0] = D[6][0]=30;
		W[6][0] = 30;
		FOR(i, 0, 6)FOR(j, 1, 10) {
			UP[i][j] = ceil(UP[i][j - 1] * Scale);
			DP[i][j] = ceil(DP[i][j - 1] * Scale);
			W[i][j] = ceil(W[i][j - 1] * Scale);
			U[i][j] = ceil(U[i][j - 1] * Scale);
			D[i][j] = ceil(D[i][j - 1] * Scale);
			H[i][j] = ceil(H[i][j - 1] * Scale);
		}
	}
	void operator()(int Type, int level, int& u, int& d, int& w)const {
		u += UP[Type][level];
		d += DP[Type][level];
		w += W[Type][level];
	}
	void operator()(const string& str, int level, int& u, int& d, int& w)const {
		//return;
		LOGFONT old;
		gettextstyle(&old);
		LOGFONT* now = new LOGFONT;
		*now = old;
		now->lfHeight = H[4][level];
		now->lfWidth = W[4][level];
		settextstyle(now);
		w += textwidth(str.c_str());
		u += textheight(str.c_str())>>1;
		d += textheight(str.c_str())+1>>1;
		settextstyle(&old);
	}
	void Show(char t, int left, int top, int w, int h) {
		//printf("{%c}", t); return;
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
			setlinecolor(GREEN);
			rectangle(left, top, left + w-1, top + h-1);
			return;
		}
		}
		putimage(left, top, &img);
	}
	bool Check(int left, int top, int w, int h, int x, int y) {
		return left <= x && x < left + w && top <= y && y < top + h;
	}
	void Show(const string& str,int level,int left,int top) {
		//printf("{%s}", str.c_str()); return;
		LOGFONT old;
		gettextstyle(&old);
		LOGFONT* now=new LOGFONT;
		*now = old;
		now->lfHeight = H[4][level];
		now->lfWidth = W[4][level];
		settextstyle(now);
		settextcolor(WHITE);
		outtextxy(left, top, str.c_str());
		settextstyle(&old);
	}
}font;
struct Exp {
	Exp* f;
	vector<Exp*>a;
	int u, d, w, level;
	char Type;
	bool negative;
	int left, top;
	string text;
	void getstr(const string& s){
		text = s;
		if (s.empty())Type = '#';
		else Type = '0';
		negative = 0;
		a.clear();
	}
	Exp() {
		Type = '#';
		f = NULL;
		text ="";
		u = d = w = level = left = top = 0;
		negative= 0;
		font(text, level,u, d, w);
	}
	void addx(int x) {
		left += x;
		FOO(i, a)a[i]->addx(x);
	}
	void addy(int y) {
		top += y;
		FOO(i, a)a[i]->addy(y);
	}
	void add(char Type){
		switch (Type) {
		case '/':font(0, level, u, d, w); break;
		case '+':case '-':font(1, level, u, d, w); break;
		case '*':font(2, level, u, d, w); break;
		case '^':font(3, level, u, d, w); break;
		case '#':font("#", level, u, d, w); break;
		case '(':font(5, level, u, d, w); font(5, level, u, d, w); break;
		}
	}
	void add(const string& str) {
		font(str, level, u, d, w);
	}
	void push_back(Exp* son) {
		a.push_back(son);
		/*
		if (son->f) {
			FOO(i, son->f->a)if (son->f->a[i] == this) {
				son->f->a.erase(son->f->a.begin() + i);
				break;
			}
		}
		*/
		son->f = this;
	}
	void insert(const vector<Exp*>::iterator pos, Exp* son) {
		a.insert(pos, son);
		son->f=this;
	}
	void Add_brackets() {
		Exp* nw = new Exp;
		*nw = *this;
		a.clear();
		push_back(nw);
		w += font.W[5][level] << 1;
		Type = '(';
		negative = 0;
		nw->addx(font.W[5][level]);
	}
	void debrackets() {
		if (Type == '(') {
			Exp* fa = f;
			*this = *a[0];
			f = fa;
			addx(-font.W[5][level]);
			w -= font.W[5][level] << 1;
		}
	}
	~Exp() {
		if (f) {
			FOO(i,f->a)if (f->a[i] == this) {
				f->a.erase(f->a.begin()+i);
				break;
			}
		}
	}
	Exp(int Left, int Top) {
		f = NULL;
		text = "";
		Type = '#';
		level=u = d = w = 0;
		negative = 0;
		left = Left;
		top = Top;
	}
	Exp(Expression& s) {
		f = NULL;
		text = "";
		u = d = w = level = left = top = 0;
		negative = 0;
		Create(&s, NULL, 2,0);
		debrackets();
	}
	Exp(Expression* s) {
		f = NULL;
		text = "";
		u = d = w = level = left = top = 0;
		negative =  0;
		Create(s, NULL, 2,0);
		debrackets();
	}
	void Create(Expression* s, Exp* fa, int b,bool l) {
		if (fa) {
			fa->push_back(this);
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
			add('/');
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
				if (i && !son->negative)add('+');
			}
			if (b)Add_brackets();
			break;
		}
		case '*': {
			if (s->a[0]->isnum() && equ(s->a[0]->v.v, -1)) {
				if (s->size() == 2) {
					Type = '+';
					Exp* son = new Exp;
					son->Create(s->a[1], this, 0, 0);
					tomax(u, son->u);
					tomax(d, son->d);
					w += son->w;
				}else{
					Type = '*';
					FOR(i, 2, s->size()) {
						Exp* son = new Exp;
						son->Create(s->a[i], this, 1,0);
						tomax(u, son->u);
						tomax(d, son->d);
						w += son->w;
						if (i > 2)add('*');
					}
				}
				negative = 1;
				add('-');
			}else if (s->a[0]->isnum() && s->a[0]->v < 0) {
				negative = 1;
				add('-');
				Type = '*';
				*s->a[0] *= -1;
				FOO(i, s->a) {
					Exp* son = new Exp;
					son->Create(s->a[i], this, 1,0);
					tomax(u, son->u);
					tomax(d, son->d);
					w += son->w;
					if (i)add('*');
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
					if (i)add('*');
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
			add('^');
			if (b == 2)Add_brackets();
			break;
		}
		case '0': {
			Type = '0';
			if (!b && s->v.t == '0' && s->v.v < 0) {
				negative = 1;
				add('-');
				text = "-" + s->v.getstr();
			}
			else text = s->v.getstr();
			font(text, level, u, d, w);
			break;
		}
		case '#': {
			Type = '#';
			add('#');
			break;
		}
		}
	}
	void reConstruct() {
		reConstruct(0);
	}
	void reConstruct(bool l) {
		if (f) level = f->level + l;
		else level = 0;
		u = d = w = 0;
		if (negative) add('-');
		FOO(i, a)a[i]->reConstruct(Type == '/' || (Type == '^' && i == 1));
		switch (Type) {
		case '/': {
			u = a[0]->Height();
			d = a[1]->Height();
			w = max(a[0]->Width(), a[1]->Width());
			add('/');
			break;
		}
		case '+': {
			FOO(i, a) {
				w += a[i]->Width();
				tomax(u, a[i]->u);
				tomax(d, a[i]->d);
				if (i && !a[i]->negative)add('+');
			}
			break;
		}
		case '*': {
			FOO(i, a) {
				w += a[i]->Width();
				tomax(u, a[i]->u);
				tomax(d, a[i]->d);
				if (a[i]->negative)error("oops6");
				if (i)add('*');
			}
			break;
		}
		case '^': {
			u = a[0]->u + a[1]->Height();
			d = a[0]->d;
			w += a[0]->w + a[1]->w;
			add('^');
			break;
		}
		case '0': {
			add(text);
			break;
		}
		case '(': {
			u = a[0]->u;
			d = a[0]->d;
			w+= a[0]->w;
			add('(');
			break;
		}
		case '#': {
			add('#');
			break;
		}
		}
	}
	void Show() {
		cleardevice();//
		reConstruct();
		Show(left, top);
	}
	void Show(int Left, int Top){
		setlinecolor(WHITE);//
		rectangle(left-1, top-1, left + w, top + Height());//
		left = Left, top = Top;
		int W=w;
		int mid = top + u;
		int cur = left;
		if (negative) {
			font.Show('-', cur, mid - font.U[1][level], font.W[1][level], font.H[1][level]);
			cur += font.W[1][level];
			W -= font.W[1][level];
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
					font.Show('+', cur, mid - font.U[1][level], font.W[1][level], font.H[1][level]);
					cur += font.W[1][level];
				}
				a[i]->Show(cur, mid - a[i]->u);
				cur += a[i]->w;
			}
			break;
		}
		case '*': {
			FOO(i, a) {
				if (i) {
					font.Show('*', cur, mid - font.U[2][level], font.W[2][level], font.H[2][level]);
					cur += font.W[2][level];
				}
				a[i]->Show(cur, mid - a[i]->u);
				cur += a[i]->w;
			}
			break;
		}
		case '^': {
			a[0]->Show(cur, mid - a[0]->u);
			a[1]->Show(cur + a[0]->w + font.W[3][level], mid - a[0]->u - a[1]->Height() - font.UP[3][level]);
			break;
		}
		case '0': {
			font.Show(text, level, cur, top);
			break;
		}
		case '#': {
			printf("{#}"); break;
			setlinecolor(GREEN);
			rectangle(cur, top, cur + w - 1, top + Height() - 1);
			break;
		}
		case '(': {
			font.Show('(', cur, top, font.W[5][level], Height());
			font.Show(')', cur + W - font.W[5][level], top, font.W[5][level], Height());
			a[0]->Show(cur + font.W[5][level], top);
			break;
		}
		}
	}
	int Height()const { return u + d; }
	int Width()const { return w; }
	int size()const { return a.size(); }
	Exp* Head() {return a.empty() || negative || Type == '/' || Type == '^' ||Type=='(' ? this : a[0]->Head(); }
	Exp* End() { return a.empty() || Type == '/' || Type == '^' ||Type=='(' ? this : a[a.size()-1]->End(); }
	bool Head(int h_e) { return !h_e; }
	bool End(int h_e) { return Type == '0' ? h_e == text.length() : h_e; }
	void getEnd(int& h_e) {
		h_e = getEnd();
	}
	int getEnd() {
		if (Type == '#')return 0;
		if (Type == '0')return text.length();
		return 1;
	}
	int getSon() {
		if (!f) {
			error("oops4");
			return -1;
		}
		for (int i = 0; i < f->a.size(); i++)if (f->a[i] == this)return i;
		error("oops5");
		return -1;
	}
	Exp* Former(int& h_e) {
		if (h_e && Type == '0')return h_e--,this;
		if (!h_e) {
			if (f) {
				int son = getSon();
				if (son)return f->a[son - 1]->getEnd(h_e), f->a[son - 1]->End();
				if (negative||f->Type=='/'||f->Type=='(')return h_e = 0, f;
				if (f->Type == '^')error("oops3");
				return f->Former(h_e);
			}return this;
		}
		if (Type == '/' || Type == '^') {
			a[1]->getEnd(h_e);
			return a[1]->End();
		}
		else if (Type == '(') {
			a[0]->getEnd(h_e);
			return a[0]->End();
		}
		error("oops7");
		return NULL;
	}
	Exp* Latter(int& h_e) {
		if (h_e < getEnd() && Type == '0')return h_e++, this;
		if (h_e == getEnd()) {
			if (f) {
				int son = getSon();
				if (son < f->a.size() - 1)return h_e = 0, f->a[son + 1]->Head();
				if (f->Type == '/' || f->Type == '^' || f->Type == '(')return h_e = 1, f;
				return f->Latter(h_e);
			}return this;
		}
		return h_e = 0, a[0]->Head();
	}
	Exp(Exp* fa, int l, bool n) {
		f = fa;
		level = l;
		Type = '#';
		text = "";
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
			*nw = Val(text);
			break;
		}
		case '#': {
			flag = 1;
			setlinecolor(RED);
			rectangle(left, top, left + w-1, top + Height()-1);
			break;
		}
		case '(': {
			nw = a[0]->Calc();
			break;
		}
		}
		if (flag) {
			delete nw;
			return NULL;
		}
		if (negative)*nw = -*nw;
		return nw;
	}
	bool Check(int x, int y,Exp*& pos,int& h_e) {
		if (x < left || y < top || x >= left + w || y >= top + Height())return 0;
		int W = w;
		int mid = top + u;
		int cur = left;
		if (negative) {
			if (x >= cur && x < cur + font.W[1][level] && y >= mid - font.U[1][level] && y < mid + font.D[1][level]) {
				if (x < cur + font.W[1][level] / 2) {
					pos = this;
				}
				else {
					if(a.empty())error("oops2");
					pos = a[0];
				}
				h_e = 0;
				return 1;
			}
			cur += font.W[1][level];
			W -= font.W[1][level];
		}
		switch (Type) {
		case '/': {
			if (a[0]->Check(cur + (W - a[0]->w) / 2, top, pos, h_e))return 1;
			if (a[1]->Check(cur + (W - a[1]->w) / 2, mid + font.D[0][level], pos, h_e))return 1;
			if (y >= mid - font.U[0][level] && y < mid + font.D[0][level]) {
				if (x >= cur && x < cur + W / 2) {
					pos = this;
					h_e = 0;
					return 1;
				}
				else if (x >= cur + W / 2 && x < cur + W) {
					pos = this;
					h_e = 1;
					return 1;
				}
			}
			break;
		}
		case '+': {
			FOO(i, a) {
				if (x < cur)return 0;
				if (i && !a[i]->negative) {
					if (x >= cur && x < cur + font.W[1][level] && y >= mid - font.U[1][level] && y < mid + font.D[1][level]) {
						if (x < cur + font.W[1][level] / 2) {
							pos = a[i - 1]->End();
							h_e = 1;
						}
						else {
							pos = a[i]->Head();
							h_e = 0;
						}
						return 1;
					}
					cur += font.W[1][level];
				}
				if (a[i]->Check(cur, mid - a[i]->u, pos, h_e))return 1;
				cur += a[i]->w;
			}
			break;
		}
		case '*': {
			FOO(i, a) {
				if (x < cur)return 0;
				if (i) {
					if (x >= cur && x < cur + font.W[2][level] && y >= mid - font.U[2][level] && y < mid + font.D[2][level]) {
						if (x < cur + font.W[2][level] / 2) {
							pos = a[i - 1]->End();
							h_e = 1;
						}
						else {
							pos = a[i]->Head();
							h_e = 0;
						}
						return 1;
					}
					cur += font.W[2][level];
				}
				if (a[i]->Check(cur, mid - a[i]->u, pos, h_e))return 1;
				cur += a[i]->w;
			}
			break;
		}
		case '^': {
			if (a[0]->Check(cur, mid - a[0]->u, pos, h_e)) {
				if (!h_e&&pos==a[0]) pos = this;
				return 1;
			}
			if (a[1]->Check(cur + a[0]->w + font.W[3][level], mid - a[0]->u - a[1]->Height() - font.UP[3][level], pos, h_e))return 1;
			if(x>=cur&&x<cur+w&&y>=top&&y<top+Height()){
				pos=this;
				h_e=x>=cur+w/2;
				return 1;
			}
			break;
		}
		case '0': {
			LOGFONT old;
			gettextstyle(&old);
			LOGFONT* now = new LOGFONT;
			*now = old;
			now->lfHeight = font.H[4][level];
			now->lfWidth = font.W[4][level];
			settextstyle(now);
			int tmpW=textwidth(text.c_str()), tmpH=textheight(text.c_str());
			int tmp= textwidth("#");
			settextstyle(&old);
			if (x >= cur && x < cur + tmpW && y >= top && y < top + tmpH) {
				pos = this;
				h_e=0;
				while(x>=cur+tmp)cur+=tmp,h_e++;
				if(x>=cur+tmp/2)h_e++;
				return 1;
			}
			break;
		}
		case '#': {
			if (x >= cur && x < cur + W && y >= top && y < top + Height()) {
				pos = this;
				h_e = 0;
				return 1;
			}
			break;
		}
		case '(': {
			if (x>=cur&&x<cur+W&&y >= top && y < top + Height()) {
				if (x < cur + font.W[5][level] / 2) {
					pos = this;
					h_e = 0;
				}
				else if (x < cur + font.W[5][level]) {
					pos = a[0]->Head();
					h_e = 0;
				}
				else if (x < cur + W - (font.W[5][level] + 1) / 2) {
					pos = a[0]->End();
					h_e = 1;
				}
				else {
					pos = this;
					h_e = 1;
				}return 1;
			}
		}
		}return 0;
	}
	bool Check(Exp*& pos,int& h_e,int x, int y) {
		if (Check(x, y, pos, h_e)) return 1;
		if (y >= top && y < top + Height()) {
			if (x < left) {
				pos = Head();
				h_e = 0;
			}
			else if (x >= left + w) {
				pos = End();
				h_e = 1;
			}
			return 1;
		}return 0;
	}
	void drawcur(int h_e){
		setlinecolor(WHITE);
		int neg_len = negative * font.W[1][level];
		if(Type=='0'){
			LOGFONT old;
			gettextstyle(&old);
			LOGFONT* now = new LOGFONT;
			*now = old;
			now->lfHeight = font.H[4][level];
			now->lfWidth = font.W[4][level];
			settextstyle(now);
			int len = textwidth("#");
			settextstyle(&old);
			if (!h_e) line(left + neg_len+2, top + 2, left + neg_len + 2, top + Height() - 3);
			else if (h_e == text.length())line(left + w - 3, top + 2, left + w - 3, top + Height() - 3);
			else line(left + neg_len +h_e*len,top+2,left + neg_len +h_e*len,top+Height()-3);
		}else if(h_e)line(left+w-3,top+2,left+w-3,top+Height()-3);
		else line(left + neg_len +2,top+2,left + neg_len +2,top+Height()-1);
	}
	void hidecur(int h_e){
		setlinecolor(BLACK);
		int neg_len = negative * font.W[1][level];
		if(Type=='0'){
			LOGFONT old;
			gettextstyle(&old);
			LOGFONT* now = new LOGFONT;
			*now = old;
			now->lfHeight = font.H[4][level];
			now->lfWidth = font.W[4][level];
			settextstyle(now);
			int len = textwidth("#");
			settextstyle(&old);
			if (!h_e) line(left + neg_len + 2, top + 2, left + neg_len + 2, top + Height() - 3);
			else if (h_e == text.length())line(left + w - 3, top + 2, left + w - 3, top + Height() - 3);
			else line(left + neg_len + h_e * len, top + 2, left + neg_len + h_e * len, top + Height() - 3);
		}
		else if (h_e)line(left + w - 3, top + 2, left + w - 3, top + Height() - 3);
		else line(left + neg_len + 2, top + 2, left + neg_len + 2, top + Height() - 1);
	}
	bool find(char c) {
		return text.find(c) != text.npos;
	}
	void del(int id) {
		if (id <= 0 || id > text.length())error("oops1");
		text.erase(id - 1, 1);
		getstr(text);
	}
	Exp& operator=(const Exp& _) {
		f = _.f;
		FOO(i, _.a)push_back(_.a[i]);
		Type = _.Type;
		negative = _.negative;
		left = _.left;
		top = _.top;
		text = _.text;
		return *this;
	}
};
void Show(Expression* p, int left, int top) {
	Exp res(p);
	res.Show(left, top);
}
void Show(Expression& p, int left, int top) {
	Exp res(p);
	res.Show(left, top);
}
void Work() {
	initgraph(1440, 640);
	//setbkmode(TRANSPARENT);
	Exp* exp= new Exp(50,50);
	Exp* posCur=exp;
	int h_e = 0;
	EasyButton OK(200,300,500,350,"OK");
	bool binput=1;
	char lastch=0;
	while(binput){
		ExMessage msg;
		bool f1, f2;
		while(f1=f2=0,binput&&((f1=peekmessage(&msg, EM_MOUSE|EM_CHAR,false))||(f2=_kbhit()))){
			if (f1) {
				if (msg.message == WM_LBUTTONDOWN) {
					if (OK.Check(msg.x, msg.y)) {
						Expression* ans = exp->Calc();
						if (ans) Show(ans, 50, 250);
						binput = 0;
					}
					else if (exp->Check(posCur, h_e, msg.x, msg.y));
				}
				else if (msg.message == WM_CHAR) {
					char ch = msg.ch;
					switch (ch) {
					case '/': case -83: {
						if (lastch == -83 && ch == -83)break;
						Exp* nw = new Exp, * newCur = new Exp;
						if (h_e < posCur->getEnd() && h_e) {
							nw->getstr(posCur->text.substr(0, h_e));
							newCur->getstr(posCur->text.substr(h_e, posCur->text.length() - h_e));
						}
						else {
							*nw = *posCur;
							nw->negative = 0;
						}
						posCur->Type = ch=='/'?'/':'^';
						posCur->a.clear();
						if (posCur->Type == '^' && nw->Type != '0' && nw->Type != '#'&&nw->Type!='(')nw->Add_brackets();
						if (h_e) {
							posCur->push_back(nw);
							posCur->push_back(newCur);
						}
						else {
							posCur->push_back(newCur);
							posCur->push_back(nw);
						}
						if (posCur->f && posCur->f->Type == '^' && posCur->f->a[0] == posCur)
							posCur->Add_brackets();
						posCur = newCur;
						h_e = 0;
						break;
					}
					case '+': {
						Exp* newCur = new Exp;
						Exp* fa;
						while (fa = posCur->f, fa&&fa->Type == '*'&& posCur->End(h_e)&& posCur->getSon() == fa->a.size() - 1) 
							posCur = fa;
						while (fa = posCur->f, fa&& fa->Type == '*' &&!h_e &&!posCur->getSon())
							posCur = fa;
						if (fa && fa->Type == '+') {
							int son = posCur->getSon();
							if (son < 0)error("oops8");
							if (h_e == posCur->getEnd()) fa->insert(fa->a.begin() + son + 1, newCur);
							else if (h_e) {
								newCur->getstr(posCur->text.substr(h_e, posCur->text.length() - h_e));
								posCur->text = posCur->text.substr(0, h_e);
								fa->insert(fa->a.begin() + son + 1, newCur);
							}
							else {
								fa->insert(fa->a.begin() + son, newCur);
								newCur->negative = posCur->negative;
								posCur->negative = 0;
							}
						}
						else {
							Exp* nw = new Exp;
							if (h_e && h_e < posCur->getEnd()) {
								nw->getstr(posCur->text.substr(0, h_e));
								newCur->getstr(posCur->text.substr(h_e, posCur->text.length() - h_e));
							}
							else *nw = *posCur;
							posCur->Type = '+';
							posCur->a.clear();
							if (h_e) {
								nw->negative = posCur->negative;
								newCur->negative = 0;
								posCur->push_back(nw);
								posCur->push_back(newCur);
							}
							else {
								nw->negative = 0;
								newCur->negative = posCur->negative;
								posCur->push_back(newCur);
								posCur->push_back(nw);
							}
							posCur->negative = 0;
							if (fa && (fa->Type == '*' || (fa->Type == '^' && fa->a[0] == posCur)))
								posCur->Add_brackets();
						}
						posCur = newCur;
						h_e = 0;
						break;
					}
					case '-': {
						Exp* newCur = new Exp;
						Exp* fa;
						while (fa = posCur->f, fa&& fa->Type == '*' && posCur->End(h_e) && posCur->getSon() == fa->a.size() - 1) 
							posCur = fa;
						while (fa = posCur->f, fa&& fa->Type == '*' && !h_e && !posCur->getSon())
							posCur = fa;
						if (!h_e && (!fa || fa->a[0] == posCur)) {
							*newCur = *posCur;
							posCur->Type = '+';
							newCur->negative = 1;
							posCur->a.clear();
							posCur->push_back(newCur);
						}
						else if (fa && fa->Type == '+') {
							int son = posCur->getSon();
							if (son < 0)error("oops9");
							if (h_e == posCur->getEnd()) {
								newCur->negative = 1;
								fa->insert(fa->a.begin() + son + 1, newCur);
							}
							else if (h_e) {
								newCur->getstr(posCur->text.substr(h_e, posCur->text.length() - h_e));
								newCur->negative = 1;
								posCur->text = posCur->text.substr(0, h_e);
								fa->insert(fa->a.begin() + son + 1, newCur);
							}
							else {
								fa->insert(fa->a.begin() + son, newCur);
								newCur->negative = posCur->negative;
								posCur->negative = 1;
							}
						}
						else {
							Exp* nw = new Exp;
							if (h_e && h_e < posCur->getEnd()) {
								nw->getstr(posCur->text.substr(0, h_e));
								newCur->getstr(posCur->text.substr(h_e, posCur->text.length() - h_e));
							}
							else *nw = *posCur;
							posCur->Type = '+';
							posCur->a.clear();
							if (h_e) {
								nw->negative = posCur->negative;
								newCur->negative = 1;
								posCur->push_back(nw);
								posCur->push_back(newCur);
							}
							else {
								nw->negative = 1;
								newCur->negative = posCur->negative;
								posCur->push_back(newCur);
								posCur->push_back(nw);
							}
							posCur->negative = 0;
							if (fa && (fa->Type == '*' || (fa->Type == '^' && fa->a[0] == posCur)))
								posCur->Add_brackets();
						}
						posCur = newCur;
						h_e = 0;
						break;
					}
					case '*': {
						Exp* newCur = new Exp;
						Exp* fa = posCur->f;
						if (fa && fa->Type == '*') {
							int son = posCur->getSon();
							if (son < 0)error("oops10");
							if (h_e == posCur->getEnd())fa->insert(fa->a.begin() + son + 1, newCur);
							else if (h_e) {
								newCur->getstr(posCur->text.substr(h_e, posCur->text.length() - h_e));
								posCur->text = posCur->text.substr(0, h_e);
								fa->insert(fa->a.begin() + son + 1, newCur);
							}
							else fa->insert(fa->a.begin() + son, newCur);
						}
						else {
							Exp* nw = new Exp;
							if (h_e && h_e < posCur->getEnd()) {
								nw->getstr(posCur->text.substr(0, h_e));
								newCur->getstr(posCur->text.substr(h_e, posCur->text.length() - h_e));
							}
							else *nw = *posCur;
							posCur->Type = '*';
							posCur->a.clear();
							if (h_e) {
								posCur->push_back(nw);
								posCur->push_back(newCur);
							}
							else {
								posCur->push_back(newCur);
								posCur->push_back(nw);
							}
							if (fa && fa->Type == '^' && fa->a[0] == posCur)
								posCur->Add_brackets();
						}
						posCur = newCur;
						h_e = 0;
						break;
					}
					case -88: {//(
						if (!h_e) {
							while (posCur->Type == '^')posCur = posCur->a[0];
							Exp* nw = new Exp;
							*nw = *posCur;
							posCur->a.clear();
							posCur->Type = '(';
							posCur->push_back(nw);
							posCur->negative = 0;
							posCur = nw;
						}
						else if (h_e == posCur->getEnd()) {
							Exp* braCur = new Exp, * newCur = new Exp;
							braCur->Type = '(';
							braCur->push_back(newCur);
							Exp* fa = posCur->f;
							if (fa && fa->Type == '*') {
								int son = posCur->getSon();
								if (son < 0)error("oops11");
								fa->insert(fa->a.begin() + son + 1, braCur);
							}
							else {
								Exp* nw = new Exp;
								*nw = *posCur;
								posCur->Type = '*';
								posCur->a.clear();
								posCur->push_back(nw);
								posCur->push_back(braCur);
								if (fa && fa->Type == '^' && fa->a[0] == posCur)
									posCur->Add_brackets();
							}
							posCur = newCur;
							h_e = 0;
							break;
						}
						else {
							Exp* braCur = new Exp, * newCur = new Exp;
							braCur->Type = '(';
							braCur->push_back(newCur);
							newCur->getstr(posCur->text.substr(h_e, posCur->text.length() - h_e));
							posCur->text = posCur->text.substr(0, h_e);
							Exp* fa = posCur->f;
							if (fa && fa->Type == '*') {
								int son = posCur->getSon();
								if (son < 0)error("oops19");
								fa->insert(fa->a.begin() + son + 1, braCur);
							}
							else {
								Exp* nw = new Exp;
								*nw = *posCur;
								posCur->Type = '*';
								posCur->a.clear();
								posCur->push_back(nw);
								posCur->push_back(braCur);
								if (fa && fa->Type == '^' && fa->a[0] == posCur)
									posCur->Add_brackets();
							}
							posCur = newCur;
							h_e = 0;
							break;
						}
						break;
					}
					case -87: {//)
						if (lastch == '(') {
							Exp* fa = posCur->f;
							Exp* ffa = fa->f;
							int son;
							if (ffa && (son = fa->getSon()) < ffa->a.size() - 1) {
								if (ffa->Type == '^') {
									Exp* nw = new Exp;
									*nw = *ffa;
									ffa->Type = '(';
									ffa->a.clear();
									ffa->push_back(nw);
									ffa->a[0] = posCur;
									delete posCur->f;
									posCur->f = ffa;
									posCur = ffa;
								}
								else if (ffa->Type != '/') {
									if (posCur->Type == ffa->Type);
									else if (ffa->Type == '+') {
										Exp* nw = new Exp;
										*nw = *posCur;
										posCur->Type = '+';
										posCur->a.clear();
										posCur->push_back(nw);
									}
									else if (posCur->Type == '+') {
										Exp* nw = new Exp, * braCur = new Exp;
										*nw = *posCur;
										braCur->Type = '(';
										braCur->push_back(nw);
										posCur->Type = '*';
										posCur->a.clear();
										posCur->push_back(braCur);
									}
									else {
										Exp* nw = new Exp;
										*nw = *posCur;
										posCur->Type = '*';
										posCur->a.clear();
										posCur->push_back(nw);
									}
									posCur->push_back(ffa->a[son + 1]);
									ffa->a.erase(ffa->a.begin() + son + 1);
								}
							}
						}
						break;
					}
					case '0':case '1':case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9': {
						if (posCur->Type=='+' && !h_e) {
							Exp* newCur = new Exp;
							posCur->insert(posCur->a.begin(), newCur);
							posCur = newCur;
							h_e = 0;
							/*
							Exp* fa = posCur->f;
							if (fa && fa->Type == '+')error("oops14");
							Exp* nw = new Exp;
							*nw = *posCur;
							posCur->Type = '+';
							posCur->negative = 0;
							posCur->a.clear();
							posCur->push_back(nw);
							posCur->push_back(newCur);
							if (fa && (fa->Type == '*' || (fa->Type == '^' && fa->a[0] == posCur)))
								error("oops15");
								*/
						}
						else {
							switch (posCur->Type) {
							case '/': {
								Exp* newCur = new Exp;
								Exp* fa = posCur->f;
								if (fa && fa->Type == '*') {
									int son = posCur->getSon();
									if (son < 0)error("oops17");
									if (h_e)fa->insert(fa->a.begin() + son + 1, newCur);
									else fa->insert(fa->a.begin() + son, newCur);
								}
								else {
									Exp* nw = new Exp;
									*nw = *posCur;
									posCur->Type = '*';
									posCur->negative = 0;
									posCur->a.clear();
									if (h_e) {
										posCur->push_back(nw);
										posCur->push_back(newCur);
									}
									else {
										posCur->push_back(newCur);
										posCur->push_back(nw);
									}
									if (fa && fa->Type == '^' && fa->a[0] == posCur)
										posCur->Add_brackets();
								}
								posCur = newCur;
								h_e = 0;
								break;
							}
							case '^': {
								if (!h_e && (posCur->a[0]->Type == '0' || posCur->a[0]->Type == '#')) {
									posCur->a[0]->text = ch + posCur->a[0]->text;
									posCur->a[0]->Type = '0';
									posCur = posCur->a[0];
									h_e = 1;
								}
								else {
									Exp* newCur = new Exp;
									Exp* fa = posCur->f;
									if (fa && fa->Type == '*') {
										int son = posCur->getSon();
										if (son < 0)error("oops18");
										if (h_e)fa->insert(fa->a.begin() + son + 1, newCur);
										else fa->insert(fa->a.begin() + son, newCur);
									}
									else {
										Exp* nw = new Exp;
										*nw = *posCur;
										posCur->Type = '*';
										posCur->negative = 0;
										posCur->a.clear();
										if (h_e) {
											posCur->push_back(nw);
											posCur->push_back(newCur);
										}
										else {
											posCur->push_back(newCur);
											posCur->push_back(nw);
										}
										if (fa && fa->Type == '^' && fa->a[0] == posCur)
											posCur->Add_brackets();
									}
									posCur = newCur;
									h_e = 0;
								}
								break;
							}
							case '+':case '*':error("oops16");
							case '0': {
								string txt = posCur->text;
								posCur->getstr(txt.substr(0, h_e) + ch + txt.substr(h_e, txt.length() - h_e));
								h_e++;
								break;
							}
							case '(': {
								Exp* nw = new Exp, * newCur = new Exp;
								*nw = *posCur;
								nw->negative = 0;
								posCur->Type = '*';
								posCur->a.clear();
								if (h_e) {
									posCur->push_back(nw);
									posCur->push_back(newCur);
								}
								else {
									posCur->push_back(newCur);
									posCur->push_back(nw);
								}
								break;
							}
							}
						}
						if (posCur->Type == '#') {
							string txt = "";
							txt += ch;
							int neg = posCur->negative;
							posCur->getstr(txt);
							posCur->negative = neg;
							h_e++;
							break;
						}
						break;
					}
					case '.': {
						if (posCur->Type == '0' && !posCur->find('.')) {
							string txt = posCur->text;
							int neg = posCur->negative;
							posCur->getstr(txt.substr(0, h_e) + ch + txt.substr(h_e, txt.length() - h_e));
							posCur->negative = neg;
							h_e++;
						}
						break;
					}
					case 8: {//BackSpace
						while (h_e && (posCur->Type == '/' || posCur->Type == '^')) {
							posCur = posCur->a[1]->End();
							posCur->getEnd(h_e);
						}
						if (h_e) {
							switch (posCur->Type) {
							case '0': {
								posCur->del(h_e);
								h_e--;
								break;
							}
							case '(': {
								Exp* newCur = posCur->a[0];
								newCur->f = posCur->f;
								*posCur = *newCur;
								posCur = posCur->End();
								posCur->getEnd(h_e);
								break;
							}
							default:error("oops12");
							}
						}
						else {
							Exp* fa;
							while (fa = posCur->f, fa&& fa->Type!='('&&fa->a[0] == posCur && !posCur->negative)posCur = fa;
							if (fa) {
								if (fa->a[0] != posCur) {
									int son = posCur->getSon();
									Exp* forCur = fa->a[son - 1]->End();
									if (forCur->Type == '#' || posCur->Type == '#') {
										forCur->getEnd(h_e);
										forCur->text += posCur->text;
										delete posCur;
										if (fa->a.size() == 1 && !fa->negative) {
											Exp* ffa = fa->f;
											*fa = *forCur;
											delete forCur;
											posCur = fa;
											posCur->f = ffa;
										}
										else posCur = forCur;
									}
									else if (forCur->Type == '0' && posCur->Type == '0') {
										h_e += forCur->text.length();
										forCur->text += posCur->text;
										delete posCur;
										if (fa->a.size() == 1 && !fa->negative) {
											Exp* ffa = fa->f;
											*fa = *forCur;
											delete forCur;
											posCur = fa;
											posCur->f = ffa;
										}
										else posCur = forCur;
									}
									else if (fa->Type != '*') {
										if (forCur->Type != '*') {
											Exp* newCur = new Exp;
											*newCur = *forCur;
											newCur->negative = 0;
											forCur->a.clear();
											forCur->Type = '*';
											forCur->push_back(newCur);
											forCur->push_back(posCur);
											output("here", 0, 0);
										}
										else if (posCur->Type == '*')
											FOO(i, posCur->a)forCur->push_back(posCur->a[i]);
										else forCur->push_back(posCur);
										forCur->getEnd(h_e);
										posCur = forCur;
									}
									else {
										forCur->getEnd(h_e);
										posCur = forCur;
									}

								}
								else if(posCur->negative) {
									posCur->negative = 0;
									posCur = posCur->Head();
								}
								else if (fa->Type == '(') {
									Exp* ffa = fa->f;
									if (fa->negative && posCur->negative)
										fa->Type = '+';
									else if (ffa) {
										if (ffa->Type == '*');
										else if(ffa->Type == '^' && !fa->getSon());
										else {
											int son = fa->getSon();
											ffa->a.erase(ffa->a.begin() + son);
											if (ffa->Type == '+'&&posCur->Type=='+') {
												FOO(i, posCur->a) {
													if (!i && fa->negative && posCur->a[0]->negative) {
														Exp* nw = new Exp;
														nw->Type = '+';
														nw->push_back(posCur->a[0]);
														nw->negative = 1;
														ffa->insert(ffa->a.begin() + son + i, nw);
													}else ffa->insert(ffa->a.begin() + son + i, posCur->a[i]);
												}
											}
											else ffa->insert(ffa->a.begin() + son, posCur);
										}
									}
									else {
									}
								}
							}
						}
						break;
					}
					}
					if (lastch == '(' && ch == ')');
					else if(ch!=-95)lastch = ch;
				}
				else f1 = 0;
				while (posCur->f && posCur->f->Type == '^' && posCur->f->a[0] == posCur && !h_e)
					posCur = posCur->f;
				peekmessage(NULL, EM_MOUSE | EM_CHAR);
			}else if(f2){
				char ch=_getch();
				if (ch != 32 && ch != -32) {
					f2 = 1;
					switch (ch) {
					case 83: {//Delete
						if (!h_e) {
							while (!h_e && (posCur->Type == '/' || posCur->Type == '^'))
								posCur = posCur->a[0]->Head();
							switch (posCur->Type) {
							case '0': {
								posCur->del(h_e + 1);
								break;
							}
							case '(': {
								Exp* newCur = posCur->a[0];
								newCur->f = posCur->f;
								*posCur = *newCur;
								posCur = posCur->Head();
								h_e = 0;
							}
							default:error("oops13");
							}
						}
						else {
							Exp* fa;
							while (fa = posCur->f, fa&&fa->Type!='('&& * (fa->a.end() - 1) == posCur)posCur = fa;
							if (fa) {
								int son = posCur->getSon();
								Exp* aftCur = fa->a[son + 1]->End();
								if (aftCur->Type == '#' || posCur->Type == '#') {
									posCur->text += aftCur->text;
									delete aftCur;
									if (fa->a.size() == 1 && !fa->negative) {
										Exp* ffa = fa->f;
										*fa = *posCur;
										delete posCur;
										posCur = fa;
										posCur->f = ffa;
									}
								}
								else if (aftCur->Type == '0' && posCur->Type == '0') {
									posCur->text += aftCur->text;
									delete aftCur;
									if (fa->a.size() == 1 && !fa->negative) {
										Exp* ffa = fa->f;
										*fa = *posCur;
										delete posCur;
										posCur = fa;
										posCur->f = ffa;
									}
								}
								else if (fa->Type != '*') {
									if (posCur->Type != '*') {
										Exp* newCur = new Exp;
										*newCur = *posCur;
										newCur->negative = 0;
										posCur->Type = '*';
										posCur->a.clear();
										posCur->push_back(newCur);
										posCur->push_back(aftCur);
									}
									else if (aftCur->Type == '*')
										FOO(i, aftCur->a) posCur->push_back(aftCur->a[i]);
									else posCur->push_back(aftCur);
									h_e = 0;
									posCur = aftCur;
								}
								else {
									h_e = 0;
									posCur = aftCur;
								}
							}
						}
						break;
					}
					case 75: {//Left Arrow
						posCur = posCur->Former(h_e);
						break;
					}
					case 72: {//Up Arrow
						Exp* Cur = posCur;
						while (Cur->f && !(Cur->f->Type == '/' && Cur == Cur->f->a[1])
								      && !(Cur->f->Type == '^' && Cur == Cur->f->a[0]))
							Cur = Cur->f;
						if (Cur->f) {
							if (Cur->f->Type == '/') {
								posCur = Cur->f->a[0]->End();
								posCur->getEnd(h_e);
							}
							else {
								posCur = Cur->f->a[1]->Head();
								h_e = 0;
							}
						}
						break;
					}
					case 77: {//Right Arrow
						while (!h_e && posCur->Type == '^')posCur = posCur->a[0];
						posCur = posCur->Latter(h_e);
						break;
					}
					case 80: {//Down Arrow
						Exp* Cur = posCur;
						while (Cur->f && !(Cur->f->Type == '/' && Cur == Cur->f->a[0])
						              && !(Cur->f->Type == '^' && Cur == Cur->f->a[1]))
							Cur = Cur->f;
						if (Cur->f) {
							if (Cur->f->Type == '/') {
								posCur = Cur->f->a[1]->Head();
								h_e = 0;
							}
							else {
								posCur = Cur->f->a[0]->Head();
								posCur->getEnd(h_e);
							}
						}
						break;
					}
					default:f2 = 0;
					}
				}
				else f2 = 0;
				while (posCur->f && posCur->f->Type == '^' && posCur->f->a[0] == posCur && !h_e)
					posCur = posCur->f;
			}
			if (f1 || f2) {
				exp->Show();
				OK.Show();
			}
		}
		bool counter = 0;
		do{
			
			counter ^= 1;
			if (counter)posCur->drawcur(h_e);
			else posCur->hidecur(h_e);
			Sleep(300);
			
		}while(!peekmessage(NULL,EM_MOUSE|EM_CHAR,false)&&!_kbhit());
		if(counter)posCur->hidecur(h_e);
	}
	Expression* ans=exp->Calc();
	Exp* res=new Exp(ans);
	res->Show();
}