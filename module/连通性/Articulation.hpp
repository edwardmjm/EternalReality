// 无向图关键点、关键边和双连通分量 By 猛犸也钻地 @ 2012.07.23

#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

class Articulation {
public:
    typedef pair<int,int> PII;
    static const int SIZE = 100005; // 最大结点个数
    vector<PII> keyE;               // keyE为割边集，keyV为割点集
    vector<int> keyV,cc[SIZE];      // cc[p]表示结点p在哪些双连通分量中
    int cnt;  // 遇到奇怪的编译错误时，将上面的cc[SIZE]改成vector形式
    // 传入结点个数n及各结点的出边e[]，返回双连通分量的个数cnt
    // 限制条件：要保证是无向图，且没有重边
    int gao(int n, const vector<int> e[]){
        memset(tag,use=0,sizeof(tag));
        memset(low,cnt=0,sizeof(low));
        keyE.clear();
        fill_n(cc,SIZE,keyV=vector<int>());
        for(int i=0;i<n;i++) if(!tag[i]) dfs(i,1,e);
        return cnt;
    }
private:
    int tag[SIZE],low[SIZE],dot[SIZE],use;
    void dfs(int x, int dep, const vector<int> e[]){
        int pt=dep>1;
        dot[use++]=x;
        tag[x]=low[x]=dep;
        for(size_t i=0;i<e[x].size();i++){
            int y=e[x][i];
            if(!tag[y]){
                dfs(y,dep+1,e);
                low[x]=min(low[x],low[y]);
                if(low[y]> tag[x]) keyE.push_back(PII(x,y));
                if(low[y]>=tag[x]){
                    if(++pt==2) keyV.push_back(x);
                    while(dot[--use]!=y) cc[dot[use]].push_back(cnt);
                    cc[x].push_back(cnt);
                    cc[y].push_back(cnt++);
                }
            }else if(tag[y]!=tag[x]-1){
                low[x]=min(low[x],tag[y]);
            }
        }
    }
};
