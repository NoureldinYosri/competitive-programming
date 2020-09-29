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

vector<vi> adj;
int n, a, b, da, db;

int dfs(int u, int p, int t){
	if(u == t) return 0;
	for(int v : adj[u]) if(v != p){
		int ret = dfs(v, u, t);
		if(ret != -1) return ret + 1;
	}
	return -1;
}

pi dfs(int u, int p){
	int mx1 = 0, mx2 = 0, diameter = 0;
	for(int v : adj[u]) if(v != p){
		auto [h, sd] = dfs(v, u);
		h += 1;
		mx2 = max(mx2, h);
		if(mx2 > mx1) swap(mx1, mx2);
		diameter = max(diameter, sd);
	}
	diameter = max(diameter, mx1 + mx2);
	return pi(mx1, diameter);
}

void tc(){
	scanf("%d %d %d %d %d", &n, &a, &b, &da, &db);
	adj.clear();
	adj.resize(n+1);
	loop(e, n-1){
		int u, v; scanf("%d %d", &u, &v);
		adj[u].pb(v);
		adj[v].pb(u);
	}
	if(db <= 2*da) {
		puts("Alice");
		return;
	}
	if(dfs(a, 0, b) <= da) {
		puts("Alice");
		return;
	}
	auto [_, D] = dfs(1, 0);
	if(D <= 2*da) {
		puts("Alice");
		return;
	}
	puts("Bob");
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--) tc();	
	return 0;
}
