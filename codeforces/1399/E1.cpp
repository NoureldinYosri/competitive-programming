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

const int MAX = 1 << 20;
int siz[MAX], subtree[MAX];
ll cost[MAX], S;
int fr[MAX], to[MAX];
vector<vi> adj;
int n;

void dfs(int u, int p, int ie){
	subtree[u] = 0;
	int cnt = 0;
	for(int e : adj[u]) {
		int v = fr[e] + to[e] - u;
		if(v == p) continue;
		dfs(v, u, e);
		subtree[u] += subtree[v];
		cnt++;
	}
	subtree[u] += !cnt;
	if(ie != -1) siz[ie] = subtree[u];
}

void read(){
	scanf("%d %lld", &n, &S);
	adj.clear();
	adj.resize(n+1);
	loop(e, n-1){
		scanf("%d %d %lld", fr+e, to+e, cost + e);
		adj[fr[e]].pb(e);
		adj[to[e]].pb(e);
	}
}

void work(){
	dfs(1, -1, -1);
	ll tot = 0;
	set<pair<ll, int>> S;
	loop(e, n-1) {
//		cerr << pi(fr[e], to[e]) << " " << cost[e] << " " << siz[e] << endl;
		tot += cost[e] * siz[e];
		S.emplace(cost[e]*siz[e] - (cost[e] >> 1)*siz[e], e);
	}
	
	int ans = 0;
	while(tot > ::S){
		ans++;
		auto [_, e] = *S.rbegin();
		S.erase(*S.rbegin());
		tot -= cost[e]*siz[e] - (cost[e] >> 1)*siz[e];
		cost[e] >>= 1;
//		cerr << pi(fr[e], to[e]) << " " << cost[e] << " -> " << (cost[e] >> 1) << endl;
		ll damage = cost[e]*siz[e] - (cost[e] >> 1)*siz[e];
		S.emplace(damage, e);		
	}
	printf("%d\n", ans);
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--){
		read();
		work();
	}
	return 0;
}
