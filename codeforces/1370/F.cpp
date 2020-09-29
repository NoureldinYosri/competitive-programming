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
vector<vi> G;
vi vis, parent,  depth;
map<vi, pi> mem;

void init(){
	mem.clear();
	G.clear();
	vis.clear();
	parent.clear();
	depth.clear();
	
	G.resize(n+1);
	parent.resize(n+1);
	vis.resize(n+1, 0);
	depth.resize(n + 1, 0);
}

pi ask(vi V){
	if(mem.count(V)) return mem[V];
	printf("? %d", sz(V));
	for(int v : V) printf(" %d", v);
	puts("");
	fflush(stdout);
	int u, d; scanf("%d %d", &u, &d);
	if(u == -1 && d == -1) exit(0);
	return mem[V] = pi(u, d);
}

void answer(int u, int v){
	printf("! %d %d\n", u, v);
	fflush(stdout);
	static char buffer[100];
	scanf("%s", buffer);
	if(buffer[0] == 'I') exit(0);
}

vi leaves;

void dfs(int u, int p, int D, int d){
	vis[u] = D < 0;
	parent[u] = p;
	depth[u] = d;
	bool is_leaf = 1;
	for(int v : G[u]) if(v != p) {
		dfs(v, u, D - 1, d + 1);
		is_leaf = 0;
	}
//	cerr << "\t" << u << " " << is_leaf << endl;
	if(is_leaf) leaves.pb(u);
}

void solve(){
	static vi V;
	V.clear();
	loop(i, n) V.pb(i+1);
	auto [root, D] = ask(V);

	leaves.clear();
	dfs(root, 0, D, 0);

	static vi ans;
		
	if (sz(G[root]) == 1) {
		ans.clear();
		for(int i = 1; i <= n; i++) if(depth[i] == D) ans.pb(i);
		auto [u, _] = ask(ans);
		answer(root, u);				
	} else {
		int s = 1, e = (D+1)>>1;
		while(s < e) {
			int m = s + (e-s+1)/2;
			ans.clear();
			for(int i = 1; i <= n; i++) if(depth[i] == m) ans.pb(i);
			if(ans.empty()) e = m - 1;
			else {
				auto [_, l] = ask(ans);
				if(l == D) s = m;
				else e = m - 1; 
			}
		}
		ans.clear();
		for(int i = 1; i <= n; i++) if(depth[i] == s) ans.pb(i);
		auto [a, _1] = ask(ans);
		
		dfs(a, 0, D, 0);
		ans.clear();
		for(int i = 1; i <= n; i++) if(depth[i] == D) ans.pb(i);
		auto [b, _2] = ask(ans);
		answer(a, b);
	}

}

int main(){
	int T; scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		init();
		loop(e, n-1){
			int a, b; scanf("%d %d", &a, &b);
			G[a].pb(b);
			G[b].pb(a);
		}
		solve();
	}
	return 0;
}
