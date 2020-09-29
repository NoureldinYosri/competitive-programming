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

const int MAXN = 100*1000 + 10;
vi G[MAXN];
int n;
ll sum[MAXN], residual[MAXN];
vp tail;
ll depth_offset[MAXN];
int dfs_in[MAXN], dfs_out[MAXN], dfs_time;
vi level[MAXN];

void dfs(int u, int p, int h){
	residual[u] = depth_offset[h];
	for(int v : G[u]) if(v != p){
		dfs(v, u, h + 1);
		residual[u] += residual[v];
	}
	sum[u] += residual[u];
}

void floodfill(int u, int p, int h){
	dfs_in[u] = dfs_time++;
	level[h].pb(dfs_in[u]);
	for(int v : G[u]) if(v != p) floodfill(v, u, h + 1);
	dfs_out[u] = dfs_time;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int m; scanf("%d %d", &n, &m);
	loop(e, n-1){
		int a, b; scanf("%d %d", &a, &b);
		G[a].pb(b);
		G[b].pb(a);
	}
	floodfill(1, 0, 0);
	int B = pow(n*0.5*m*log(2)/log(n), 1/3.);
	loop(i, m){
		int t; scanf("%d", &t);
		if(t == 1){
			int d, x; scanf("%d %d", &d, &x);
			tail.emplace_back(d, x);
			depth_offset[d] += x;
		}
		else {
			int u; scanf("%d", &u);
			ll ans = sum[u];
			for(auto [d, x] : tail){
				ll cnt = lower_bound(all(level[d]), dfs_out[u]) - lower_bound(all(level[d]), dfs_in[u]);
				//cerr << u << " @ " << d << " -> " << cnt << endl;
				ans += cnt * x;
			}
			printf("%lld\n", ans);
		}
		if(sz(tail) > B) {
			//cerr << "dfs" << endl;
			dfs(1, 0, 0);
			for(auto [d, _] : tail)
				depth_offset[d] = 0;
			tail.clear();
		}
	}
	
	
	
	return 0;
}
