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

const int MAX = 100*1000 + 10;
vi G[MAX];
int n;
int h[MAX][2];


bool dfs(int u, int p, int d){
	if(sz(G[u]) == 1){
		assert(p);
		h[u][d] = 1;
		return 0;
	}
	bool ret = 0;
	for(int v : G[u]) if(v != p){
		ret |= dfs(v, u, d ^ 1);
		loop(i, 2) ret |= h[u][i] && h[v][i^1];
		loop(i, 2) h[u][i] |= h[v][i];
	}
	return ret;
}

int dfs(int u, int p){
	int ret = 0;
	bool has_leafs = 0;
	for(int v : G[u]) if(v != p) {
		if(sz(G[v]) == 1) has_leafs = 1;
		else ret += dfs(v, u) + 1;
	}
	ret += has_leafs;
	return ret;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d", &n);
	loop(e, n-1){
		int a, b; scanf("%d %d", &a, &b);
		G[a].pb(b);
		G[b].pb(a);
	}
	int root = 0;
	for(int u = 1; u <= n;u++) if(sz(G[u]) > 1) {
		root = u;
		break;
	}
	int mn = 1;
	if(dfs(root, 0, 0)) mn = 3;
	int mx = dfs(root, 0);
	cout << mn << " " << mx << endl;
	return 0;
}
