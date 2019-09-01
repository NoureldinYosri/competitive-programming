#ifdef DEBUG
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<queue>
#include<map>
#include<time.h>
#include<math.h>
using namespace std;
typedef long long LL;
LL dp[205][2];// 定义DP[cur][0/1] 表示遍历cur节点的子树叶子节点，1表示返回该cur 0表示不返回cur.
const int MAX=1e3+10;
class Edge{
public:
    LL u,v,next,w;
};
int tot=0;
Edge edge[MAX];
int head[MAX];
void add(LL u,LL v,LL w){
    edge[tot].u=u;
    edge[tot].v=v;
    edge[tot].w=w;
    edge[tot].next=head[u];
    head[u]=tot++;
}
LL sizes[MAX];// 该节点有多少个叶子节点
LL dis[MAX];// 该1节点到该节点的距离
int du[205];// 可以表示节点的子节点数
void dfs(int u,int per){
    if(du[u]<=1){
        sizes[u]=1;
    }else{
        sizes[u]=0;
    }
    LL cnt=0;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].v;
        if(v==per) continue;
        dis[v]=dis[u]+edge[i].w;
        dfs(v,u);
        LL val;
        sizes[u]+=sizes[v];
        if(dis[v]+dp[v][0]<sizes[v]*edge[i].w+dp[v][1]){
            val = dis[v]+dp[v][0];
            cnt = max(cnt,val-(edge[i].w+dp[v][0]));
        }else{
            val = sizes[v]*edge[i].w+dp[v][1];
            cnt = max(cnt,val-(edge[i].w+dp[v][0]));
        }
        dp[u][0]+=val;
        dp[u][1]+=val;
    }
    dp[u][0]-=cnt;
}
int main(){
    int T;
    cin>>T;
    while(T--){
        int n;
        scanf("%d",&n);
        memset(dp,0,sizeof dp);
        memset(head,-1,sizeof head);
        memset(dis,0,sizeof dis);
        memset(du,0,sizeof du);
        memset(sizes,0,sizeof sizes);
        tot=0;
        for(int i=1;i<n;i++){
            LL u,v,w;
            scanf("%lld %lld %lld",&u,&v,&w);
            du[u]++;
            du[v]++;
            add(u,v,w);
            add(v,u,w);
        }
        dfs(1,-1);
        cout<<dp[1][1]<<endl;
    }
}
#endif
