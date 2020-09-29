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
int n, m;
vi G[MAX];
int depth[MAX], siz[MAX], P[MAX];

void dfs(int u, int p){
	depth[u] = depth[p] + 1;
	siz[u] = 1;
	for(int v : G[u]) if(v != p) {
		dfs(v, u);
		siz[u] += siz[v];
	}
}

vi path;

int get_far(int u, int p){
	depth[u] = depth[p] + 1;
	P[u] = p;
	int c = u;
	for(int v : G[u]) if(v != p) {
		int g = get_far(v, u);
		if(depth[g] > depth[c]) c = g;
	}
	return c;
}

vi ord;

ll solve(int root){
//	cerr << "root is " << root <<  endl;
	dfs(root, 0);
	ord.clear();
	for(int u = 1; u <= n; u++)
		ord.pb(depth[u] - siz[u]);
//	prArr(depth + 1, n, int);
//	prArr(siz + 1, n, int);
//	print(ord, int);
	sort(all(ord));
	reverse(all(ord));
//	print(ord, int);
	ll ret=  0;
	loop(i, m) ret += ord[i];
	return ret;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d", &n, &m);
	loop(e, n-1){
		int a, b; scanf("%d %d", &a, &b);
		G[a].pb(b);
		G[b].pb(a);
	}
	cout << solve(1) << endl;
	
	
	return 0;
}
