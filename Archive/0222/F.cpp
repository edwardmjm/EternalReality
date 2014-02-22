#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
#define rep(i,n) for (int i = 0; i < (int)(n); i++)
string s, t;
int n, m, cz;
int a[1005];
int v[10];
int times[10];
int flag[1 << 12];
bool own[1 << 12];
vector <char> coor;


int getLength(int mask) {
	return 31 - __builtin_clz(mask);
}

void out(int mask) {
	int len = getLength(mask);
	for (len--; len >= 0; len--) {
		cout << ( (mask & 1 << len) ? "1" : "0" );
	}
}

void output() {
	rep (i, cz) {
		cout << coor[i] << " ";
		out(v[i]);
		cout << endl;
	}
}

bool checkCommon(int i, int mask) {
	int len = getLength(mask);
	if (i + len > m) return 0;
	int off = 0;
	for (len--; len >= 0; off++, len--) {
		if (!!(mask & 1 << len) != (t[i + off] == '1')) {
			return 0;
		}
	}
	return 1;
}

bool canAssign(int x, int value) {
	int sum = 0, all = 0, rst = 0;
	rep (i, cz) 
		if (i == x) {
			sum += value * times[i];
			all++;
		} else if (v[i] != -1) {
			sum += getLength(v[i]) * times[i];
			all++;
		} else {
			rst += times[i];
		}
	if (sum + rst > m) return 0;
	if (sum + rst * 10 < m) return 0;
	return 1;
}

int getMask(int st, int len) {
	int res = 1 << len;
	rep (i, len) {
		res |= (t[st + i] == '1') << (len - i - 1);
	}
	return res;
}

bool ok(int mask) {
	if (flag[mask]) return 0;
	int len = getLength(mask);
	while (len) {
		if (own[mask]) return 0;
		len--;
		mask >>= 1;
	}
	return 1;
}

void cover(int mask) {
	own[mask] = 1;
	int len = getLength(mask);
	while (len) {
		flag[mask]++;
		len--;
		mask >>= 1;
	}
}

void recover(int mask) {
	own[mask] = 0;
	int len = getLength(mask);
	while (len) {
		flag[mask]--;
		len--;
		mask >>= 1;
	}
}

bool dfs(int i = 0, int j = 0) {
	if (i == n) {
		if (j == m) {
			output();
			return 1;
		} else {
			return 0;
		}
	} else if (v[a[i]] != -1) {
		if (checkCommon(j, v[a[i]])) {
			if (dfs(i + 1, j + getLength(v[a[i]]))) return 1;
		}
	} else {
		for (int len = 1; len <= 10; len++) {
			if (canAssign(a[i], len)) {
				v[a[i]] = getMask(j, len);
				if (ok(v[a[i]])) {
					cover(v[a[i]]);
					if (dfs(i + 1, j + len)) return 1;
					recover(v[a[i]]);
				}
				v[a[i]] = -1;
			}
		}
	}
	return 0;
}

int main() {
	freopen("prefix.in", "r", stdin);
	freopen("prefix.out", "w", stdout);
	getline(cin, s);
	getline(cin, t);
	rep (i, s.size()) coor.push_back(s[i]);
	sort(coor.begin(), coor.end());
	coor.resize(unique(coor.begin(), coor.end()) - coor.begin());
	n = s.size();
	m = t.size();
	cz = coor.size();
	rep (i, coor.size()) times[i] = 0, v[i] = -1;
	memset(flag, 0, sizeof(flag));
	rep (i, n) {
		a[i] = lower_bound(coor.begin(), coor.end(), s[i]) - coor.begin();
		times[a[i]]++;
	}
	dfs();
}
