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
#define pl pair<ll,ll>
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


const int MAX = 200*1000 + 10,MAXLG = 20,oo = 1 << 30;
int n,m;
int fr[MAX],to[MAX],cost[MAX],ord[MAX];
vi E[MAX];
int id[MAX],weight[MAX];
bool is_mst[MAX];
int dfs_in[MAX],dfs_out[MAX],dfs_time,siz[MAX],pref_child[MAX],depth[MAX],euler[MAX << 1];
int P[MAX][MAXLG],W[MAX][MAXLG];
int ans[MAX];
int heavy_head[MAX],heavy_id[MAX],heavy_siz[MAX],heavy_cnt;
int ST[MAX*8],LA[MAX*8];

int find(int a){
	return id[a] = (a == id[a]) ? a : find(id[a]);
}

void join(int a,int b){
	a = find(a),b = find(b);
	if(a == b) return;
	if(weight[a] < weight[b]) swap(a,b);
	id[b] = a;
	weight[a] += weight[b];
}


void get_mst(){
	range(i,1,n) id[i] = i,weight[i] = 1;
	sort(ord,ord + m,[](const int & a,const int & b){
		return cost[a] < cost[b];
	});
	loop(i,m) {
		int e = ord[i];
		int u = fr[e],v = to[e];
		if(find(u) == find(v)) continue;
		join(u,v);
		is_mst[e] = 1;
		E[u].pb(e);
		E[v].pb(e);
	}
//	loop(e,m) if(is_mst[e]) cerr << fr[e] << " " << to[e] << " " << cost[e] << endl;
}

void dfs(int u,int p,int w){
	siz[u] = 1;
	pref_child[u] = -1;
	P[u][0] = p;
	W[u][0] = w;
	depth[u] = depth[p] + 1;
	loop(i,MAXLG - 1) {
		P[u][i + 1] = P[P[u][i]][i];
		W[u][i + 1] = max(W[u][i],W[P[u][i]][i]);
	}
	for(int e : E[u]) {
		int v = fr[e] + to[e] - u;
		if(v == p) continue;
		dfs(v,u,cost[e] - 1);
		siz[u] += siz[v];
		if(pref_child[u] == -1 || siz[v] > siz[pref_child[u]]) pref_child[u] = v;
	}
}


void hld(int u,int p){
	euler[dfs_time] = oo;
	dfs_in[u] = dfs_time++;
	if(!heavy_siz[heavy_cnt]) heavy_head[heavy_cnt] = u;
	heavy_id[u] = heavy_cnt;
	heavy_siz[heavy_cnt]++;
	if(pref_child[u] != -1) hld(pref_child[u],u);
	for(int e : E[u]) {
		int v = fr[e] + to[e] - u;
		if(v == p || v == pref_child[u]) continue;
		heavy_cnt++;
		hld(v,u);
	}
	dfs_out[u] = dfs_time-1;
}

void update(int node,int s,int e,int l,int r,int v){
	if(l <= s && e <= r) {
		LA[node] = min(LA[node],v);
		ST[node] = min(ST[node],v);
		return;
	}
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(r <= m) update(left,s,m,l,r,v);
	else if(m < l) update(right,m+1,e,l,r,v);
	else update(left,s,m,l,m,v),update(right,m+1,e,m+1,r,v);
	ST[node] = min(ST[node],v);
}

int query(int node,int s,int e,int p){
	if(s == e) return ST[node];
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	int res = LA[node],r = oo;
	if(p <= m) r = query(left,s,m,p);
	else r = query(right,m+1,e,p);
	return res = min(res,r);
}

void update(int u,int p,int val) {
	while(heavy_id[u] != heavy_id[p]) {
		int id = heavy_id[u],head = heavy_head[id];
		int l = dfs_in[head],r = dfs_in[u];
		update(1,0,n-1,l,r,val);
		u = P[head][0];
	}
	if(u != p) {
		int l = dfs_in[p] + 1,r = dfs_in[u];
		update(1,0,n-1,l,r,val);
	}
}

bool inSubTree(int a,int b){
	return dfs_in[b] <= dfs_in[a] && dfs_in[a] <= dfs_out[b];
}

int lca(int a,int b){
	if(depth[a] > depth[b]) swap(a,b);
	if(inSubTree(b,a)) return a;
	int k = MAXLG - 1;
	while(a != b){
		if(depth[a] > depth[b]) swap(a,b);
		while(k && inSubTree(a,P[b][k])) k--;
		b = P[b][k];
	}
	return a;
}

int max_on_path(int u,int d){
	int r = 0;
	int mx = 0;
	while(d) {
		int t = LSOne(d);
		while(t != (1 << r)) r++;
		mx = max(mx,W[u][r]);
		d ^= t;
		u = P[u][r];
	}
	return mx;
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d",&n,&m);
	loop(i,m){
		scanf("%d %d %d",fr + i,to + i,cost + i);
		ord[i] = i;
	}
	get_mst();
	dfs(1,0,0);
	hld(1,0);
	dfs_out[0] = n;
	fill(ans,ans + m,-2);
	fill(ST,ST + 8*MAX,oo);
	fill(LA,LA + 8*MAX,oo);
	for(int e = 0;e < m;e++){
		int p = lca(fr[e],to[e]);
		int u = fr[e],v = to[e];
		if(!is_mst[e]) {
			ans[e] = max(max_on_path(u,depth[u] - depth[p]),max_on_path(v,depth[v] - depth[p]));
			update(u,p,cost[e] - 1);
			update(v,p,cost[e] - 1);
		}

	}
	for(int e = 0;e < m;e++){
		int u = fr[e],v = to[e];
		if(depth[u] > depth[v]) swap(u,v);
		if(is_mst[e]) {
			ans[e] = query(1,0,n-1,dfs_in[v]);
			if(ans[e] == oo) ans[e] = -1;
		}

	}
//	loop(e,m) printf("%d %d\n",ans[e],is_mst[e]);
	loop(e,m) printf("%d%c",ans[e]," \n"[e==m-1]);
	return 0;
}
