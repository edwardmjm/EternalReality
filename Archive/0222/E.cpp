#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#define rep(i,n) for (int i = 0; i < (int)(n); i++)
using namespace std;
typedef pair <int, int> PII;
typedef vector <short> VEC;
const int N = 305;
int n;
VEC a[N], b[N], c[N];

VEC join(const VEC &a, const VEC &b) {
	VEC res(a.size() + b.size());
	rep (i, a.size()) res[i] = a[i];
	rep (i, b.size()) res[i + a.size()] = b[i];
	return res;
}

bool test(const VEC &v) {
	int m = 0;
	for (int del = 1; del <= n; del++) {
		VEC tmp = v;
		tmp.erase(find(tmp.begin(), tmp.end(), del));
		rep (j, n - 1) if (tmp[j] > del) tmp[j]--;
		c[m++] = tmp;
	}
	sort(c, c + m);
	rep (i, n) if (b[i] != c[i]) return 0;
	rep (i, v.size()) {
		if (i) printf(" ");
		printf("%d", v[i]);
	}
	puts("");
	return 1;
}

void gao() {
	rep (i, n) {
		swap(a[0], a[i]);
		int lhs = 0, rhs = 0;
		for (int j = 1; j < n; j++) {
			if (a[j][0] == 1) lhs++;
			if (a[j][n - 2] == 1) rhs++;
		}
		VEC cur = a[0];
		rep (j, n - 1) cur[j]++;
		if (lhs == n - 1) {
			if (test(join(VEC(1, 1), cur))) return;
		} else if (rhs == n - 1) {
			if (test(join(cur, VEC(1, 1)))) return;
		} else {
			for (int idx = 1; idx < n; idx++) {
				rep (j, n - 1) {
					if (a[idx][j] == 1 && j && j + 1 < n - 1) {
						lhs = a[idx][j - 1];
						rhs = a[idx][j + 1];
						goto FINISH;
					}
				}
			}
			FINISH:;
			VEC tmp = cur;
			tmp.insert(find(tmp.begin(), tmp.end(), lhs) + 1, 1);
			if (test(tmp)) return;
			if (lhs + 1 <= n) {
				tmp = cur;
				tmp.insert(find(tmp.begin(), tmp.end(), lhs + 1) + 1, 1);
				if (test(tmp)) return;
			}
			tmp = cur;
			tmp.insert(find(tmp.begin(), tmp.end(), rhs), 1);
			if (test(tmp)) return;
			if (rhs + 1 <= n) {
				tmp = cur;
				tmp.insert(find(tmp.begin(), tmp.end(), rhs + 1), 1);
				if (test(tmp)) return;
			}
		}
		swap(a[0], a[i]);
	}
}

int main() {
	freopen("permutation.in", "r", stdin);
	freopen("permutation.out", "w", stdout);
	scanf("%d", &n);
	rep (i, n) {
		a[i].resize(n - 1);
		rep (j, n - 1) {
			int tmp;
			scanf("%d", &tmp);
			a[i][j] = tmp;
		}
	}
	sort(a, a + n);
	rep (i, n) b[i] = a[i];
	gao();
	return 0;
}
