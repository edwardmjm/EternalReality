#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
	freopen("irreducible.in","r",stdin);
	freopen("irreducible.out","w",stdout);
	int n,m=0,x;
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%d",&x);
		m+=(x+!(i&1))/2;
		m-=(x+ (i&1))/2;
	}
	int ans=m>0?m*2-1:m*-2;
	printf("1\n%d",ans);
	for(int i=ans;i;i--) printf(" %d",i);
	puts("");
}

