#include <bits/stdc++.h>
using namespace std;
 
const int N = 1e5 + 5;
vector<int>adj[N];
int in[N] , out[N] , visit[N] , dist[N] , rev[N] , ans[N] , add[500] , arr[N];
vector<int>vec[500];
int preSum[500][N] , mini[500] , maxi[500];
int t,n;
int BS,len;
void dfs(int u , int d = 0)
{
    in[u] = t;
    rev[t] = u;
    visit[u] = 1;
    dist[t] = d;
    t++;
    for(auto v : adj[u])
        if(!visit[v]) dfs(v , d+1);
    out[u] = t-1;
}
 
void updateAllBlock(int x, int val , int flag , int y = -1)
{
    int idx = x/BS;
    for(int i = mini[idx] ; i<= maxi[idx] ; ++i) preSum[idx][i] = 0;
    mini[idx] = 1e9 , maxi[idx] = -1e9;
    for(int i = idx*BS ; i/BS == idx && i < n ; ++i)
    {
        dist[i] += add[idx];
        if(i >= x && flag == 1) dist[i] += val;
        if(i <= x && flag == 2) dist[i] += val;
        if(i <= y && i>=x && flag == 3) dist[i] += val;
        preSum[idx][dist[i]]++;
        mini[idx] = min(mini[idx] , dist[i]);
        maxi[idx] = max(maxi[idx] , dist[i]);
    }
    for(int i = mini[idx] ; i<= maxi[idx] ; ++i)
        if(i != 0) preSum[idx][i] += preSum[idx][i-1];
    add[idx] = 0;
}
 
void updateRange(int l , int r , int val)
{
    for(int i = l/BS + 1 ; i< r/BS ; ++i)
    {
        add[i] += val;
    }
 
    if(l/BS != r/BS)
    {
        updateAllBlock(l ,  val , 1);
        updateAllBlock(r ,  val , 2);
    }
    else
    {
        updateAllBlock(l , val , 3 , r );
    }
}
 
void update(int u , int val)
{
    updateRange(0 , n-1 , val);
    updateRange(in[u] , out[u] , -2*val);
}
 
int getSum(int mid)
{
    int sum = 0;
    for(int i = 0 ; i<len ; ++i)
    {
        int tot = preSum[i][maxi[i]];
        int need = mid - add[i];
 
        if(need < mini[i]) sum += tot;
        else if(need > maxi[i]) sum += 0;
        else sum += tot - preSum[i][need];
    }
    //cout<<mid<<" "<<sum<<endl;
    return sum;
}
 
void solve(int u , int par = -1)
{
    if(u != 0)
    {
        update(u,1);
    }
 
    int l = 0 , r = n;
    while (l<r)
	{
		int mid = l + (r - l + 1) / 2;
		int sum = getSum(mid);
		if (sum >= arr[u]) l = mid;
		else r = mid - 1;
	}
	//cout<<u<<" "<<getSum(l)<<endl;
    ans[u] = l;
    for(auto v : adj[u])
        if(v != par) solve(v , u);
 
    if(u != 0)
    {
        update(u,-1);
    }
}
 
 
int main() {
 
    scanf("%d" , &n);
    for(int i = 0 ; i<n ; ++i) scanf("%d" , &arr[i]);
    for(int i = 0 ; i<n-1 ; ++i)
    {
        int u,v;
        scanf("%d%d" , &u , &v);
        --u , --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(0);
    BS = 300;
 
    len = (n-1)/BS + 1;
    for(int i = 0 ; i<len ; ++i) updateAllBlock(0 , 0 , 0);
 
    solve(0);
    for(int i = 0 ; i<n ; ++i) printf("%d%c" , ans[i] , " \n"[i+1 == n]);
    return 0;
}