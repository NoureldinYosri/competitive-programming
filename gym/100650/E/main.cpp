#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define popcnt(x) __builtin_popcountll(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
using namespace std;

const ll oo = 1LL << 60;
int fr[20],to[20]; ll cost[20];
int n,m;
ll dp[20][1 << 20];
int adj[20][20],dfs_num[20],dfs_low[20],dfs_time;

bool dfs(int u,int p){
	dfs_num[u] = dfs_low[u] = dfs_time++;
	for(int v = 0;v < n;v++) if(adj[u][v] && v != p) {
		if(dfs_num[v] == -1) {
			if(dfs(v,u)) return 1;
			if(dfs_low[v] > dfs_num[u]) return 1;
			dfs_low[u] = min(dfs_low[v],dfs_low[u]);
		}
		else dfs_low[u] = min(dfs_low[u],dfs_num[v]);
	}
	return 0;
}

bool done(int msk){
	memset(adj,0,sizeof adj);
	loop(e,m) if(msk & (1 << e)) adj[fr[e]][to[e]] = adj[to[e]][fr[e]] = 1;
	dfs_time = 0;
	memset(dfs_num,-1,sizeof dfs_num);
	if(dfs(0,-1)) return 0;
	loop(i,n) if(dfs_num[i] == -1) return 0;
	return 1;
}

ll solve(int cur,int msk){
	if(cur == m) return done(msk) ? 0 : oo;
	if(dp[cur][msk] != -1) return dp[cur][msk];
	ll & ret = dp[cur][msk];
	ret = solve(cur + 1,msk);
	ret = min(ret,solve(cur + 1,msk | (1 << cur)) + cost[cur]);
	return ret;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	for(int case_num = 1;scanf("%d %d",&n,&m) == 2 && !(n == 0 && m == 0);case_num++){
		loop(e,m) {
			scanf("%d %d %lld",fr + e,to + e,cost + e);
			fr[e]--,to[e]--;
		}
		memset(dp,-1,sizeof dp);
		ll ans = solve(0,0);
		if(ans >= oo) printf("There is no reliable net possible for test case %d.\n",case_num);
		else printf("The minimal cost for test case %d is %lld.\n",case_num,ans);
	}
	return 0;
}
