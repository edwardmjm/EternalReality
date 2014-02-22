#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

typedef pair<int,int> PII;

vector<PII> e[100005];
vector<int> ans;

int n,m;

int gao(int x, int src){
	int cnt=1;
	vector<PII> u;
	for(size_t i=0;i<e[x].size();i++){
		int y=e[x][i].first;
		if(y==src) continue;
		u.push_back(PII(gao(y,x),e[x][i].second));
		cnt+=u.back().first;
	}
	if(cnt<=m) return cnt;
	if(u.size()==1){
		ans.push_back(u[0].second);
		cnt=1;
	}else if(cnt==m*2+1){
		ans.push_back(u[0].second);
		ans.push_back(u[1].second);
		cnt=1;
	}else if(u[0].first>u[1].first){
		cnt-=u[0].first;
		ans.push_back(u[0].second);
	}else{
		cnt-=u[1].first;
		ans.push_back(u[1].second);
	}
	return cnt;
}

int main(){
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<n;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		e[x].push_back(PII(y,i));
		e[y].push_back(PII(x,i));
	}
	gao(1,0);
	if(ans.size()>(2*n+m-1)/m){
		puts("-1");
	}else{
		printf("%d\n",ans.size());
		for(size_t i=0;i<ans.size();i++){
			if(i) putchar(' ');
			printf("%d",ans[i]);
		}
		puts("");
	}
}

