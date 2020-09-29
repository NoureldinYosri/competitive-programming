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

int n;
vector<vi> adj;
vi mx, siz;
vi cand;
vi depth;

void init(){
	adj.clear();
	mx.clear();
	siz.clear();
	siz.resize(n+1);
	mx.resize(n+1);
	adj.resize(n + 1);
	cand.clear();
	depth.clear();
	depth.resize(n+1);
}

void dfs(int u, int p){
	siz[u] = 1;
	mx[u] = 0;
	depth[u] = depth[p] + 1;
	for(int v : adj[u]) if(v != p){
		dfs(v, u);
		mx[u] = max(mx[u], siz[v]);
		siz[u] += siz[v];
	}
	mx[u] = max(mx[u], n - siz[u]);
	if(!cand.empty() && mx[u] < mx[cand[0]]) cand.clear();
	if(cand.empty() || mx[u] == mx[cand[0]]) cand.pb(u);
}

void tc(){
	scanf("%d", &n);
	init();
	loop(e, n-1){
		int a, b;
		scanf("%d %d", &a, &b);
		adj[a].pb(b);
		adj[b].pb(a);
	}
	dfs(1, 0);
	assert(sz(cand) <= 2);
	assert(!cand.empty());
	if(sz(cand) == 1){
		int v = adj[1].back();
		printf("1 %d\n1 %d\n", v, v);
	} else {
		int u = cand[0], v = cand[1];
		if(depth[u] > depth[v]) swap(u, v);
		int c = 0;
		for(int t : adj[v]) if(t != u) {
			if(siz[t] > siz[c]) c = t;
		}
		printf("%d %d\n", v, c);
		printf("%d %d\n", u, c);
	}
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--) tc();
	return 0;
}
