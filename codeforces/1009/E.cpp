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


const int MAXN = 1 << 20;
int cnt[MAXN];
int depth[MAXN], siz[MAXN], dfs_in[MAXN], dfs_out[MAXN], euler[MAXN], pref_child[MAXN], n, dfs_time;
vi G[MAXN];

void dfs(int u, int p){
	siz[u] = 1;
	depth[u] = depth[p] + 1;
	euler[dfs_time] = u;
	dfs_in[u] = dfs_time++;
	for(int v : G[u]) if(v != p){
		dfs(v, u);
		if(siz[v] > siz[pref_child[u]]) pref_child[u] = v;
		siz[u] += siz[v];
	}

	dfs_out[u] = dfs_time;
}

int ans[MAXN];
int D;
inline void insert(int d){
	cnt[d]++;
	if(cnt[d] > cnt[D]) D = d;
	else if(cnt[d] == cnt[D] && d < D) D = d;
}

void dsu(int u, int p, bool keep){
	for(int v : G[u]) if(v != p && v != pref_child[u]) dsu(v, u, 0);
	if(pref_child[u]) dsu(pref_child[u], u, 1);
	
	insert(depth[u]);
	for(int v : G[u]) if(v != p && v != pref_child[u]){
		for(int i = dfs_in[v]; i < dfs_out[v]; i++){
			int t = euler[i];
			insert(depth[t]);
		}
	}
	ans[u] = D - depth[u];
	
	if(!keep){
		for(int i = dfs_in[u]; i < dfs_out[u];i++){
			int t = euler[i];
			cnt[depth[t]] = 0;
		}
		D = 0;
	}
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d",&n);
	loop(e, n-1){
		int a, b; scanf("%d %d", &a, &b);
		G[a].pb(b);
		G[b].pb(a);
	}
	dfs(1, 0);
	dsu(1, 0, 0);
	for(int i = 1;i <= n;i++) printf("%d\n",ans[i]);
	return 0;
}
