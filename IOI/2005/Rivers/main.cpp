#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define point pair<double,double>
#define pl pair<ll,ll>
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

const int MAX = 101;
vi E[MAX];
int N,K;
int W[MAX],D[MAX];
ll sum[MAX];
vl dp[MAX][MAX][51];

void dfs(int u){
    for(int v : E[u]) {
        sum[v] = sum[u] + D[v];
        dfs(v);
    }
}
ll solve(int u,int lst,int ik,int idx){
    if(idx == sz(E[u])){
        if(idx == 0 && ik > 0) return 0;
        else return (sum[u] - sum[lst]) * W[u];
    }
    if(dp[u][lst][ik][idx] != -1) return dp[u][lst][ik][idx];
    ll ret = 1LL << 60;
    if(u != lst && idx == 0 && ik != 0) ret = solve(u,u,ik - 1,idx);
    int v = E[u][idx];
    for(int k = 0;k <= ik;k++)
        ret = min(ret,solve(u,lst,ik - k,idx + 1) + solve(v,lst,k,0));
    dp[u][lst][ik][idx] = ret;
    return ret;
}


int main(){
	scanf("%d %d",&N,&K);
	range(i,1,N){
		int p;
		scanf("%d %d %d",W + i,&p,D + i);
		E[p].pb(i);
	}
	loop(i,N+1) loop(j,N+1) loop(k,K + 1) dp[i][j][k] = vl(E[i].size(),-1);
	dfs(0);
	cerr << solve(0,0,K,0) << endl;
	cout << solve(0,0,K,0) << endl;
	
	return 0;
}
