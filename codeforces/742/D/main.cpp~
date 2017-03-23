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

const int MAX = 1 << 10;
int n,m,cap;
ll dp[MAX][MAX];
int W[MAX],B[MAX],vis[MAX],id[MAX];
int nxt[MAX],lst[MAX],ord[MAX],dfs_time,cnt;
ll SW[MAX],SB[MAX];
vi G[MAX];

void dfs(int u,int q){
	if(vis[u]) return;
	vis[u] = 1; 
	id[u] = q;
	SW[q] += W[u];
	SB[q] += B[u];
	lst[q] = u;
	ord[dfs_time++] = u;
	for(int v : G[u]) dfs(v,q);
}

ll solve(int p,int k){
	if(p == -1 || !k) return 0;
	if(dp[p][k] != -1) return dp[p][k];
	int u = ord[p];
	dp[p][k] = solve(p - 1,k);
	if(W[u] <= k) dp[p][k] = max(dp[p][k],solve(nxt[id[u]],k - W[u]) + B[u]);
	if(lst[id[u]] == u && SW[id[u]] <= k){
		dp[p][k] = max(dp[p][k],solve(nxt[id[u]],k - SW[id[u]]) + SB[id[u]]);
	}
	return dp[p][k];
}

int main(){
	scanf("%d %d %d",&n,&m,&cap);
	loop(i,n) scanf("%d",W + i + 1);
	loop(i,n) scanf("%d",B + i + 1);
	
	loop(i,m){
		int a,b; scanf("%d %d",&a,&b);
		G[a].pb(b);
		G[b].pb(a);
	}
	for(int i = 1;i <= n;i++) {
		nxt[cnt] = dfs_time - 1;
		dfs(i,cnt);
		cnt++;
	}
	assert(dfs_time == n);
	memset(dp,-1,sizeof dp);
	cout << solve(n-1,cap) << endl;
	
	return 0;
}
