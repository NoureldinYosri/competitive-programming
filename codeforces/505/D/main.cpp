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
#define popcnt(x) __builtin_popcount(x)
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

const int MAXV = 100*1000 + 10,MAXE = 100*1000 + 10;
vi E[MAXE],ST;
int fr[MAXE],to[MAXE],weight[MAXE];
int dfs_in[MAXV],dfs_low[MAXV],dfs_time;
bool inStack[MAXV];
int id[MAXV],SCC_cnt,n;
vi SCC[MAXV],SCC_adj[MAXV];
vi SCC_rev[MAXV];
int lev[MAXV],vis[MAXV],dont[MAXE],num_e;
set<int> S;

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
		SCC_cnt++;
		while(!done){
			int v = ST.back();
			id[v] = SCC_cnt;
			SCC[id[v]].pb(v);
			ST.pop_back();
			done = v == u;
			inStack[v] = 0;
		}
	}
}

int compress(){
	vi aux;
	int ret = 0,e = 0;
	for(int i = 1;i <= SCC_cnt;i++){
		for(int u : SCC[i]){
			for(int e : E[u])
				if(id[to[e]] != i)
					aux.pb(id[to[e]]);
		}
		sort(all(aux));
		aux.resize(unique(all(aux)) - aux.begin());
		for(int v : aux) {
			fr[e] = i;
			to[e] = v;
			SCC_adj[i].pb(e);
			SCC_rev[v].pb(e);
			e++;
		}
		ret += sz(SCC[i]);
		fr[e] = 0;
		to[e] = i;
		SCC_adj[0].pb(e);
		dont[e] = 1;
		e++;
	}
	num_e = e;
	return ret;
}


void bfs(){
	queue<int> q;
	q.push(0);
	while(!q.empty()){
		int u = q.front(); q.pop();
		for(int e : SCC_adj[u]) {
			int v = to[e];
			if(!lev[v]) {
				lev[v] = lev[u] + 1;
				q.push(v);
			}
		}
	}
}

void dfs(int u){
	for(int e : SCC_rev[u]) {
		int v = fr[e];
		if(S.find(v) != S.end())
			dont[e] = 1;
	}

}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	int m; scanf("%d %d",&n,&m);
	memset(dfs_in,-1,sizeof dfs_in);
	loop(e,m) {
		scanf("%d %d",fr + e,to + e);
		E[fr[e]].pb(e);
	}
	for(int u = 1;u <= n;u++) if(dfs_in[u] == -1 && !E[u].empty()) {
//		cerr << "enter tarjan @" << u << endl;
		tarjanSCC(u);
		assert(ST.empty());
	}
	int ans = compress();
	bfs();
	dfs(0);
	loop(e,num_e) ans += !dont[e];
	cout << ans << endl;
	return 0;
}
