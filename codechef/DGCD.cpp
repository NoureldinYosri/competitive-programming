#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

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

const int MAX = 50000 + 10;
vi G[MAX];
int dfs_in[MAX], dfs_out[MAX], pref_child[MAX], dfs_time, siz[MAX], depth[MAX], parent[MAX];
int h_cnt, heavy_head[MAX], heavy_id[MAX];
int n;
int A[MAX];
int val[2][MAX];

int BIT[MAX];

void add(int p, int v){
	for(++p; p <= n; p += LSOne(p))
		BIT[p] += v;
}
int get(int p){
	int ret = 0;
	for(++p; p; p ^= LSOne(p))
		ret += BIT[p];
	return ret;
}

inline void dfs(int u, int p){
	pref_child[u] = -1;
	siz[u] = 1;
	depth[u] = 1 + (u ? depth[p] : 0);
	parent[u] = p;
	
	for(int v : G[u]) if(v != p) {
		dfs(v, u);
		siz[u] += siz[v];
		if(pref_child[u]==-1 || siz[v] > siz[pref_child[u]]) pref_child[u] = v;
	}
}

inline void hld(int u, int p){
	val[0][dfs_time] = A[u];
	val[1][dfs_time] = u ? (A[u] - A[p]) : 0;
	dfs_in[u] = dfs_time++;
	heavy_id[u] = h_cnt;
	if(heavy_head[h_cnt] == -1) heavy_head[h_cnt] = u;
	
	if(pref_child[u] != -1) hld(pref_child[u], u);
	
	for(int v : G[u]) if(v != p && v != pref_child[u]){
		h_cnt++;
		hld(v, u);
	}
	dfs_out[u] = dfs_time-1;
}

int ST_val[1 << 20];
int ST_gcd[1 << 20];


inline void build(int cur, int s, int e, int *V, int *ST, function<void(int, int*)> push_up){
	if(s == e){
		ST[cur] = V[s];
		return;
	}
	int m = (s + e) >> 1, left = 2*cur + 1, right = left + 1;
	build(left, s, m, V, ST, push_up);
	build(right, m+1, e, V, ST, push_up);
	push_up(cur, ST);
}

inline int gcd(int a, int b){
	assert(min(a, b) >= 0);
	if(max(a, b) == 0) return 0;
	return __gcd(a, b);
}

auto push_up_gcd = [](int cur, int *ST){
	int left = 2*cur + 1, right = left + 1;
	int a = abs(ST[left]), b = abs(ST[right]);
	if(a < b) swap(a, b);
	ST[cur] = gcd(a, b);
};


inline void update(int cur, int s, int e, int l, int r, int v, int *ST, function<void(int, int*)> push_up){
	assert(l <= r);
	if(l <= s && e <= r){
		ST[cur] += v;
		return;
	}
	int m = (s + e) >> 1, left = 2*cur + 1, right = left + 1;
	if(r <= m) update(left, s, m, l, r, v, ST, push_up);
	else if(m < l) update(right, m+1, e, l, r, v, ST, push_up);
	else {
		update(left, s, m, l, m, v, ST, push_up);
		update(right, m+1, e, m+1, r, v, ST, push_up);
	}
	push_up(cur, ST);
}
/*
inline int query(int cur, int s, int e, int p){
	if(s == e) return ST_val[cur];
	int m = (s + e) >> 1, left = 2*cur + 1, right = left + 1;
	if(p <= m) return ST_val[cur] + query(left, s, m, p);
	else return ST_val[cur] + query(right, m+1, e, p);
}
*/
inline int query(int cur, int s, int e, int l, int r){
	assert(l <= r);
	if(l <= s && e <= r) return abs(ST_gcd[cur]);
	int m = (s + e) >> 1, left = 2*cur + 1, right = left + 1;
	if(r <= m) return query(left, s, m, l, r);
	if(m < l) return query(right, m+1, e, l, r);
	return gcd(query(left, s, m, l, m), query(right, m+1, e, m+1, r));
}

inline void update(int a, int b, int v){
	while(heavy_id[a] != heavy_id[b]){
		if(heavy_id[a] > heavy_id[b]) swap(a, b);
		int h = heavy_head[heavy_id[b]];
		
		int pc = pref_child[b];
		if(pc != -1)
			update(0, 0, n-1, dfs_in[pc], dfs_in[pc], -v, ST_gcd, push_up_gcd);
		
//		update(0, 0, n-1, dfs_in[h], dfs_in[b], v, ST_val, push_up_val);
		add(dfs_in[h], v);
		add(dfs_in[b]+1, -v);
		
		b = parent[h];
	}
	
	if(depth[a] > depth[b]) swap(a, b);
	int pc = pref_child[b];
	if(pc != -1)
		update(0, 0, n-1, dfs_in[pc], dfs_in[pc], -v, ST_gcd, push_up_gcd);
//	update(0, 0, n-1, dfs_in[a], dfs_in[b], v, ST_val, push_up_val);
	add(dfs_in[a], v);
	add(dfs_in[b]+1, -v);
	update(0, 0, n-1, dfs_in[a], dfs_in[a], v, ST_gcd, push_up_gcd);
}

inline int query(int a, int b){
	int g = 0;
	while(heavy_id[a] != heavy_id[b]){
		if(heavy_id[a] > heavy_id[b]) swap(a, b);
		int h = heavy_head[heavy_id[b]];
		

		if(h != b) {
			int tmp = query(0, 0, n - 1, dfs_in[h]+1, dfs_in[b]);
			g = gcd(tmp, g);
		}
		
		int x = get(dfs_in[h]);
		int y = get(dfs_in[parent[h]]);
		g = gcd(g, abs(x-y));
		
		b = parent[h];
	}
	
	if(depth[a] > depth[b]) swap(a, b);
	if(a != b) {
		int tmp = query(0, 0, n - 1, dfs_in[a]+1, dfs_in[b]);
		g = gcd(tmp, g);
	}
	
	int x = get(dfs_in[a]);
	g = gcd(g, x);
	
	return g;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	memset(heavy_head, -1, sizeof heavy_head);
	scanf("%d", &n);
	loop(i, n-1){
		int a, b; scanf("%d %d", &a, &b);
		G[a].pb(b);
		G[b].pb(a);
	}
	loop(i, n) scanf("%d", A + i);
	dfs(0, -1);
	hld(0, -1);
	
	for(int i = 0, prv = 0; i < n; i++){
		add(i, val[0][i] - prv);
		prv = val[0][i];
	}
	build(0, 0, n-1, val[1], ST_gcd, push_up_gcd);
	
	int m; scanf("%d", &m);
	while(m--){
		char c; int u, v;
		scanf(" %c %d %d", &c, &u, &v);
		if(c == 'F') printf("%d\n", query(u, v));
		else {
			int d; scanf("%d", &d);
			update(u, v, d);
		}
	}
	return 0;
}
