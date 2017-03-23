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

const int MAX = 100*1000 + 10;
vi G[MAX];
int val[MAX],nxt[MAX];
int ord[MAX],dfs_time,n,K;
ll dp[MAX][201];
const ll NINF = -(1LL << 60);

void dfs(int u,int p){
	nxt[u] = dfs_time - 1;
	for(int v : G[u]) if(v != p) {
		nxt[v] = dfs_time;	
		dfs(v,u);
	}
	ord[dfs_time++] = u;
}


ll solve(int pos,int k){
	if(pos == -1) return 0;
	if(dp[pos][k] != -1) return dp[pos][k];
	int u = ord[pos];
	dp[pos][k] = (k ? solve(nxt[u],k - 1) : NINF);
	dp[pos][k] = max(dp[pos][k],val[u] + solve(pos - 1,k));
	return dp[pos][k];
}

int main(){
	scanf("%d %d",&n,&K);
	range(i,1,n) scanf("%d",val + i);
	loop(i,n-1){
		int a,b; scanf("%d %d",&a,&b);
		G[a].pb(b);
		G[b].pb(a);
	}
	dfs(1,0);
	memset(dp,-1,sizeof dp);
	cerr << solve(n-1,K) << endl;
	cout << solve(n-1,K) << endl;	
	
	return 0;
}
