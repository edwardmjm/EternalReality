#include <cstdio>
#include <algorithm>
using namespace std;

const int INF = 10000007;

int a[105][205],idx[105],src[105],dst[105];
int s[105][105],end[105];

int main(){
	freopen("epig.in","r",stdin);
	freopen("epig.out","w",stdout);
	int n,m,loop=0;
	scanf("%d%d",&n,&m);
	a[0][0]=INF;
	a[1][0]=m;
	int all=n-1;
	for(int i=1;i<=m;i++) a[0][i]=a[1][i]=1;
	for(int i=1;i<=n;i++) s[0][i]=-INF;
	while(all){
		loop++;
		for(int i=1;i<=n;i++){
			int k=0;
			for(int j=1;j<=m;j++){
				if(a[i][j]) continue;
				if(a[0][j]<a[0][k]) k=j;
			}
			idx[i]=k;
		}
		for(int i=1;i<=n;i++){
			if(!idx[i]){
				src[i]=0;
				continue;
			}
			int k=0;
			for(int j=1;j<=n;j++){
				if(a[j][idx[i]]==0) continue;
				if(a[j][0]<a[k][0]) k=j;
			}
			src[i]=k;
		}
		for(int i=1;i<=n;i++){
			int k=0;
			for(int j=1;j<=n;j++){
				if(src[j]!=i) continue;
				if((s[j][i]> s[k][i])
				|| (s[j][i]==s[k][i] && a[j][0]<a[k][0])) k=j;
			}
			dst[i]=k;
		}
		for(int i=1;i<=n;i++) if(dst[i]){
			a[dst[i]][idx[dst[i]]]=1;
			a[dst[i]][0]++;
			a[0][idx[dst[i]]]++;
			s[i][dst[i]]++;
			if(a[dst[i]][0]==m){
				end[dst[i]]=loop;
				all--;
			}
		}
	}
	for(int i=2;i<=n;i++){
		if(i!=2) putchar(' ');
		printf("%d",end[i]);
	}
	puts("");
}

