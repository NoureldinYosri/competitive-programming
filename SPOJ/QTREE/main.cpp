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
#define popcnt(x) __builtin_popcount(x)
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

const int MAX = 2*10000 + 10,MAXLG = 20;
vi E[MAX];
int fr[MAX],to[MAX],weight[MAX],n;
int depth[MAX],siz[MAX],pref_child[MAX];
int dfs_in[MAX],dfs_out[MAX],dfs_time;
int head[MAX],hld_siz[MAX],hld_id[MAX],hld_cnt;
int euler[MAX],edge_euler[MAX],lst[MAX];
int sparse_table[MAX][MAXLG],lg[MAX];
int ST[MAX << 2],parent[MAX];
char command[50];

void clean(){
	fill(hld_siz,hld_siz + hld_cnt,0);
	hld_cnt = dfs_time = 0;
	range(i,1,n) E[i].clear();
}

void dfs(int u,int p){
	depth[u] = depth[p] + 1;
	siz[u] = 1;
	pref_child[u] = -1;
	lst[u] = dfs_time;
	euler[dfs_time++] = u;

	loop(i,sz(E[u])) {
		int e = E[u][i];
		int v = fr[e] + to[e] - u;
		if(v == p) continue;
		fr[e] = u;
		to[e] = v;
		dfs(v,u);
		if(pref_child[u] == -1 || siz[pref_child[u]] < siz[v]) pref_child[u] = v;
		siz[u] += siz[v];
		lst[u] = dfs_time;
		euler[dfs_time++] = u;
	}
}

void hld(int u,int p,int edge_weight){
	dfs_in[u] = dfs_time;
	edge_euler[dfs_time] = edge_weight;
	dfs_time++;
	hld_id[u] = hld_cnt;
	parent[u] = p;
	if(hld_siz[hld_cnt] == 0) head[hld_cnt] = u;
	hld_siz[hld_cnt]++;

	int we = 0;
	loop(i,sz(E[u])) {
		int e = E[u][i];
		int v = fr[e] + to[e] - u;
		if(v == p) continue;
		assert(v == to[e]);
		if(v == pref_child[u]) we = weight[e];
	}
	if(pref_child[u] != -1) hld(pref_child[u],u,we);

	loop(i,sz(E[u])) {
		int e = E[u][i];
		int v = fr[e] + to[e] - u;
		if(v == p || v == pref_child[u]) continue;
		hld_cnt++;
		hld(v,u,weight[e]);
	}
	dfs_out[u] = dfs_time - 1;
}


void build(int node,int s,int e){
	if(s == e) {
		ST[node] = edge_euler[s];
		return;
	}
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	build(left,s,m);
	build(right,m+1,e);
	ST[node] = max(ST[left],ST[right]);
}

void update(int node,int s,int e,int p,int v){
	if(s == e) {
		ST[node] = v;
		return;
	}
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(p <= m) update(left,s,m,p,v);
	else update(right,m+1,e,p,v);
	ST[node] = max(ST[left],ST[right]);
}

int query(int node,int s,int e,int l,int r){
	if(l <= s && e <= r) return ST[node];
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(r <= m) return query(left,s,m,l,r);
	if(m < l) return query(right,m+1,e,l,r);
	return max(query(left,s,m,l,m),query(right,m+1,e,m+1,r));
}

int get(int u,int p){
	int ret = 0;
	while(hld_id[u] != hld_id[p]) {
		int id = hld_id[u];
		int h = head[id];
		ret = max(ret,query(1,0,dfs_time-1,dfs_in[h],dfs_in[u]));
		u = parent[h];
	}
	if(p != u)
		ret = max(ret,max(ret,query(1,0,dfs_time-1,dfs_in[p]+1,dfs_in[u])));
	return ret;
}

int query(int u,int v){
	if(u == v) return 0;
	int ret = INT_MIN;
	while(hld_id[u] != hld_id[v]){
		if(hld_id[u] > hld_id[v]) swap(u,v);
		int x = head[hld_id[v]];
		int tmp = query(1,0,n-1,dfs_in[x],dfs_in[v]);
		ret = max(ret,tmp);
		v = parent[x];
	}
	if(u == v) return ret;
	if(dfs_in[u] > dfs_in[v]) swap(u,v);
	int tmp = query(1,0,n-1,dfs_in[u]+1,dfs_in[v]);
	ret = max(ret,tmp);
	return ret;
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	int T; scanf("%d",&T);
	while(T--) {
		scanf("%d",&n);
		range(e,1,n-1){
			scanf("%d %d %d",fr + e,to + e,weight + e);
			E[fr[e]].pb(e);
			E[to[e]].pb(e);
		}
		dfs(1,0);
//		prArr(fr+1,n-1,int);
//		prArr(to+1,n-1,int);
		//build_RMQ();
		dfs_time = 0;
		hld(1,0,0);
		build(1,0,dfs_time-1);
		while(scanf("%s",command) == 1 && strcmp(command,"DONE") != 0) {
			int a,b; scanf("%d %d",&a,&b);
			if(strcmp(command,"QUERY") == 0) {
				printf("%d\n",query(a,b));
			}
			else {
				update(1,0,dfs_time-1,dfs_in[to[a]],b);
			}
		}
		clean();
	}

	return 0;
}
