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

vector<vi> adj, V;
int n, m;
vector<bool> vis;

void dfs(int u, int c){
	if(vis[u]) return;
	vis[u] = true;
	V[c].pb(u);
	for(int v : adj[u]) dfs(v, c ^ 1);
}

void tc(){
	adj.clear(), V.clear(), vis.clear();
	scanf("%d %d", &n, &m);
	V.resize(2);
	adj.resize(n+1);
	vis.resize(n+1, false);
	loop(e, m){
		int a, b; scanf("%d %d", &a, &b);
		adj[a].pb(b);
		adj[b].pb(a);
	}
	dfs(1, 0);
	vi & res = V[sz(V[1]) < sz(V[0])];
	printf("%d\n", sz(res));
	for(int u : res) printf("%d ", u);
	puts("");
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--) tc();
	return 0;
}
