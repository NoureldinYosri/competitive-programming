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

const int MAX = 1 << 20;
vi G[MAX];
int n = 4;
int Q[MAX],m;
int siz[MAX],pref_child[MAX],depth[MAX],pathID[MAX],parent[MAX];
int head[MAX],path_siz[MAX],dfs_in[MAX],dfs_out[MAX],dfs_time,cnt;
int ord[MAX];
int ST[MAX << 2],ST2[MAX << 2];
int diameter = 0;

int dfs(int u,int p){
	siz[u] = 1;
	depth[u] = depth[p] + 1;
	parent[u] = p;
	for(int v : G[u]) {
		int t = dfs(v,u);
		siz[u] += t;
		if(t > siz[pref_child[u]]) pref_child[u] = v;
	}
	return siz[u];
}

void hld(int u){
	ord[dfs_time] = u;
	dfs_in[u] = dfs_time++;
	pathID[u] = cnt;
	if(!path_siz[cnt]) head[cnt] = u;
	path_siz[cnt]++;
	if(pref_child[u]) hld(pref_child[u]);
	for(int v : G[u]) if(v != pref_child[u]) {
		++cnt;
		hld(v);
	}
	dfs_out[u] = dfs_time - 1;
}

void update(int node,int s,int e,int p,int val,int *ST){
	if(s == e){
		ST[node] = max(ST[node],val);
		return;
	}
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(p <= m) update(left,s,m,p,val,ST);
	else update(right,m+1,e,p,val,ST);
	ST[node] = max(ST[left],ST[right]);
}

int query(int node,int s,int e,int l,int r,int *ST){
	if(l <= s && e <= r) return ST[node];
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(r <= m) return query(left,s,m,l,r,ST);
	else if(m < l) return query(right,m+1,e,l,r,ST);
	else return max(query(left,s,m,l,m,ST) , query(right,m+1,e,m+1,r,ST));
}



void insert(int u){
	update(1,0,n-1,dfs_in[u],depth[u],ST2);
	int d = depth[u];
	int l = -1,r = -1;
	while(u){
		int path = pathID[u],h = head[path];
		int mx;
		if(h != u){
			mx = query(1,0,n-1,dfs_in[h],dfs_in[u]-1,ST);
			diameter = max(diameter,mx + d);
		}
		mx = -(1 << 25);
		if(l == -1)	mx = query(1,0,n-1,dfs_in[u],dfs_out[u],ST2);
		else{
			mx = query(1,0,n-1,dfs_in[u],l-1,ST2);
			if(r != dfs_out[u])
				mx = max(mx,query(1,0,n-1,r+1,dfs_out[u],ST2));
		}
		l = dfs_in[u]; r = dfs_out[u];
		diameter = max(diameter,mx + d - 2*depth[u]);
		update(1,0,n-1,dfs_in[u],d - 2*depth[u],ST);
		u = parent[h];
	}
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	range(i,2,4) G[1].pb(i);
	scanf("%d",&m);
	loop(i,m){
		scanf("%d",Q + i);
		++n; G[Q[i]].pb(n);
		++n; G[Q[i]].pb(n);
	}
	dfs(1,0);
	hld(1);
	fill(ST,ST + 3*n,INT_MIN);


	range(i,1,4) insert(i);

	int N = 4;
	loop(i,m){
		++N; insert(N);
		++N; insert(N);
		printf("%d\n",diameter);
	}

	return 0;
}
