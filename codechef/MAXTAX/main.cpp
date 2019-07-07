#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
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
using namespace std;


const int MAXV = 100*1000 + 10,mod = 1000000021;
vi G[MAXV],rG[MAXV],ord;
vi SCC[MAXV],SCC_adj[MAXV];
int n,m,K,SCC_cnt;
int B[MAXV];
int vis[MAXV],ID[MAXV];
long long dp[MAXV][201];


void read(){
	scanf("%d %d %d",&n,&m,&K);
	for(int i = 1;i <= n;i++) {
		G[i].clear();
		rG[i].clear();
		scanf("%d",B + i);
	}
	loop(e,m) {
		int a,b;
		scanf("%d %d",&a,&b);
		G[a].pb(b);
		rG[b].pb(a);
	}
}

void dfs(int u,int id) {
	SCC[id].pb(u);
	vis[u] = 1;
	ID[u] = id;
	for(int v : G[u])
		if(!vis[v])
			dfs(v,id);
}

void topoSort(int u,vi *graph) {
	vis[u] = 1;
	for(int v : graph[u])
		if(!vis[v])
			topoSort(v,graph);
	ord.pb(u);
}

void findSCC() {
	fill(vis,vis + n + 1,0);
	ord.clear();
	for(int i = 1;i <= n;i++)
		if(!vis[i])
			topoSort(i,rG);
	reverse(all(ord));
	fill(vis,vis + n + 1,0);
	SCC_cnt = 0;
	for(int u : ord)
		if(!vis[u]){
			SCC[SCC_cnt].clear();
			SCC_adj[SCC_cnt].clear();
			dfs(u,SCC_cnt++);
		}
}

void compress(){
	loop(i,SCC_cnt){
		vi & aux = SCC_adj[i];
		aux.clear();
		for(int u : SCC[i])
			for(int v : G[u])
				if(ID[v] != i)
					aux.push_back(ID[v]);
		sort(all(aux));
		aux.resize(unique(all(aux)) - aux.begin());
	}
	loop(k,SCC_cnt) {
		vi & aux = SCC[k];
		for(int i = 0;i < sz(aux);i++)
			aux[i] = B[aux[i]];
		sort(all(aux));
	}
}

ll solve(int u,int K) {
	ll & ret = dp[u][K];
	if(ret != -1) return ret;
	ret = 0;
	const vi & aux = SCC[u];
	for(int i = 0;i <= K && i < sz(aux);i++) {
		ll tmp = (sz(aux)-i+0LL)*aux[i];
		ret = max(ret,tmp);
		for(int v : SCC_adj[u])
			ret = max(ret,solve(v,K-i) + tmp);
	}
	return ret;
}


ll f(int u,int k,int i) {
	const vi & aux = SCC[u];
	ll tmp = (sz(aux)-i+0LL)*aux[i];
	ll tmp2 = 0;
	for(int v : SCC_adj[u])
		tmp2 = max(tmp2,dp[v][k-i]);
	return tmp + tmp2;
}

void DC(int u,int s,int e,int l,int r) {
	if(s > e) return;
	int k = (s + e) >> 1;
	const vi & aux = SCC[u];
	int besti = l;
	ll ret = 0;
	for(int i = max(l-25,0);i <= k && i <= r+25 && i < sz(aux);i++) {
		ll tmp = (sz(aux)-i+0LL)*aux[i];
		ll tmp2 = 0;
		for(int v : SCC_adj[u])
			tmp2 = max(tmp2,dp[v][k-i]);
		if(tmp+tmp2 > ret){
			ret = tmp + tmp2;
			besti = i;
		}
	}
	dp[u][k] = ret;
	DC(u,s,k-1,l,besti);
	DC(u,k+1,e,besti,r);
}

void buildTable(){
	ord.clear();
	fill(vis,vis + SCC_cnt,0);
	loop(i,SCC_cnt)
		if(!vis[i])
			topoSort(i,SCC_adj);


	for(int u : ord){
//		print(SCC[u],int);
		DC(u,0,K,0,K);
//		prArr(dp[u],K+1,int);
	}
}

void solve(){
	findSCC();
	compress();
	buildTable();
	ll ans = 0;
	for(int i = 0;i < SCC_cnt;i++)
		ans = max(ans,dp[i][K]);
	ans %= mod;
	printf("%lld\n",ans);
}


int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	int T; scanf("%d",&T);
	while(T--) {
		read();
		solve();
	}
	return 0;
}
