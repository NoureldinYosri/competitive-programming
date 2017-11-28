#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define popcnt(x) __builtin_popcountll(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
using namespace std;

const int MAX = 1 << 20;
vi G[MAX];
int P[MAX],n;
ll f[MAX];
int depth[MAX],siz[MAX],pref_child[MAX];
int hld_id[MAX],hld_siz[MAX],hld_head[MAX],hld_cnt;
int dfs_in[MAX],dfs_out[MAX],dfs_time;
ll ST[MAX << 2];
int LA[MAX << 2];
vi L[MAX << 2];

void dfs(int u){
	depth[u] = depth[P[u]]  + 1;
	L[depth[u]].pb(u);
	siz[u] = 1;
	pref_child[u] = 0;
	for(int v : G[u]) {
		dfs(v);
		siz[u] += siz[v];
		if(siz[v] > siz[pref_child[u]]) pref_child[u] = v;
	}
}

void hld(int u){
	dfs_in[u] = ++dfs_time;
	hld_id[u] = hld_cnt;
	if(!hld_siz[hld_cnt]) hld_head[hld_cnt] = u;
	hld_siz[hld_cnt]++;

	if(pref_child[u]) hld(pref_child[u]);

	for(int v : G[u]) if(v != pref_child[u]) {
		++hld_cnt;
		hld(v);
	}
	dfs_out[u] = dfs_time;
}

void update(int node,int s,int e,int l,int r){
	ST[node] += r - l + 1;
	if(l <= s && e <= r) {
		LA[node]++;
		return ;
	}
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(r <= m) update(left,s,m,l,r);
	else if(m < l) update(right,m+1,e,l,r);
	else update(left,s,m,l,m),update(right,m+1,e,m+1,r);
}

ll query(int node,int s,int e,int l,int r){
	if(l <= s && e <= r) return ST[node];
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	ll ret = 0;
	if(r <= m) ret = query(left,s,m,l,r) + LA[node] * (r - l + 1LL);
	else if(m < l) ret = query(right,m+1,e,l,r) + LA[node] * (r - l + 1LL);
	else ret = query(left,s,m,l,m) + query(right,m+1,e,m+1,r) + LA[node] * (r - l + 1LL);
	return ret;
}

void add(int u){
	while(u){
		int id = hld_id[u],head = hld_head[id];
		update(1,1,n,dfs_in[head],dfs_in[u]);
		u = P[head];
	}
}

ll query(int u) {
	ll ret = 0;
	while(u) {
		int id = hld_id[u],head = hld_head[id];
		ret += query (1,1,n,dfs_in[head],dfs_in[u]);
		u = P[head];

	}
	return ret;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d",&n);
	int root = 0;
	range(i,1,n) {
		scanf("%d",P + i);
		if(!P[i]) root = i;
		G[P[i]].pb(i);
	}
	dfs(root);
	hld(root);

	range(l,1,n) {
		for(int u : L[l])
			add(u);
		for(int u : L[l])
			f[u] = query(u);
	}
	range(i,1,n) printf("%lld%c",f[i] - depth[i]," \n"[i==n]);
	return 0;
}
