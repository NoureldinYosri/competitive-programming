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
unordered_set<int> adj[MAX];
int n, m;
int val[MAX], deg[MAX];

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n;i++) scanf("%d", val + i);
	loop(e, m){
		int a, b; scanf("%d %d", &a, &b);
		G[a].pb(b);
		G[b].pb(a);
		adj[a].insert(b);
		adj[b].insert(a);
		deg[a]++;
		deg[b]++;
	}
	auto cmp = [](const int & a, const int &b){
		return tie(deg[a], a) > tie(deg[b], b);
	};
//	prArr(deg + 1, n, int);
	ll ans = 0;
	for(int u = 1; u <= n; u++){
		sort(all(G[u]), cmp);
		while(!G[u].empty() && cmp(u, G[u].back())) G[u].pop_back();
//		print(G[u], int);
		loop(j, sz(G[u])) loop(i, j){
			int a = G[u][i], b = G[u][j];
			if(adj[a].find(b) != adj[a].end()) {
			//	cout << u << " " << a << " " << b << endl;
				ans += max(val[u], max(val[a], val[b]));
			}
		}
	}
	cout << ans << endl;
	return 0;
}