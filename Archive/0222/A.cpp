#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef pair <int, int> PII;
const int N = 35;
int n, m;
PII a[N];
int f[N][5005];
PII c[N][5005];
int mul[N][5005];
int s[N][N];
int value[N];

int solve(int n, int m) {
	if (n == 0) return 0;
	PII pre = c[n][m];
	int res = solve(pre.first, pre.second);
	for (int i = pre.first; i < n; i++) {
		value[i] = mul[n][m] + res;
	}
	return mul[n][m] + res;
}

int main() {
	freopen("cookies.in", "r", stdin);
	freopen("cookies.out", "w", stdout);
	scanf("%d%d", &n, &m);
	memset(f, 0xff, sizeof(f));
	f[0][0] = 0;
	for (int i = 0; i < n; i++) {
		scanf("%d", &a[i].first);
		a[i].second = i;
	}
	sort(a, a + n);
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j <= n; j++) {
			s[i][j] = 0;
			for (int k = i; k < j; k++)
				s[i][j] += a[k].first;
		}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) if (f[i][j] != -1) {
			for (int k = 1; j + k * (n - i) <= m; k++) {
				for (int t = i + 1; t <= n; t++) {
					int &res = f[t][j + k * (n - i)];
					PII &coo = c[t][j + k * (n - i)];
					int &mul = ::mul[t][j + k * (n - i)];
					if (res == -1 || f[i][j] + s[i][t] * (n - t) < res) {
						res = f[i][j] + s[i][t] * (n - t);
						coo = make_pair(i, j);
						mul = k;
					}
				}
			}
		}
	}
	printf("%d\n", f[n][m]);
	solve(n, m);
	for (int i = 0; i < n; i++) {
		if (i) putchar(' ');
		for (int j = 0; j < n; j++) {
			if (a[j].second == i) {
				printf("%d", value[j]);
			}
		}
	}
	puts("");
}
