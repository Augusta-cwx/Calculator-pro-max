#pragma once
#include"³£ÓÃº¯Êý.h"
struct Prime {
	const int n = 6e4;
	int p[60000];
	bool mark[60005];
	Prime() {
		for (int i = 2; i <= n; i++)if (!mark[i]) {
			for (int j = i + i; j <= n; j++)mark[j] = 1;
			p[++p[0]] = i;
		}
	}
	bool operator()(int x, vector<pair<int, int> >& s)const {
		for (int i = 1; i <= p[0] && p[i] <= x / p[i]; i++)if (x % p[i] == 0) {
			int t = 0;
			while (x % p[i] == 0) {
				t++;
				x /= p[i];
			}
			s.push_back(make_pair(p[i], t));
		}
		if (x > 1)s.push_back(make_pair(x, 1));
		return s.size() > 1;
	}
	void Enum(const vector<pair<int, int> >& q, int cur, int v, vector<int>& p)const {
		--cur;
		if (cur == -1) {
			if (v ^ 1)p.push_back(v);
			return;
		}
		Enum(q, cur, v, p);
		for(int i=1;i<=q[cur].second;i++)
			Enum(q, cur, v *= q[cur].first, p);
	}
	void operator[](vector<int>& p)const {
		vector<pair<int, int> >q;
		(*this)(p[0], q);
		p.erase(p.begin(), p.end());
		Enum(q, q.size(), 1, p);
		sort(p.begin(), p.end());
	}
};