#include <cstdio>
#include <vector>
#include <cstring>
#include <map>
#include <algorithm>
using namespace std;

typedef pair<int,int> PII;
typedef vector<PII> VPI;
const int INF = 1000000007;

int X[50005],Y[50005],n,dp[50005],go[50005],by[50005];
int D[50005],L[50005],R[50005];
map<int,VPI> row,col,lhs,rhs;

void init(map<int,VPI>& u, int v[]){
	for(map<int,VPI>::iterator t=u.begin();t!=u.end();++t){
		VPI& a=t->second;
		sort(a.begin(),a.end());
		for(size_t i=0;i+1<a.size();i++)
			v[a[i+1].second]=a[i].second;
		if(!t->first) v[a[0].second]=0;
	}
}

void relax(int dst, int src){
	if (dp[dst]<dp[src]+1){
		dp[dst]=dp[src]+1;
		go[dst]=src;
	}
}

void output(int i){
	if(!i) return;
	if(by[i]){
		output(go[by[i]]);
		if(go[by[i]]) putchar(' ');
		printf("%d ",by[i]);
		VPI& a=row[Y[i]];
		int src=find(a.begin(),a.end(),PII(X[by[i]],by[i]))-a.begin();
		int dst=find(a.begin(),a.end(),PII(X[i],i))-a.begin();
		if(src<dst){
			for(int k=src-1;k!=-1 ;k--) printf("%d ",a[k].second);
			for(int k=src+1;k!=dst;k++) printf("%d ",a[k].second);
		}else{
			for(int k=src+1;k!=a.size();k++) printf("%d ",a[k].second);
			for(int k=src-1;k!=dst;k--) printf("%d ",a[k].second);
		}
	}else{
		output(go[i]);
		if(go[i]) putchar(' ');
	}
	printf("%d",i);
}

int main(){
	freopen("queen.in","r",stdin);
	freopen("queen.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d",X+i,Y+i);
		row[Y[i]].push_back(PII(X[i],i));
		col[X[i]].push_back(PII(Y[i],i));
		lhs[Y[i]-X[i]].push_back(PII(Y[i],i));
		rhs[Y[i]+X[i]].push_back(PII(Y[i],i));
	}
	memset(dp,192,sizeof(dp));
	memset(D,-1,sizeof(D));
	memset(L,-1,sizeof(L));
	memset(R,-1,sizeof(R));
	dp[0]=0;
	init(col,D);
	init(lhs,L);
	init(rhs,R);
	int u[50005]={-INF},p[50005]={};
	int v[50005]={-INF},q[50005]={};
	int ans=0,end=0;
	for(map<int,VPI>::iterator t=row.begin();t!=row.end();++t){
		VPI& a=t->second;
		sort(a.begin(),a.end());
		for(int i=0;i<a.size();i++){
			int x=a[i].second;
			if(~D[x]) relax(x,D[x]);
			if(~L[x]) relax(x,L[x]);
			if(~R[x]) relax(x,R[x]);
			if(dp[x]>u[i]){
				u[i+1]=dp[x];
				p[i+1]=x;
			}else{
				u[i+1]=u[i];
				p[i+1]=p[i];
			}
		}
		for(int i=a.size()-1;~i;i--){
			int x=a[i].second,j=a.size()-i-1;
			if(dp[x]>v[j]){
				v[j+1]=dp[x];
				q[j+1]=x;
			}else{
				v[j+1]=v[j];
				q[j+1]=q[j];
			}
		}
		for(int i=0;i<a.size();i++){
			int x=a[i].second,j=a.size()-i-1;
			if(u[i]+i>dp[x]){
				dp[x]=u[i]+i;
				by[x]=p[i];
			}
			if(v[j]+j>dp[x]){
				dp[x]=v[j]+j;
				by[x]=q[j];
			}
			if(dp[x]>ans){
				ans=dp[x];
				end=x;
			}
		}
	}
	printf("%d\n",ans);
	output(end);
	puts("");
}


