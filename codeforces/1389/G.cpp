#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
typedef std::vector<int> vi;
typedef std::pair<int,int> pi;
typedef std::vector<pi> vp;
typedef long long ll;
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
template<class A,class B>
std::ostream& operator << (std::ostream& st,const std::pair<A,B> p) {
	st << "(" << p.first << ", " << p.second << ")";
	return st;
}
using namespace std;

const int MAXN = 300*1000 + 10;
int n, m, K;
bool isSpecialNode[MAXN], isSpecialSuperNode[MAXN];
ll NodeProfit[MAXN], SuperNodeProfit[MAXN];
int fr[MAXN], to[MAXN], cost[MAXN]; bool fixedEdge[MAXN];
int dfs_num[MAXN], dfs_low[MAXN], dfs_time, NodeId[MAXN];
vi NodeAdj[MAXN], SuperNodeAdj[MAXN];
vi ST;
int N = 0;
vi Content[MAXN];

void compress(int root){
	while(!ST.empty() && ST.back() != root){
		int u = ST.back(); ST.pop_back();
		assert(NodeId[u] == -1 || NodeId[u] == N);
		NodeId[u] = N;
		Content[N].push_back(u);
	}
	if(Content[N].empty()) return;
	N++;
}

void getBridges(int u, int pe){
	dfs_num[u] = dfs_low[u] = dfs_time++;
	ST.push_back(u);
	for(int e : NodeAdj[u]) {
		int v = fr[e] + to[e] - u;
		if(dfs_num[v] == -1){
			getBridges(v, e);
			if(dfs_low[v] > dfs_num[u]){
				compress(u);
			}
			dfs_low[u] = min(dfs_low[u], dfs_low[v]);
			ST.push_back(u);
		} else if(pe != e){
			dfs_low[u] = min(dfs_low[u], dfs_num[v]);
		}
	}
}

int SpecialCount[MAXN];
ll subtreeSum[MAXN], f[MAXN], g[MAXN];

void dfs(int u, int p){
	SpecialCount[u] = isSpecialSuperNode[u];
	f[u] = subtreeSum[u] = SuperNodeProfit[u];
	
	
	for(int e : SuperNodeAdj[u]){
		int v = fr[e] + to[e] - u;
		if(v == p) continue;
		dfs(v, u);
		SpecialCount[u] += SpecialCount[v];		
		subtreeSum[u] += subtreeSum[v];
	}
	for(int e : SuperNodeAdj[u]){
		int v = fr[e] + to[e] - u;
		if(v == p) continue;
		if(SpecialCount[v] && K-SpecialCount[v]) {
			g[v] = max(f[v] - cost[e], 0LL);			
		} else {
			g[v] = f[v];
			if(SpecialCount[v] == 0) assert(f[v] == subtreeSum[v]);
		}
		f[u] += g[v];
	}
}

void dfs(int u, int p, ll fp){
//	cerr << u << " " << p << " " << fp << endl;
	f[u] += max(fp, 0LL);
	for(int e : SuperNodeAdj[u]){
		int v = fr[e] + to[e] - u;
		if(v == p) continue;
		ll cont = f[u] - g[v];
		if(SpecialCount[v] && K-SpecialCount[v]){
			cont -= cost[e];
		}
		dfs(v, u, cont);
	}	
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d %d", &n, &m, &K);
	loop(i, K){
		int v; scanf("%d", &v);
		isSpecialNode[v] = 1;
	}
	for(int i = 1; i <= n; i++) scanf("%lld", NodeProfit + i);
	loop(e, m) scanf("%d", cost + e);
	loop(e, m) {
		scanf("%d %d", fr + e, to + e);
		NodeAdj[fr[e]].pb(e);
		NodeAdj[to[e]].pb(e);
	}
	memset(dfs_num, -1, sizeof dfs_num);
	memset(NodeId, -1, sizeof NodeId);
	for(int i = 1; i <= n; i++) if(dfs_num[i] == -1) {
		getBridges(i, 0);
		compress(-1);
	}
	
	K = 0;
	loop(i, N){
		vi & V = Content[i];
		sort(all(V));
		V.resize(unique(all(V)) - V.begin());
//		print(V, int);
		for(int v : V){
			isSpecialSuperNode[i] |= isSpecialNode[v];
			SuperNodeProfit[i] += NodeProfit[v];
			for(int e : NodeAdj[v]) {
				if(!fixedEdge[e]) {
					fixedEdge[e] = true;
					fr[e] = NodeId[fr[e]];
					to[e] = NodeId[to[e]];
					if(fr[e] != to[e]) {
						SuperNodeAdj[fr[e]].pb(e);
						SuperNodeAdj[to[e]].pb(e);
					}
				} 
			}
		}
		K += isSpecialSuperNode[i];
/*		cerr << SuperNodeProfit[i] << " " << isSpecialSuperNode[i] << ": ";
		for(int e : SuperNodeAdj[i]){
			cerr << fr[e] + to[e] - i << " ";
		}
		cerr << endl;
*/	}
	
//	print(Content[0], int);
	dfs(0, -1);
//	prArr(NodeId+1, n, int);
//	prArr(f, N, ll);
//	prArr(g, N, ll);
	dfs(0, -1, 0);
	
	for(int i = 1; i <= n; i++) printf("%lld%c", f[NodeId[i]], " \n"[i==n]);
	
	return 0;
}
