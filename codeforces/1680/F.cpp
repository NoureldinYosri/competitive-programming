#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
using vi = std::vector<int>;
using pi = std::pair<int,int>;
using vp = std::vector<pi>;
using ll = long long;
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
template<class A,class B>
std::ostream& operator << (std::ostream& st,const std::pair<A,B> p) {
	st << "(" << p.first << ", " << p.second << ")";
	return st;
}
void tc();
auto test_cases = [](){
	int T; scanf("%d", &T);
	while(T--) tc();
};
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

vp E;
vector<vi> adj;
vi color;
int n, m;
int dont;
vi ST, cycle;

bool dfs(int u, int c) {
	if(color[u] != -1) {
		if(color[u] == c) return false;
		ST.clear();
		ST.push_back(u);
		cycle.clear();
		return true;
	}
	color[u] = c;
	for(int e : adj[u])  if(e != dont){
		auto [a, b] = E[e];
		int v = a + (b - a)*(a == u);
		if(dfs(v, c ^ 1)) {
			if(!(sz(ST) > 1 && ST[0] == ST.back())) {
				ST.push_back(u);
				cycle.push_back(e);
			}
			return true;
		}
	}
	return false;
}

bool bipartite(int ie = -1) {
	fill(all(color), -1);
	dont = ie;
	loop(i, n) {
		shuffle(all(adj[i]), rng);
	}
	return !dfs(0, 0);
}

void tc() {
	scanf("%d %d", &n, &m);
	E.resize(m);
	adj.clear(); adj.resize(n);
	color.resize(n);
	loop(e, m) {
		int a, b; scanf("%d %d", &a, &b);
		a--, b--;
		E[e] = pi(a, b);
		adj[a].push_back(e);
		adj[b].push_back(e);
	}
	if(bipartite()) {
		puts("YES");
		loop(i, n) putchar("01"[color[i]]);
		puts("");
		return;
	}
	set<int> badEdges{all(cycle)}, aux;
	loop(t, 50) {
		bipartite();
		aux.clear();
		set<int> tmp{all(cycle)};
		if(sz(cycle) > sz(badEdges)) {
			badEdges.swap(tmp);
		}
		for(int e : tmp) if(badEdges.count(e)) {
			aux.insert(e);
		}
		badEdges.swap(aux);
		if(sz(badEdges) <= 1) break;
	}
	if(badEdges.empty() || !bipartite(*badEdges.begin())) {
		puts("NO");
		return;
	}
	auto [a, b] = E[*badEdges.begin()];
	int flip = max(color[a], color[b]) == 0;
	puts("YES");
	loop(i, n) putchar("01"[color[i] ^ flip]);
	puts("");	
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	test_cases();
	return 0;
}
