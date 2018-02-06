#pragma GCC optimize ("O3")
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


const int MAXV = 500 + 10,MAXE = 100*1000 + 10;
vi E[MAXE],ST;
int fr[MAXE],to[MAXE],weight[MAXE];
int dfs_in[MAXV],dfs_low[MAXV],dfs_time;
bool inStack[MAXV];
int SCC_id[MAXV],SCC_cnt,n;
vi SCC[MAXV],SCC_adj[MAXV];
int vis[MAXV];
bool adj[MAXV][MAXV];

void tarjanSCC(int u) {
	dfs_in[u] = dfs_low[u] = dfs_time++;
	ST.pb(u);
	inStack[u] = true;
	for(int e : E[u]){
		int v = to[e];
		if (dfs_in[v] == -1) {
			tarjanSCC(v);
			dfs_low[u] = min(dfs_low[u], dfs_low[v]);
		}
		else if (inStack[v]) {
			dfs_low[u] = min(dfs_low[u], dfs_low[v]);
		}
	}
	if (dfs_low[u] == dfs_in[u]) {
		bool done = 0;
		while(!done){
			int v = ST.back();
			SCC_id[v] = SCC_cnt;
			SCC[SCC_id[v]].pb(v);
			ST.pop_back();
			done = v == u;
			inStack[v] = 0;
		}
		SCC_cnt++;
	}
}

int dfs(int u,int id,int f,int t) {
	if(vis[u] == 1) return 1;
	if(vis[u] == 2) return 0;
	vis[u] = 1;
	int ret = 0;
	for(int e : E[u]) {
		int v = to[e];
		if(SCC_id[v] != id) continue;
		if(f == u && t == v) continue;
		ret += dfs(v,id,f,t);
	}
	vis[u] = 2;
	return ret;
}


int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	int m;
	scanf("%d %d",&n,&m);
	loop(e,m) {
		scanf("%d %d",fr + e,to + e);
		E[fr[e]].pb(e);
		adj[fr[e]][to[e]] = 1;
	}
	fill(dfs_in,dfs_in + n + 1,-1);
	range(i,1,n) if(dfs_in[i] == -1) tarjanSCC(i);

	vi C1;
	loop(i,SCC_cnt)
		if(sz(SCC[i]) > 1)
			C1.pb(i);
	if(sz(C1) > 1) return puts("NO"),0;
	if(sz(C1) == 0) return puts("YES"),0;

	int id = C1[0];
	vi indeg(n+1,0),I(n+1,0);

	for(int u : SCC[id])
		for(int e : E[u]) {
			int v = to[e];
			if(SCC_id[v] != id) continue;
			indeg[v]++;
			I[v] = u;
		}

	for(int v : SCC[id]){
		memset(vis,0,sizeof vis);
		if(indeg[v] == 1 && !dfs(v,id,I[v],v))
			return puts("YES"),0;
	}
	puts("NO");

	return 0;
}
