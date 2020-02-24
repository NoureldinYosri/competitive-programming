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
 
const int MAXN = 200*1000 + 10;
int fr[MAXN], to[MAXN], n;
vi E[MAXN];
int weight[MAXN], strength[MAXN], D[MAXN];
ll subtree_weight[MAXN];
int inE[MAXN];
int pref_child[MAXN];
int siz[MAXN];
int dfs_in[MAXN], dfs_out[MAXN], dfs_time, euler[MAXN];


int head[MAXN], heavy_id[MAXN], heavy_siz[MAXN], heavy_cnt;


void dfs(int u, int p){
	
	subtree_weight[u] = 0;
	siz[u] = 1;
	for(int e : E[u]){
		int v = fr[e] + to[e] - u;
		if(v == p) continue;
		fr[e] = u;
		to[e] = v;
		inE[v] = e;
		dfs(v, u);
		D[e] = min(weight[e] - 1, strength[e]);
		weight[e] -= D[e];
		strength[e] -= D[e];
		ll diff = max(subtree_weight[v] - strength[e], 0LL);
		if(diff > D[e]){
			puts("-1");
			exit(0);
		}
		D[e] -= diff;
		weight[e] += diff;
		strength[e] += diff;
		assert(strength[e] >= subtree_weight[v]);
		subtree_weight[u] += weight[e] + subtree_weight[v];
		siz[u] += siz[v];
		if(siz[v] > siz[pref_child[u]]) pref_child[u] = v;
	}
}
 

void hld(int u, int p){
	euler[dfs_time] = u;
	dfs_in[u] = dfs_time++;
	
	if(!head[heavy_cnt]) head[heavy_cnt] = u;
	heavy_siz[heavy_cnt] ++;
	heavy_id[u] = heavy_cnt;
	
	if(pref_child[u]) hld(pref_child[u], u);
	
	for(int e : E[u]) {
		if(fr[e] != u) continue;
		if(to[e] == p || to[e] == pref_child[u]) continue;
		heavy_cnt++;
		hld(to[e], u);
	}	
	
	dfs_out[u] = dfs_time;
}


ll ST[1 << 20], LA[1 << 20];

void update(int cur, ll v){
	ST[cur] += v;
	LA[cur] += v;
	assert(ST[cur] >= 0);
}

void push_down(int cur){
	if(!LA[cur]) return;
	int left = 2*cur + 1, right = left+1;
	update(left, LA[cur]);
	update(right, LA[cur]);
	LA[cur] = 0;
}

void push_up(int cur){
	int left = 2*cur + 1, right = left+1;
	ST[cur] = min(ST[left], ST[right]);
	LA[cur] = 0;
}

void update(int cur, int s, int e,int l, int r, ll v){
	if(l <= s && e <= r) return update(cur, v);
	push_down(cur);
	int m = (s + e) >> 1, left = 2*cur + 1, right = left+1;
	if(r <= m) update(left, s, m, l, r, v);
	else if(m < l) update(right, m+1, e, l, r, v);
	else {
		update(left, s, m, l, m, v);
		update(right, m+1, e, m+1, r, v);
	}
	push_up(cur);
}

ll query(int cur, int s, int e, int l, int r){
	if(l <= s && e <= r) return ST[cur];
	push_down(cur);
	int m = (s + e) >> 1, left = 2*cur + 1, right = left+1;
	ll ret;
	if(r <= m) ret = query(left, s, m, l, r);
	else if(m < l) ret = query(right, m+1, e, l, r);
	else ret = min(query(left, s, m, l, m), query(right, m+1, e, m+1, r));
	push_up(cur);
	return ret;
}

ll query(int u){
	ll ret = LLONG_MAX;
	if(u == 1) return ret;
	while(heavy_id[u]){
		int id = heavy_id[u];
		int h = head[id];
		ret = min(ret, query(0, 0, n-1, dfs_in[h], dfs_in[u]));
		u = fr[inE[h]];
	}
	if(u != 1) {
		ret = min(ret, query(0, 0, n-1, dfs_in[1]+1, dfs_in[u]));
	}
	return ret;
}
void update_path(int u, ll v){
	if(u == 1) return;
	while(heavy_id[u]){
		int id = heavy_id[u];
		int h = head[id];
		update(0, 0, n-1, dfs_in[h], dfs_in[u], v);
		u = fr[inE[h]];
	}
	if(u != 1) update(0, 0, n-1, dfs_in[1]+1, dfs_in[u], v);
}

queue<int> q;
 
void bfs(){
	q.push(1);
	for(;!q.empty(); q.pop()){
		int u = q.front();
		for(int e : E[u]) if(fr[e] == u) {
			int v = to[e];
			q.push(v);
			ll d = min((ll)D[e], query(u));
			assert(d >= 0);
			strength[e] += d;
			weight[e] += d;
			update_path(u, -d);
			assert(strength[e] >= subtree_weight[v]);
			update(0, 0, n-1, dfs_in[v], dfs_in[v], strength[e] - subtree_weight[v]);
		}		
	}
}
 
int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d", &n);
	loop(e,n-1) {
		scanf("%d %d %d %d", fr+e, to+e, weight+e, strength+e);
		E[fr[e]].pb(e);
		E[to[e]].pb(e);
	}
	dfs(1, 0);
	hld(1, 0);
	bfs();
	printf("%d\n", n);
	loop(e, n-1) printf("%d %d %d %d\n", fr[e], to[e], weight[e], strength[e]);
	return 0;
}
