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

int n, m;
int A[1 << 20], B[1 << 20];
vector<tuple<int, int, int>> ORs;


int NOT(int x) {
	return x ^ 1;
}

vector<vi> G, rG;


void addEdge(int a, int b) {
	G[a].push_back(b);
	cerr << a << " " << b << endl;
	rG[b].push_back(a);
}

void addOR(int i, int j) {
	addEdge(NOT(i), j);
	addEdge(NOT(j), i);
}

void addNOR(int i, int j) {
	addOR(i, NOT(j));
	addOR(NOT(i), j);
}

void build(int b) {
	G.clear();
	rG.clear();
	G.resize(2*n);
	rG.resize(2*n);
	for(auto [i, j, v] : ORs) {
		i = (i << 1) | 1;
		j = (j << 1) | 1;
		v = (v >> b) & 1;
		if(v) addOR(i, j);
		if(!v) addNOR(i, j);
	}
	for(auto & V : G) {
		sort(all(V));
	}
	for(auto & V : rG) {
		sort(all(V));
	}
}

bool vis[1 << 20];
vi ord;
int scc[1 << 20];

void dfs(int u) {
	if(vis[u]) return;
	vis[u] = true;
	for(int v : rG[u]) if(!vis[u]) dfs(v);
	ord.push_back(u);
}

void dfs(int u, int id) {
	if(vis[u]) return;
	scc[u] = id;
	vis[u] = true;
	for(int v : G[u]) if(!vis[u]) dfs(v, id);
}
void solve(int b) {
	cerr << "build" << endl;
	build(b);
	cerr << "solve" << endl;
	ord.clear();
	int N = n << 1;
	fill(vis, vis + N, false);
	cerr << "get order" << endl;
	loop(i, N) if(!vis[i]) dfs(i);
	reverse(all(ord));
	fill(vis, vis + N, false);
	int z = 0;
	cerr << "get components" << endl;
	for(int u : ord) if(!vis[u]) {
		dfs(u, z++);
	}
	cerr << "form answer" << endl;
	loop(i, n) {
		int v = scc[i << 1] > scc[(i << 1) | 1];
		A[i] |= v << b;
	}
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d", &n, &m);
	ORs.resize(m);
	for(auto & [i, j, v] : ORs) {
		scanf("%d %d %d", &i, &j, &v);
		i--, j--;
	}	
	// for(int b = 29; b >= 0; b--)
	// 	solve(b);
	solve(1);

	loop(i, n) printf("%d ", A[i]);
	puts("");
	return 0;
}
