/*@copyright Augusta*/
#include<bits/stdc++.h>
#include<iostream>
#include<time.h>
#define double long double
#define FOR(x,y,z) for(int x=y,x##_=(int)z;x<x##_;x++)
#define FON(x,y,z) for(int x=y,x##_=z;x<x##_;x=nxt[x])
#define FOS(x,y) for(int x=0,x##_=(int)y.length();x<x##_;x++)
#define FOO(x,y) for(int x=0,x##_=(int)y.size();x<x##_;x++)
#define DOO(x,y) for(int x=y.size()-1;~x;x--)
#define FO(x,y) for(int x=0,x##_=y;x<=x##_;x=x?(x<0?-(x-1):-x):1)
#define DOR(x,y,z) for(int x=z.size()-1,x##_=y;x>x##_;x--)
using namespace std;
void error(const string& s);
void error(const string& s,char c);
void error(const string& s,char c,char d);
namespace My{
	const double esp=1e-14;
	const clock_t MAX_t=400;
	template<class T>bool iszero(const T& x){return fabs(x)<esp;}
	template<class T>bool equ(const T& x,const int& y){return fabs(x-y)<esp;}
	template<class T>int beint(const T& x){
		if(equ(x,(int)x))return (int)x;
		if(equ(x,1+(int)x))return 1+(int)x;
		return (int)x-1;
	}
	bool isint(const double& x){return iszero(x-floor(x))||iszero(x-ceil(x));}
	double rand_double(){//[10,110]
		return (double)(rand()*rand()%1000000000+100000000)/10000000*(rand()%2?1:-1);
	}
	struct Const{
		map<char,double>mp;
		Const(){
			mp['E']=2.7182818284;
			mp['P']=3.1415926535;
			mp['x']=1.0757150757;
			mp['y']=1.7978507978;
			mp['z']=2.6971126971;
			mp['a']=1.9567129567;
			mp['b']=2.1749391749;
			mp['c']=1.1470551470;
		}
		double operator[](char c){return mp[c];}
	}Con;
	struct Val{
		double v;
		char t;
		Val(){v=0;t='0';}
		Val(int V){v=V;t='0';}
		Val(double V){v=V;t='0';}
		Val(char c){
			switch(t=c){
				case 'E':case 'P':case 'x':case 'y':case 'z':case 'a':case 'b':case 'c':{
					v=Con[t];
					break;
				}
			}
		}
		bool operator <(const Val &_)const{return v<_.v;}
		bool operator <(const double &_)const{return v<_;}
		bool operator <(const int &_)const{return v<_;}
		bool operator <=(const Val &_)const{return v<=_.v;}
		bool operator <=(const double &_)const{return v<=_;}
		bool operator <=(const int &_)const{return v<=_;}

		bool operator >(const Val &_)const{return v>_.v;}
		bool operator >(const double &_)const{return v>_;}
		bool operator >(const int &_)const{return v>_;}
		bool operator >=(const Val &_)const{return v>=_.v;}
		bool operator >=(const double &_)const{return v>=_;}
		bool operator >=(const int &_)const{return v>=_;}

		bool operator ==(const Val &_)const{return iszero(v-_.v);}
		bool operator ==(const double &_)const{return iszero(v-_);}
		bool operator ==(const int &_)const{return iszero(v-_);}

		bool operator !=(const Val &_)const{return !(*this==_);}
		bool operator !=(const double &_)const{return !(*this==_);}
		bool operator !=(const int &_)const{return !(*this==_);}

		Val operator -()const{return Val(-v);}
		Val operator +(const Val &_)const{return Val(v+_.v);}
		Val operator -(const Val &_)const{return Val(v-_.v);}
		Val operator *(const Val &_)const{return Val(v*_.v);}
		Val operator ^(const Val &_)const{return Val(pow(v,_.v));}
		Val operator ^(const int &_)const{return Val(pow(v,_));}
		Val operator /(const Val &_)const{
			if(iszero(_.v))error("divided by 0");
			return Val(v/_.v);
		}
		Val operator /(const int &_)const{
			if(iszero(_))error("divided by 0");
			return Val(v/_);
		}
		Val operator /(const double &_)const{
			if(iszero(_))error("divided by 0");
			return Val(v/_);
		}
		Val operator %(const Val &_)const{
			if(iszero(_.v))error("mod by 0");
			return Val(beint(v)%beint(_.v));
		}//????
		Val operator %(const int &_)const{
			if(iszero(_))error("mod by 0");
			return Val(beint(v)%_);
		}
		Val& operator +=(const Val &_){return *this=*this+_;}
		Val& operator -=(const Val &_){return *this=*this-_;}
		Val& operator *=(const Val &_){return *this=*this*_;}
		Val& operator /=(const Val &_){return *this=*this/_;}
		Val& operator /=(const int &_){return *this=*this/_;}
		Val& operator /=(const double &_){return *this=*this/_;}
		Val& operator %=(const Val &_){return *this=*this%_;}
		Val& operator %=(const int &_){return *this=*this%_;}
		Val& operator ^=(const Val &_){return *this=*this^_;}
		Val& operator ^=(const int &_){return *this=*this^_;}
		Val& operator =(const char &_){return *this=Val(_);}
		Val& operator =(const int &_){return *this=Val(_);}
		void operator()(const char &c,const Val &_){
			switch(c){
				case '+':v+=_.v;break;
				case '*':v*=_.v;break;
			}
			t='0';
		}
		void operator()(const char &c,const Val &x,const Val &y){
			switch(c){
				case '/':{
					if(iszero(y.v))error("divided by 0");
					v=x.v/y.v;
					break;
				}
				case '^':{
					if(iszero(x.v)&&iszero(y.v))error("0^0");
					if(x.v<0&&!isint(y.v))error("-^irrational");
					v=pow(x.v,y.v);
					break;
				}
			}
			t='0';
		} 
	};
	bool cmp(char x,char y){
		switch(x){
			case '/':x=0;break;
			case '+':x=1;break;
			case '*':x=2;break;
			case '^':x=3;break;
			case '0':x=4;break;
		}
		switch(y){
			case '/':y=0;break;
			case '+':y=1;break;
			case '*':y=2;break;
			case '^':y=3;break;
			case '0':y=4;break;
		}
		return x>y;
	}

	struct Bin{
		int operator[](const int& x)const{
			if(!x)error("bin");
			for(int i=0;;i++)if(x>>i&1)return i;
		}
		int operator()(const int& x)const{return x^(x&-x);}
	}bin;
	struct Prime{
		const int n=6e4;
		int p[60000];
		bool mark[60005];
		Prime(){
			for(int i=2;i<=n;i++)if(!mark[i]){
				for(int j=i+i;j<=n;j++)mark[j]=1;
				p[++p[0]]=i;
			}
		}
		bool operator()(int x,vector<pair<int,int> >& s)const{
			for(int i=1;i<=p[0]&&p[i]<=x/p[i];i++)if(x%p[i]==0){
				int t=0;
				while(x%p[i]==0){
					t++;
					x/=p[i];
				}
				s.push_back(make_pair(p[i],t));
			}
			if(x>1)s.push_back(make_pair(x,1));
			return s.size()>1;
		}
		void Enum(const vector<pair<int,int> >&q,int cur,int v,vector<int>& p)const{
			--cur;
			if(cur==-1){
				if(v^1)p.push_back(v);
				return;
			}
			Enum(q,cur,v,p);
			FOR(i,1,q[cur].second+1)
				Enum(q,cur,v*=q[cur].first,p);
		}
		void operator[](vector<int>& p)const{
			vector<pair<int,int> >q;
			(*this)(p[0],q);
			p.erase(p.begin(),p.end());
			Enum(q,q.size(),1,p);
			sort(p.begin(),p.end());
		}
	}Pri;
	struct Brackets{
		map<char,int>mp;
		Brackets(){
			mp['(']=mp[')']=0;
			mp['[']=mp[']']=1;
			mp['{']=mp['}']=2;
		}
		int operator()(const char& c){return mp[c];}
		char operator[](const char& c){return c+1+(c!='(');}
	}Bracket;
	struct node{
		//优先级：分式，加，乘，指数，数值
		char Type;
		vector<node*>a;//Check 地址与值
		Val v;
		int size()const{return a.size();}
		bool isnum()const{return Type=='0'&&v.t=='0';}
		bool empty(){return a.empty();}
		void Adjust(){//调整符号，往低优先级调整
			while(Type!='0'){
				if(Type=='/'&&*a[1]==1)*this=*a[0];
				else if(Type=='+'||Type=='*'){
					if(size()==0)Type='0';
					else if(size()==1)*this=*a[0];
					else return;
				}else if(Type=='^'&&*a[1]==1)*this=*a[0];
				else if(Type=='^'&&*a[0]==1)*this=node(1);
				else return;
			}
		}
		bool Negative(const node &x){
			if(x.v>=0)return 0;
			node nw=x;
			if(nw.Type=='+'){
				vector<pair<node,int> >s;
				vector<node>t1,t2;
				vector<double>V1,V2;
				t2.push_back(node(1));
				V2.push_back(1.0);
				nw.Split(s);
				nw.Unique(s,t1,V1);
				nw.Factorization(t1,V1,t2,V2);
			}else if(nw.Type!='*')nw=node('*',nw);
			return nw.a[0]->Type=='0'&&nw.a[0]->v<0;
		}
		bool Negative(node* x){return Negative(*x);}
		bool Check(const vector<double>& V,vector<int>& X,int cur,double v,const double& res,int& mx,const vector<int>& p){
			--cur;
			DOO(i,p)if(iszero(pow(v,p[i])-res)&&!(p[i]%2==0&&v<0)){
				while(~cur)X[cur--]=0;
				return mx=-p[i],1;
			}
			if(cur<0)return 0;
			if(!cur){
				DOO(i,p){
					double j;
					if(p[i]%2==0&&isint(j=pow(res,1.0/p[i])-v)){
						X[cur]=beint(j);
						return mx=-p[i],1;
					}
					if(isint(j=-pow(res,1.0/p[i])-v)){
						X[cur]=beint(j);
						return mx=-p[i],1;
					}
				}
				return 0;
			}
			FO(i,mx){
				X[cur]=i;
				if(Check(V,X,cur,v+V[cur]*i,res,mx,p))
					return 1;
			}return 0;
		}
		bool Check(double v1,double v2){return v1>=0||v2>=0;}
		void Factorization(const vector<node>& t,const vector<double>& V,const vector<int>& p){
			if(Type=='0'||t.empty())return *this=node('*',*this),void();
			clock_t ti=clock();
			vector<int>X(t.size());
			int mx,n=t.size();
			int mt=MAX_t/t.size();
			for(mx=1;clock()-ti<=mt&&!Check(V,X,n,0,v.v,mx,p);mx++);
			if(mx<0){
				node x(t,X);
				*this=node('^');
				Push_back(x,-mx);
			}
		}
		bool Check(const vector<double>& V1,const vector<double>& V2,vector<int>& X,vector<int>& Y,int cur,double v1,double v2,const double& res,int& mx){
			--cur;
			if(iszero(v1*v2-res)&&Check(v1,v2)&&!equ(v2,1)&&Check(X,Y)){
				while(~cur){
					X[cur]=Y[cur]=0;
					cur--;
				}return mx=-1,1;
			}
			if(cur<0)return 0;
			if(!cur){
				FO(i,mx)if(!iszero(v1+i)){
					double j=res/(v1+i)-v2;
					if(isint(j)&&!equ(v2,1-beint(j))&&Check(v1+i,v2+j)){
						X[cur]=i,Y[cur]=beint(j);
						if(Check(X,Y))return mx=-1,1;
					}
				}return 0;
			}
			if(cur<V1.size()&&cur<V2.size()){
				FO(i,mx)FO(j,mx){
					X[cur]=i,Y[cur]=j;
					if(Check(V1,V2,X,Y,cur,v1+V1[cur]*i,v2+V2[cur]*j,res,mx))
						return 1;
				}
			}else if(cur<V1.size()){
				FO(i,mx){
					X[cur]=i,Y[cur]=0;
					if(Check(V1,V2,X,Y,cur,v1+V1[cur]*i,v2,res,mx))
						return 1;
				}
			}else{
				FO(j,mx){
					X[cur]=0,Y[cur]=j;
					if(Check(V1,V2,X,Y,cur,v1,v2+V2[cur]*j,res,mx))
						return 1;
				}
			}
			return 0;
		}
		//修改为node*
		void Factorization(const vector<node>& t1,const vector<double>& V1,const vector<node>& t2,const vector<double>& V2){
			if(Type=='0'||t2.empty()||t1.empty())return *this=node('*',*this),void();
			clock_t ti=clock();
			int mx_sz=max(t1.size(),t2.size());
			vector<int>X(mx_sz),Y(mx_sz);
			int mx;
			int mt=MAX_t/mx_sz;
			for(mx=1;clock()-ti<=mt&&!Check(V1,V2,X,Y,mx_sz,0,0,v.v,mx);mx++);
			if(mx==-1){
				node x(t1,X),y(t2,Y);
				x.Factorization(t1,V1,t2,V2);
				y.Factorization(t2,V2);
				*this=node('*');
				FOO(i,x.a)Insert(*x.a[i]);
				FOO(i,y.a)Insert(*y.a[i]);
			}
			if(Type!='*')*this=node('*',*this);
		}
		bool Check(const vector<int>& X,const vector<int>& Y){
			if(X[0]<0&&Y[0]<0)return 0;
			if(X[0]<0&&!Y[0])return 0;
			if(!X[0]&&Y[0]<0)return 0;
			if(X[0]<0&&Y[0]>0)return 0;
			bool F=0;
			int s=0,t=0;
			FOR(i,1,X.size()){
				if(X[i]>0||Y[i]>0)F=1;
				s+=X[i]!=0;
				t+=Y[i]!=0;
			}
			if(s==X.size()-1&&t)return 0;
			if(t==X.size()-1&&s)return 0;
			if(!X[0]&&!Y[0])return F;
			return 1;
		}
		bool Check(const vector<double>& V,vector<int>& X,vector<int>& Y,int cur,double v1,double v2,const double& res,int& mx){
			--cur;
			if(iszero(v1*v2-res)&&Check(v1,v2)&&!equ(v1,1)&&!equ(v2,1)&&Check(X,Y)){
				while(~cur){
					X[cur]=Y[cur]=0;
					cur--;
				}return mx=-1,1;
			}
			if(cur<0)return 0;
			if(!cur){
				FO(i,mx)if(!iszero(v1+i)&&!equ(v1,1-i)){
					double j=res/(v1+i)-v2;
					if(isint(j)&&!equ(v2,1-beint(j))&&Check(v1+i,v2+j)){
						X[cur]=i,Y[cur]=beint(j);
						if(Check(X,Y))return mx=-1,1;
					}
				}return 0;
			}
			FO(i,mx)FO(j,mx){X[cur]=i,Y[cur]=j;
				if(Check(V,X,Y,cur,v1+V[cur]*i,v2+V[cur]*j,res,mx))
					return 1;
			}
			return 0;
		}
		//修改为node*
		void Factorization(const vector<node>& t,const vector<double>& V){
			if(Type=='0'||t.empty())return *this=node('*',*this),void();
			clock_t ti=clock();
			vector<int>X(t.size()),Y(t.size());
			int mx,n=t.size();
			int mt=MAX_t/t.size();
			for(mx=1;clock()-ti<=mt&&!Check(V,X,Y,n,0,0,v.v,mx);mx++);
			if(mx==-1){
				node x(t,X),y(t,Y);
				x.Factorization(t,V);
				y.Factorization(t,V);
				*this=node('*');
				FOO(i,x.a)Insert(*x.a[i]);
				FOO(i,y.a)Insert(*y.a[i]);
			}
			if(Type!='*')*this=node('*',*this);
		}
		node(const vector<node>& t,const vector<int>& V){
			Type='+';
			FOO(i,t)if(V[i])Insert(t[i]*V[i]);
			Adjust();
			if(Type=='0')*this=node('*',*this);
		}
		void Insert(vector<pair<node,int> >& s,const node& x){
			if(x.isnum()||x==0)return;
			if(x.Type=='^'&&x.a[0]->isnum()){
				vector<pair<int,int> >p;
				Pri(beint(x.a[0]->v.v),p);
				int F=(x.a[1]->Type=='/'&&x.a[1]->a[0]->isnum())?beint(x.a[1]->a[0]->v.v):1;
				int mx=(x.a[1]->Type=='/'&&x.a[1]->a[1]->isnum())?beint(x.a[1]->a[1]->v.v)-1:2e9;
				FOO(i,p)s.push_back(make_pair(node('^',p[i].first,*x.a[1]/F),min(F*p[i].second,mx)));
				return;
			}
			if(x.Type=='^'&&x.a[1]->isnum()){
				s.push_back(make_pair(*x.a[0],beint(x.a[1]->v.v)));
				return;
			}
			s.push_back(make_pair(x,1));
		}
		void Split(vector<pair<node,int> >& s){
			FOO(i,a){
				if(a[i]->Type=='*')FOO(j,a[i]->a)Insert(s,*(a[i]->a[j]));
				else Insert(s,*a[i]);
			}
		}
		void Enum(const vector<pair<node,int> >& s,vector<int>& e,vector<node>& t,int cur){
			--cur;
			if(cur==-1){
				node nw=1;
				FOO(i,s)nw*=s[i].first^e[i];
				t.push_back(nw);
				return;
			}
			FOR(i,0,s[cur].second+1){
				e[cur]=i;
				Enum(s,e,t,cur);
			}
		}
		void Unique(vector<pair<node,int> >& s,vector<node>& t,vector<double>& V);
		void Unique(vector<pair<node,int> >& s,vector<node>& t1,vector<double>& V1,vector<node>& t2,vector<double>& V2);
		void Factorization(int n){//置于外部的情况/原始乘法一定是不可继续拆分的
			if(n){
				vector<int>p;
				p.push_back(n);
				Pri[p];
				vector<pair<node,int> >s;
				vector<node>t;
				vector<double>V;
				Split(s);
				Unique(s,t,V);
				Factorization(t,V,p);
			}else{
				if(Type=='+'){
					vector<pair<node,int> >s;
					vector<node>t;
					vector<double>V;
					Split(s);
					Unique(s,t,V);
					Factorization(t,V);
				}else if(Type!='*')*this=node('*',*this);
			}
		}
		node Factorization(const node& t){
			node T=t;
			T.Factorization(0);
			return T;
		}
		void Factorization(node& p,node& q){
			if(p.isnum()&&q.isnum()){
				p=node('*',p);
				q=node('*',q);
			}else{
				vector<pair<node,int> >s1,s2;
				vector<node>t1,t2,t3;
				vector<double>V1,V2,V3;
				if(p.Type=='+')p.Split(s1);
				if(q.Type=='+')q.Split(s2);
				Unique(s1,t1,V1);
				Unique(s2,t2,V2,t3,V3);
				p.Factorization(t1,V1,t3,V3);
				q.Factorization(t2,V2,t3,V3);
			}
		}
		bool Radical(){return Type=='^'&&a[1]->Type=='/'&&a[1]->a[1]->isnum();}
		int count(){
			if(Type=='^')return Radical();
			if(Type=='+'||Type=='*'){
				int c=0;
				FOO(i,a)c+=a[i]->count();
				return c;
			}return 0;
		}
		bool Rationalization(node& p){
			int flag=0;
			FOO(i,a){
				flag=0;
				node A,B('+');
				if(a[i]->Radical()){
					A=*a[i];
					flag=a[i]->a[1]->a[1]->v.v;
				}else if(a[i]->Type=='*'){
					FOO(j,a[i]->a)if(a[i]->a[j]->Radical()){
						A=*a[i];
						flag=a[i]->a[j]->a[1]->a[1]->v.v;
						break;
					}
				}
				if(flag){
					FOO(j,a)if(j!=i)B.Insert(*a[j]);
					B.Adjust();
					B=-B;
					node nw=(A^flag)-(B^flag);
					if(nw.count()>=count())return 0;
					*this=nw;
					node D('+'),res=1;
					FOR(i,0,flag){
						D.Push_back(res);
						res*=A;
					}
					res=1;
					for(int j=flag-1;~j;j--,res*=B)*D.a[j]*=res;
					node C=0;
					FOO(i,D.a){
						if(D.a[i]->Type=='+')FOO(j,D.a[i]->a)
							C+=*D.a[i]->a[j];
						else C+=*D.a[i];
					}
					C.Abbreviation();
					p*=C;
					return Rationalization(p),1;
				}
			}return 0;
		}
		void Init(){
			Type='/';
			v=1;
			a.push_back(New(1));
			a.push_back(New(1));
		}
		int gcd_(int n,int m){
			return m?gcd_(m,n%m):n;
		}
		bool gcd(Val& x,Val& y){
			int X=x.v,Y=y.v;
			if(Y<0)X=-X,Y=-Y;
			int g=gcd_(abs(X),Y);
			if(g==1)return 0;
			x/=g;
			y/=g;
			return 1;
		}
		bool Abbre_free();
		void Abbre_after();
		void Abbreviation();
		int Extract(){
			if(Type=='*'){
				if(a[0]->isnum()){
					int p=a[0]->v.v;
					if(size()==2){
						p*=a[1]->Extract();
						*this=*a[1];
					}
					else{
						free(a[0]);
						FOR(i,1,size()){
							p*=a[i]->Extract();
							a[i-1]=a[i];
						}
						a.erase(a.end()-1);
					}return p;
				}else{
					int p=1;
					FOO(i,a)p*=a[i]->Extract();
					return p;
				}
			}
			if(Radical()&&a[0]->isnum()&&a[1]->a[0]->isnum()){
				int s=beint(a[1]->a[0]->v.v),t=beint(a[1]->a[1]->v.v);
				if(s>=t){
					*this=(*a[0])^node('/',node(s%t),t);
					return beint(pow(a[0]->v.v,s/t));
				}
			}
			if(isnum()){
				int tmp=v.v;
				return *this=1,tmp;
			}
			return 1;
		}
		bool operator |=(const node &_){//+合并
			if(Type=='/'||Type=='+'||_.Type=='/'||_.Type=='+')return 0;
			node x=*this,y=_;
			if(x==0)return *this=_,1;
			if(y==0)return 1;
			int p=x.Extract(),q=y.Extract();
			if(x==y)return *this=x*(p+q),1;
			return 0;
		}
		bool operator &=(const node &_){//*合并
			node x=*this,y=_;
			if(x==1)return *this=_,1;
			if(y==1)return 1;
			if(x.Type=='/'||x.Type=='+'||x.Type=='*')return 0;
			if(y.Type=='/'||y.Type=='+'||y.Type=='*')return 0;
			if(x.Type=='0'&&y.Type=='0'){
				if(x.isnum()&&y.isnum())return *this=node(beint(x.v.v*y.v.v)),1;
				if(x.v.t==y.v.t)return *this=node('^',x,node(2)),1;
				return 0;
			}
			if(x.Type=='0'&&y.Type=='^'){
				if(x==*y.a[0]){
					*y.a[1]+=node(1);
					y.v*=x.v;
					y.Abbreviation();
					if(cmp(y.Type,'*'))return *this=y,1;
					return 0;
				}return 0;
			}
			if(x.Type=='^'&&y.Type=='0'){
				if(*x.a[0]==y){
					*x.a[1]+=node(1);
					x.v*=y.v;
					x.Abbreviation();
					if(cmp(x.Type,'*'))return *this=x,1;
					return 0;
				}return 0;
			}
			if(*x.a[0]==*y.a[0]){
				*x.a[1]+=*y.a[1];
				x.v*=y.v;
				x.Abbreviation();
				if(cmp(x.Type,'*'))return *this=x,1;
				return 0;
			}
			if(*x.a[1]==*y.a[1]){
				node nw=*x.a[0]**y.a[0];
				if(nw.size()<=x.a[0]->size()&&nw.size()<=y.a[0]->size()&&x.a[0]->size()+y.a[0]->size())
					return *this=nw^*x.a[1],1;
			}
			return 0;
		}
		void Insert(const node &x){
			switch(Type){
				case '/':case '^':error("oops");
				case '+':{
					FOO(i,a)if(x<*a[i]){
						Push_back(*(a.end()-1));
						v-=(*(a.end()-1))->v;
						DOR(j,i,a)*a[j]=*a[j-1];
						a[i]=New(x);
						v+=x.v;
						return;
					}
					Push_back(x);
					break;
				}
				case '*':{
					if(size()==1&&*a[0]==1)return *this=node('*',x),void();
					FOO(i,a)if(x<*a[i]){
						Push_back(*(a.end()-1));
						DOR(j,i,a)*a[j]=*a[j-1];
						a[i]=New(x);
						v=v*x.v/(*(a.end()-1))->v;
						return;
					}
					Push_back(x);
					break;
				}
				default:error("Wrong Add");
			}

		}
		void Add_(const node &x){//按原符号添加元素，但保留符号
			switch(Type){
				case '/':case '^':error("oops");
				case '+':{
					if(x==0)return;
					FOO(i,a)if(*a[i]|=x){
						v+=x.v;
						Abbreviation();
						if(Type!='+')*this=node('+',*this);
						return;
					}
					Insert(x);
					break;
				}
				case '*':{
					if(size()&&*a[0]==0)return;
					if(size()==1&&*a[0]==1)return *this=node('*',x),void();
					if(x==0)return *this=node('*',0),void();
					if(x==1){
						if(empty())Push_back(x);
						return;
					}
					FOO(i,a)if(*a[i]&=x){
						v*=x.v;
						Abbreviation();
						if(Type!='*')*this=node('*',*this);
						return;
					}
					Insert(x);
					break;
				}
				default:error("Wrong Add");
			}
		}
		void Add(const node &x){//按原符号添加元素，可能变符号
			Add_(x);
			Adjust();//整理，调整符号
		}
		node* New(const node &x){
			node* nw=new node;
			*nw=x;
			return nw;
		}
		node* New(node* x){return New(*x);}
		node* New(const int& x){
			node* nw=new node(x);
			return nw;
		}
		void Push_back(const node& x){
			a.push_back(New(x));
			if((Type=='^'||Type=='/')&&size()==1)v=x.v;
			else if(Type=='^'&&x.Type=='/'&&x.a[0]->isnum()&&x.a[1]->isnum()&&v.v<0&&(int)x.a[1]->v.v%2){
				v.v=pow(pow(-v.v,x.a[0]->v.v),1/x.a[1]->v.v);
				if((int)x.a[0]->v.v%2)v.v=-v.v;
				v.t='0';
			}
			else v(Type,x.v);
		}
		void Push_back(node* x){
			a.push_back(New(x));
			if((Type=='^'||Type=='/')&&size()==1)v=x->v;
			else if(Type=='^'&&x->Type=='/'&&x->a[0]->isnum()&&x->a[1]->isnum()&&v.v<0&&(int)x->a[1]->v.v%2){
				v.v=pow(pow(-v.v,x->a[0]->v.v),1/x->a[1]->v.v);
				if((int)x->a[0]->v.v%2)v.v=-v.v;
				v.t='0';
			}
			else v(Type,x->v);
		}
		void Push_back(const int& x){
			a.push_back(New(x));
			if((Type=='^'||Type=='/')&&size()==1)v=x;
			else v(Type,(double)x);
		}
		void Push_back(const node& x,const node& y){
			a.push_back(New(x));
			a.push_back(New(y));
			if(Type=='^'&&y.Type=='/'&&y.a[0]->isnum()&&y.a[1]->isnum()&&x.v.v<0&&(int)y.a[1]->v.v%2){
				v.v=pow(pow(-x.v.v,y.a[0]->v.v),1/y.a[1]->v.v);
				if((int)y.a[0]->v.v%2)v.v=-v.v;
				v.t='0';
			}
			else v(Type,x.v,y.v);
		}
		node(){}
		node(char t){
			switch(t){
				case '/':case '+':case '^':case '0':{
					Type=t;
					break;
				}
				case '*':{
					Type=t;
					v=1;
					Push_back(1);
					break;
				}
				case '#':{
					Type=t;
					v.v=rand_double();
					break;
				}
				default:Type='0',v=t;
			}
		}
		node(Val x):Type('0'),v(x){}
		node(int x):Type('0'),v(Val(x)){}
		node(const node &x){*this=x;}
		node(char t,const vector<node*>&s){
			*this=node(t);
			FOO(i,s)Add_(*s[i]);
		}
		node(char t,const vector<node*>&s1,const vector<node*>s2){
			*this=node(t);
			FOO(i,s1)Add_(*s1[i]);
			FOO(i,s2)Add_(*s2[i]);
			Adjust();
		}
		node(char t,const node &x){
			Type=t;
			Push_back(x);
			v=x.v;
		}
		node(char t,const node &x,const node& y){
			*this=node(t);
			switch(t){
				case '/':case '^':{
					Push_back(x,y);
					Abbreviation();
					break;
				}
				case '+':case '*':{
					Add_(x);
					Add(y);
					break;
				}
				case '0':error("OOPS");
			}
		}
		node& operator=(const node &_){
			Type=_.Type;
			vector<node*>s;
			FOO(i,a)s.push_back(a[i]);
			a.clear();
			if(Type=='^'||Type=='/')FOO(i,_.a)Push_back(_.a[i]);
			else FOO(i,_.a)Insert(*_.a[i]);
			v=_.v;
			FOO(i,s)free(s[i]);
			return *this;
		}
		node& operator=(const int &_){
			Type='0';
			v=_;
			FOO(i,a)free(a[i]);
			a.clear();
			return *this;
		}
		~node(){FOO(i,a)free(a[i]);}
		bool operator <(const node &_)const{
			if(cmp(Type,_.Type))return 1;
			if(cmp(_.Type,Type))return 0;
			if(Type=='0'){
				if(isnum()^_.isnum())return isnum();
				return v<_.v;
			}
			FOR(i,0,min(size(),_.size())){
				if(*a[i]<*_.a[i])return 1;
				if(*_.a[i]<*a[i])return 0;
			}
			if(size()==_.size())return 0;
			return _.size();
		}
		node operator +(const node &_)const{
			if(cmp(Type,_.Type))return _+*this;
			if(Type=='/'&&_.Type=='/')return node('/',*a[0]**_.a[1]+*a[1]**_.a[0],*a[1]**_.a[1]);
			if(Type=='/')return node('/',*a[0]+*a[1]*_,*a[1]);
			if(Type=='+'&&_.Type=='+')return node('+',a,_.a);
			if(Type=='+'){
				node nw=*this;
				nw.Add(_);
				return nw;
			}
			node nw('+',*this);
			nw.Add(_);
			return nw;
		}
		friend node operator +(const int &x,const node &y);
		friend node operator -(const int &x,const node &y);
		friend node operator *(const int &x,const node &y);
		friend node operator ^(const int &x,const node &y);
		friend node operator /(const int &x,const node &y);
		node operator +(const int &_)const{return *this+node(_);}
		node operator -()const{return *this*(-1);}
		node operator -(const node &_)const{return *this+_*(-1);}
		node operator *(const node &_)const{
			if(v==1)return _;
			if(_.v==1)return *this;
			if(cmp(Type,_.Type))return _**this;
			if(Type=='/'&&_.Type=='/')return node('/',*a[0]**_.a[0],*a[1]**_.a[1]);
			if(Type=='/')return node('/',*a[0]*_,*a[1]);
			if(Type=='+'&&_.Type=='+'){
				node nw('+');
				FOO(i,a)FOO(j,_.a)nw.Add_(*a[i]**_.a[j]);
				nw.Adjust();
				return nw;
			}
			if(Type=='+'){
				node nw('+');
				FOO(i,a)nw.Add_(*a[i]*_);
				nw.Adjust();
				return nw;
			}
			if(Type=='*'&&_.Type=='*')return node('*',a,_.a);
			if(Type=='*'){
				node nw=*this;
				nw.Add(_);
				return nw;
			}
			if(isnum()&&_.isnum())return node(v*_.v);
			return node('*',*this,_);
		}
		node operator *(const int &_)const{return *this*node(_);}
		node operator /(const node &_)const{return node('/',*this,_);}
		node operator /(const int &_)const{
			if(!_)error("divide by 0");
			switch(Type){
				case '/':return node('/',*a[0],*a[1]*_);
				case '+':case '*':case '^':case '0':return node('/',*this,node(_));
			}
		}
		node operator ^(const node &_)const{return node('^',*this,_);}
		node operator ^(const int &_)const{return *this^node(_);}
		bool operator ==(const node &_)const{
			if(Type^_.Type||size()^_.size())return 0;
			if(Type=='0')return v==_.v;
			FOO(i,a)if(*a[i]!=*_.a[i])return 0;
			return 1;
		}
		bool operator ==(const int _)const{
			if(!_)return iszero(v.v);
			return Type=='0'&&v==_;
		}
		node& operator +=(const node &_){return *this=*this+_;}
		node& operator -=(const node &_){return *this=*this-_;}
		node& operator *=(const node &_){return *this=*this*_;}
		node& operator *=(const int &_){return *this=*this*_;}
		node& operator ^=(const node &_){return *this=*this^_;}
		node& operator ^=(const int &_){return *this=*this^_;}
		node& operator /=(const node &_){return *this=*this/_;}
		node& operator /=(const int &_){return *this=*this/_;}
		bool operator !=(const node &_)const{return !(*this==_);}
		bool operator !=(const int _)const{return !(*this==_);}
		void Print_()const{
			switch(Type){
				case '/':case '^':{
					if(Type=='/')printf("\\frac");
					if(size()>=1){
						putchar('{');
						a[0]->Print_();
						putchar('}');
					}
					else putchar('#');
					if(Type=='^')printf("%c",Type);
					if(size()>=2){
						putchar('{');
						a[1]->Print_();
						putchar('}');
					}
					else putchar('#');
					break;
				}
				case '+':case '*':{
					if(size()>1&&Type=='*')putchar('(');
					FOO(i,a){
						if(i)putchar(Type);
						a[i]->Print_();
					}
					if(size()>1&&Type=='*')printf(")");
					break;
				}
				case '0':{
					if(isnum())printf("%d",beint(v.v));
					else printf("%c",v.t);
					break;
				}
			}
		}
		void Print()const{
			printf("{%.4Lf}[",v.v);
			Print_();
			puts("]");
		}
		void Print(const string& s)const{
			cout<<s<<':';
			Print();
		}
		void Union_Trans(char t,string& s,int l,int ml,int mr,int r,const vector<int>& nxt){
			node *ls=new node,*rs=new node;
			ls->Trans(s,l,ml,nxt);
			rs->Trans(s,mr,r,nxt);
			a.push_back(ls);
			a.push_back(rs);
			switch(Type=t){
				case '+':v=ls->v+rs->v;break;
				case '-':v=ls->v-rs->v;break;
				case '*':v=ls->v*rs->v;break;
				case '/':v=ls->v/rs->v;break;
				case '^':v=ls->v^rs->v;break;
			}
		}
		void Trans(string& s,int l,int r,const vector<int>& nxt){//纯表示，不化简
			if(l==r)return *this=0,void();
			FON(i,l,r)if(s[i]=='+'||s[i]=='-'){
				if(s[i]=='-')FON(j,i+1,r){
					if(s[j]=='+')s[j]='-';
					else if(s[j]=='-')s[j]='+';
				}
				return Union_Trans(s[i],s,l,i,i+1,r,nxt);
			}
			FON(i,l,r)if(s[i]=='*'||s[i]=='/'){
				if(s[i]=='/')FON(j,i+1,r){
					if(s[j]=='*')s[j]='/';
					else if(s[j]=='/')s[j]='*';
				}
				return Union_Trans(s[i],s,l,i,i+1,r,nxt);
			}
			FON(i,l,r)if(s[i]=='^')return Union_Trans(s[i],s,l,i,i+1,r,nxt);
			if(s[l]=='('||s[l]=='['||s[l]=='{'){
				if(nxt[l]==r)return Trans(s,l+1,r-1,nxt);
				return Union_Trans('*',s,l+1,nxt[l],nxt[l]+1,r,nxt);
			}
			FOR(i,l,r)if(s[i]=='E'||s[i]=='P'||s[i]=='x'||s[i]=='y'||s[i]=='z'||s[i]=='a'||s[i]=='b'||s[i]=='c'){
				if(nxt[l]==r)return *this=node(s[i]),void();
				if(nxt[i]==r)return Union_Trans('*',s,l,i,i,r,nxt);
				return Union_Trans('*',s,l,i+1,i+1,r,nxt);
			}
			istringstream is(s.substr(l,r-l));
			double x;
			string t;
			is>>x;
			if(is.eof()){
				int p=l;
				while(p<r&&s[p]^'.')p++;
				if(p==r)return *this=node(beint(x)),void();
				return *this=node('/',beint(x*pow(10,r-p)),beint(pow(10,r-p))),void();
			}
			char c=0;
			is>>c;
			if(c=='.')error("Adjacent numbers");
			return Union_Trans('*',s,l,r-t.length(),r-t.length(),r,nxt);
		}
		void Union_Calc(char t,string& s,int l,int ml,int mr,int r,const vector<int>& nxt){
			node *ls=new node,*rs=new node;
			ls->Calc(s,l,ml,nxt);
			rs->Calc(s,mr,r,nxt);
			switch(Type=t){
				case '+':*this=(*ls)+(*rs);break;
				case '-':*this=(*ls)-(*rs);break;
				case '*':*this=(*ls)*(*rs);break;
				case '/':*this=(*ls)/(*rs);break;
				case '^':*this=(*ls)^(*rs);break;
			}
		}
		void Calc(string& s,int l,int r,const vector<int>& nxt){//计算并化简
			if(l==r)return *this=0,void();
			FON(i,l,r)if(s[i]=='+'||s[i]=='-'){
				if(s[i]=='-')FON(j,i+1,r){
					if(s[j]=='+')s[j]='-';
					else if(s[j]=='-')s[j]='+';
				}
				return Union_Calc(s[i],s,l,i,i+1,r,nxt);
			}
			FON(i,l,r)if(s[i]=='*'||s[i]=='/'){
				if(s[i]=='/')FON(j,i+1,r){
					if(s[j]=='*')s[j]='/';
					else if(s[j]=='/')s[j]='*';
				}
				return Union_Calc(s[i],s,l,i,i+1,r,nxt);
			}
			FON(i,l,r)if(s[i]=='^')return Union_Calc(s[i],s,l,i,i+1,r,nxt);
			if(s[l]=='('||s[l]=='['||s[l]=='{'){
				if(nxt[l]==r)return Calc(s,l+1,r-1,nxt);
				return Union_Calc('*',s,l+1,nxt[l],nxt[l]+1,r,nxt);
			}
			FOR(i,l,r)if(s[i]=='E'||s[i]=='P'||s[i]=='x'||s[i]=='y'||s[i]=='z'||s[i]=='a'||s[i]=='b'||s[i]=='c'){
				if(nxt[l]==r)return *this=node(s[i]),void();
				if(nxt[i]==r)return Union_Calc('*',s,l,i,i,r,nxt);
				return Union_Calc('*',s,l,i+1,i+1,r,nxt);
			}
			istringstream is(s.substr(l,r-l));
			double x;
			string t;
			is>>x;
			if(is.eof()){
				int p=l;
				while(p<r&&s[p]^'.')p++;
				if(p==r)return *this=node(beint(x)),void();
				return *this=node('/',beint(x*pow(10,r-p)),beint(pow(10,r-p))),void();
			}
			char c=0;
			is>>c;
			if(c=='.')error("Adjacent numbers");
			return Union_Calc('*',s,l,r-t.length(),r-t.length(),r,nxt);
		}
		void Read(){
			string s;
			cin>>s;
			vector<int>nxt(s.length());
			vector<int>l;
			FOS(i,s){
				nxt[i]=i+1;
				switch(s[i]){
					case '(':case '[':case '{':l.push_back(i);break;
					case ')':case ']':case '}':{
						if(l.empty())error("unmatched ",s[i]);
						int x=*(l.end()-1);
						if(Bracket(s[x])!=Bracket(s[i]))error("wrong match ",s[x],s[i]);
						nxt[*(l.end()-1)]=i+1;
						l.erase(l.end()-1,l.end());
						break;
					}
					case '+':case '-':case '*':case '/':case '^':break;
					case '0':case '1':case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9':case '.':break;
					case 'E':case 'P':case 'e':break;
					case 'x':case 'y':case 'z':case 'a':case 'b':case 'c':break;
					default:error("Unknown char ",s[i]);
				}
			}
			if(!l.empty())error("expect",Bracket[s[*(l.end()-1)]]);
			Calc(s,0,s.length(),nxt);
			// Trans(s,0,s.length(),nxt);
		}
	};
	node operator +(const int &x,const node &y){return node(x)+y;}
	node operator -(const int &x,const node &y){return node(x)-y;}
	node operator *(const int &x,const node &y){return node(x)*y;}
	node operator ^(const int &x,const node &y){return node(x)^y;}
	node operator /(const int &x,const node &y){return node(x)/y;}
	bool cmp_pair(pair<node,int>& A,pair<node,int>& B){
		if(A.first<B.first)return 1;
		if(B.first<A.first)return 0;
		return A.second>B.second;
	}
	void node::Unique(vector<pair<node,int> >& s,vector<node>& t,vector<double>& V){
		if(s.empty()){
			t.push_back(node(1));
			V.push_back(1);
			return;
		}
		sort(s.begin(),s.end(),cmp_pair);
		vector<pair<node,int> >::iterator i,j;
		if(s.size()>1){
			for(i=s.begin(),j=i+1;j!=s.end();j++)if(i->first<j->first&&i+1<j)*++i=*j;
			// exit(0);
			s.erase(i+1,s.end());
		}
		vector<int>e(s.size());
		Enum(s,e,t,s.size());
		sort(t.begin(),t.end());
		V.resize(t.size());
		FOO(i,t)V[i]=t[i].v.v;
	}
	void node::Unique(vector<pair<node,int> >& s,vector<node>& t1,vector<double>& V1,vector<node>& t2,vector<double>& V2){
		if(s.empty()){
			t1.push_back(node(1));
			t2.push_back(node(1));
			V1.push_back(1);
			V2.push_back(1);
			return;
		}
		sort(s.begin(),s.end(),cmp_pair);
		vector<pair<node,int> >::iterator i,j;
		if(s.size()>1){
			for(i=s.begin(),j=i+1;j!=s.end();j++)if(i->first<j->first&&i+1<j)*++i=*j;
			s.erase(i+1,s.end());
		}
		vector<int>e(s.size());
		Enum(s,e,t1,s.size());
		sort(t1.begin(),t1.end());
		V1.resize(t1.size());
		FOO(i,t1)V1[i]=t1[i].v.v;

		if(s.size()>1){
			for(i=s.begin(),j=i+1;j!=s.end();j++)if(j->first.Radical()&&i+1<j)*++i=*j;
			s.erase(i+1,s.end());
		}
		e.resize(s.size());
		Enum(s,e,t2,s.size());
		sort(t2.begin(),t2.end());
		V2.resize(t2.size());
		FOO(i,t2)V2[i]=t2[i].v.v;
	}
	set<node>s;
	bool node::Abbre_free(){return s.find(*this)!=s.end();}
	void node::Abbre_after(){node nw=*this;s.insert(nw);}
	void node::Abbreviation(){//最多只有一层不合法的表达
		if(isint(v.v))return *this=beint(v.v),void();
		if(Abbre_free())return;
		while(Adjust(),Type^'0'){
			switch(Type){
				case '/':{
					node x(*a[0]),y(*a[1]);
					if(x==0)return *this=0,Abbre_after();
					if(y==0)error("Divide by 0");
					if(y==1){
						*this=x;
						break;
					}
					if(x.Type=='/'){
						*this=node('/',*x.a[0],*x.a[1]*y);
						break;
					}
					if(y.Type=='/'){
						*this=node('/',x**y.a[1],*y.a[0]);
						break;
					}
					if(Negative(y)){
						x*=-1;
						y*=-1;
						*this=x/y;
					}
					if(x.isnum()&&y.isnum()){
						if(gcd(x.v,y.v))*this=x/y;
						return Abbre_after();
					}
					if(y.Rationalization(x))*this=x/y;
					Factorization(x,y);
					int i=0,j=0;
					bool flag=1;
					node nw;
					nw.Init();
					while(i<x.size()&&j<y.size()){
						if(x.a[i]->isnum()&&y.a[j]->isnum()&&gcd(x.a[i]->v,y.a[j]->v)){
							*nw.a[0]*=x.a[i++]->v;
							*nw.a[1]*=y.a[j++]->v;
							flag=0;
						}else if(*x.a[i]<*y.a[j])*nw.a[0]*=*x.a[i++];
						else if((*x.a[i])==(*y.a[j]))i++,j++,flag=0;
						else *nw.a[1]*=*y.a[j++];
					}
					if(flag)return Abbre_after();
					while(i<x.size())*nw.a[0]*=*x.a[i++];
					while(j<y.size())*nw.a[1]*=*y.a[j++];
					nw.v=v;
					*this=nw;
					break;
				}
				case '+':{
					int flag=0;
					FOO(i,a)if(a[i]->Type=='/'){
						*this=node('/',*this**a[i]->a[1],*a[i]->a[1]);
						break;
					}
					node nw(Type,*a[0]);
					FOR(i,1,size()){
						flag|=1;
						FOO(j,nw.a)if(*nw.a[j]|=*a[i]){
							flag|=2;
							flag^=1;
							break;
						}
						if(flag&1)nw.Insert(*a[i]);
					}
					if(flag&2){
						*this=nw;
						break;
					}
					return Abbre_after();
				}
				case '*':{
					FOO(i,a)if(a[i]->Type=='/'){
						*this=node('/',*this**a[i]->a[1],*a[i]->a[1]);
						break;
					}
					FOO(i,a)if(a[i]->Type=='+'){
						node nw=node(1);
						FOO(j,a)nw*=*a[i];
						*this=nw;
						break;
					}
					int flag=0;
					node nw(Type,*a[0]);
					FOR(i,1,size()){
						flag|=1;
						FOO(j,nw.a)if(*nw.a[j]&=*a[i]){
							nw.v*=a[i]->v;
							flag|=2;
							flag^=1;
							break;
						}
						if(flag&1)nw.Insert(*a[i]);
					}
					if(flag&2){
						*this=nw;
						break;
					}
					return Abbre_after();
				}
				case '^':{
					node x(*a[0]),y(*a[1]);
					if(y==0)return *this=1,Abbre_after();
					if(y==1)return *this=x,Abbre_after();
					if(Negative(y)){
						*this=node('/',node(1),x^-y);
						break;
					}
					if(x.Type=='/'){
						Val tmp=v;
						FOO(i,x.a)*x.a[i]^=y;
						*this=x;
						v=tmp;
						break;
					}
					if(x.Type=='+'&&y.isnum()){
						int n=y.v.v;
						*this=1;
						while(n--)*this*=x;
						break;
					}
					if(x.Type=='*'){
						*this=node(1);
						FOO(i,x.a)*this*=*x.a[i]^y;
						break;
					}
					if(x.Type=='^'){
						*this=node('^',*x.a[0],*x.a[1]*y);
						break;
					}
					if(x.isnum()&&x.v>0){
						vector<pair<int,int> >p;
						Pri(beint(x.v.v),p);
						if(p.size()>1||p[0].second>1){
							node nw=1;
							FOO(i,p)nw*=node(p[i].first)^(y*p[i].second);
							*this=nw;
							break;
						}else if(y.isnum()){
							*this=beint(pow(x.v.v,y.v.v));
							break;
						}
					}else if(y.Type=='/'&&y.a[1]->isnum()){
						x.Factorization(beint(y.a[1]->v.v));
						if(x.Type=='^'){
							*this=*x.a[0]^(*x.a[1]*y);
							break;
						}
					}
					if(y.Type=='+'){
						y.Type='*';
						FOO(i,y.a)*y.a[i]=x^*y.a[i];
						*this=y;
						break;
					}
					x.Factorization(0);
					x.Adjust();
					if(x.Type=='*'){
						*this=node(1);
						FOO(i,x.a)*this*=*x.a[i]^y;
						break;
					}
					return Abbre_after();
				}
			}
		}Abbre_after();
	}
	void test(){
		// node E('E'),one(1),two(2);
		// node tmp;
		// tmp=1/(2^E);
		// tmp.Print("ans");
		// tmp=E*(E+one)/two;
		// (tmp^2).Print("tmp");
		// tmp=(tmp^2)/tmp;
		// tmp.Print("Ans");
		s.clear();
		node x;
		while(1){
			x.Read();
			x.Print("ANS");
		}
		// exit(0);
	}
}
void error(const string& s){
	cerr<<"!!:"<<s<<endl;
	My::test();
}
void error(const string& s,char c){
	cerr<<"!!:"<<s<<c<<endl;
	My::test();
}
void error(const string& s,char c,char d){
	cerr<<"!!:"<<s<<c<<d<<endl;
	My::test();
}
int main(){
	My::test();
}
/**/