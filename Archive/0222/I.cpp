#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

typedef pair<short,short> PII;

char a[3005],b[3005];
PII dp[3005][3005];

int main(){
	freopen("subpair.in","r",stdin);
	freopen("subpair.out","w",stdout);
	int n=strlen(gets(a));
	int m=strlen(gets(b));
	for(int i=0;i<n;i++)
	for(int j=0;j<m;j++){
		dp[i+1][j+1].first=(a[i]!=b[j])?0:dp[i][j].first+1;
		dp[i+1][j+1].second=i;
	}
	for(int i=0;i<=n;i++)
	for(int j=0;j<=m;j++){
		if(i && dp[i-1][j]>dp[i][j]) dp[i][j]=dp[i-1][j];
		if(j && dp[i][j-1]>dp[i][j]) dp[i][j]=dp[i][j-1];
	}
	int rv[2][3005]={},ans=0,p=0,pl=0,q=0,ql=0;
	for(int i=n-1;i>=0;i--)
	for(int j=m-1;j>=0;j--){
		rv[i&1][j]=(a[i]!=b[j])?0:rv[~i&1][j+1]+1;
		int now=dp[i][j].first+rv[i&1][j];
		if(now>ans){
			ans=now;
			p=dp[i][j].second; pl=dp[i][j].first;
			q=i; ql=rv[i&1][j];
		}
	}
	for(int i=0;i<pl;i++) putchar(a[p-pl+i+1]); puts("");
	for(int i=0;i<ql;i++) putchar(a[q+i]); puts("");
}
/*
abacabadabacaba
acabacadacabaca
*/
