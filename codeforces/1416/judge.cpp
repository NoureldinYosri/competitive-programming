#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define mem(x,y) memset(x,y,sizeof(x))
const int M=4e6+10;
const int inf=0x3f3f3f3f;
const ll mod=1e9+7;
const int bit=32;
const double pi=acos(-1.0);
struct node{
    int x,y,used;
}w[M];
struct edg{
    int x,y;
}q[M];
int a[M],f[M],b[M],sum[M],cnt=0,pre[M];
vector<int>v[M];
int in[M],out[M],tot=0;
int fi(int x){
    return f[x]==x?x:f[x]=fi(f[x]);
}
void dfs(int x){
    in[x]=++tot;
    for(int i=0;i<v[x].size();i++){
        dfs(v[x][i]);
    }
    out[x]=tot;
}
void mergy(int x,int y){
    int xx=fi(x),yy=fi(y);
    if(xx!=yy){
        cnt++;
        f[xx]=cnt;
        f[yy]=cnt;
        f[cnt]=cnt;
        v[cnt].push_back(xx);
        v[cnt].push_back(yy);
    }
}
void add(int l,int r,int x,int va,int i){
    if(l==r){
        sum[i]=va;
        return;
    }
    int mid=l+r>>1;
    if(x<=mid)
    add(l,mid,x,va,i<<1);
    else
    add(mid+1,r,x,va,i<<1|1);
    sum[i]=max(sum[i<<1],sum[i<<1|1]);
}
int query(int l,int r,int x,int y,int i){
    if(l>=x&&r<=y)
    return sum[i];
    int mid=l+r>>1;
    int ans=0;
    if(x<=mid)
    ans=query(l,mid,x,y,i<<1);
    if(y>mid)
    ans=max(ans,query(mid+1,r,x,y,i<<1|1));
    return ans;
}
stack<int>ans;
int main(){
    int n,m,k;
    scanf("%d%d%d",&n,&m,&k);
    cnt=n;
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        pre[a[i]]=i;
        f[i]=i;
    }
    for(int i=1;i<=m;i++){
        scanf("%d%d",&w[i].x,&w[i].y);
        w[i].used=0;
    }
    for(int i=1;i<=k;i++){
        scanf("%d%d",&q[i].x,&q[i].y);
        if(q[i].x==2)
        w[q[i].y].used=1;
    }
    for(int i=1;i<=m;i++){
        if(!w[i].used){
            mergy(w[i].x,w[i].y);
        }
    }
    for(int i=k;i>=1;i--){
        if(q[i].x==1){
            ans.push(fi(q[i].y));
        }
        else{
            mergy(w[q[i].y].x,w[q[i].y].y);
        }
    }
    for(int i=cnt;i>=1;i--){
        if(!in[i])
        dfs(i);
    }
    for(int i=1;i<=cnt;i++){
        add(1,cnt,in[i],a[i],1);
    }
    while(ans.size()){
        int x=ans.top();
        ans.pop();
        int p=query(1,cnt,in[x],out[x],1);
        printf("%d\n",p,in[pre[p]]);
        if(p!=0)
        add(1,cnt,in[pre[p]],0,1);
    }
    return 0;
}
