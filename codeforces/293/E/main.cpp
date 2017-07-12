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

const int MAX = 100*1000 + 10;
vi E[MAX];
int fr[MAX],to[MAX],weight[MAX];
int siz[MAX],max_subtree[MAX],dont[MAX];
int dfs_in[MAX],dfs_out[MAX],dfs_time;
int n,max_l ,max_w;
ll ans = 0;
vi vertices;
int rev[MAX],path_len[MAX];
ll path_weight[MAX];
vi ST[MAX << 2][2];
int IDX[MAX][20];
int dfs_cnt(int u,int p){
	siz[u] = 1;
	max_subtree[u] = 0;
	for(int e : E[u]){
		int v = fr[e] + to[e] - u;
		if(v == p || dont[v]) continue;
		int t = dfs_cnt(v,u);
		siz[u] += t;
		max_subtree[u] = max(max_subtree[u],t);
	}
	return siz[u];
}

void get_root(int u,int p,int V,int & root){
	max_subtree[u] = max(max_subtree[u],V - siz[u]);
	if(root == -1 || max_subtree[u] < max_subtree[root]) root = u;
	for(int e : E[u]){
		int v = fr[e] + to[e] - u;
		if(v == p || dont[v]) continue;
		get_root(v,u,V,root);
	}
}


void merge(vi & A,vi & B,vi & C){
	int i = 0,j = 0;
	while(i < sz(A) && j < sz(B)) {
		if(path_len[A[i]] < path_len[B[j]]) C.pb(A[i++]);
		else C.pb(B[j++]);
	}
	while(i < sz(A)) C.pb(A[i++]);
	while(j < sz(B)) C.pb(B[j++]);
}

void build(int node,int s,int e,int depth){
	loop(i,2) ST[node][i].clear();
	ST[node][1].resize(e - s + 1);
	if(s == e){
		int u = vertices[s];
		ST[node][0].pb(u);
		IDX[u][depth] = 0;
		return;
	}
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	build(left,s,m,depth + 1);
	build(right,m+1,e,depth + 1);
	merge(ST[left][0],ST[right][0],ST[node][0]);
	loop(i,e-s+1){
		int u = ST[node][0][i];
		IDX[u][depth] = i;
	}
}
inline void update(int p,int v,vi & BIT){
	for(++p;p <= sz(BIT);p += LSOne(p)) BIT[p - 1] += v;
}

inline int get(int p,vi & BIT){
	int ret = 0;
	for(++p;p;p ^= LSOne(p)) ret += BIT[p - 1];
	return ret;
}

void update(int node,int s,int e,int pos,int depth){
	update(IDX[vertices[pos]][depth],1,ST[node][1]);
	if(s == e) return;
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(pos <= m) update(left,s,m,pos,depth + 1);
	else update(right,m+1,e,pos,depth+1);
}

int query(int node,int s,int e,int pos,int len){
	if(e <= pos) {
		int p = lower_bound(all(ST[node][0]),len+1,[](const int & a,const int & target){
			return path_len[a] < target;
		}) - ST[node][0].begin();
		return get(p - 1,ST[node][1]);
	}
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(pos <= m) return query(left,s,m,pos,len);
	else return query(left,s,m,pos,len) + query(right,m+1,e,pos,len);;
}


void explore(int u,int p,int len,ll w){
	vertices.pb(u);
	path_len[u] = len;
	path_weight[u] = w;
	for(int e : E[u]){
		int v = fr[e] + to[e] - u;
		if(v == p || dont[v]) continue;
		explore(v,u,len + 1,w + weight[e]);
	}
}

void compute(int u,int p){
	auto idx = lower_bound(all(vertices),max_w - path_weight[u] + 1,[](const int & a,const ll & target){
		return path_weight[a] < target;
	}) - vertices.begin();
	if(idx){
		--idx;
		int tmp = query(1,0,sz(vertices)-1,idx,max_l - path_len[u]);
		ans += tmp;
	}
	for(int e : E[u]){
		int v = fr[e] + to[e] - u;
		if(v == p || dont[v]) continue;
		compute(v,u);
	}
}

void insert(int u,int p){
	update(1,0,sz(vertices)-1,rev[u],0);
	for(int e : E[u]){
		int v = fr[e] + to[e] - u;
		if(v == p || dont[v]) continue;
		insert(v,u);
	}
}

void divide_conquer(int u,int p){
	dont[p] = 1;
	int V = dfs_cnt(u,p),root = -1;
	if(V == 1) return;
	get_root(u,p,V,root);
	assert(root != -1);
	u = root;

	// build DS
	vertices.clear();
	vertices.pb(u);
	path_weight[u] = path_len[u] = 0;
	for(int e : E[u]){
		int v = fr[e] + to[e] - u;
		if(v == p || dont[v]) continue;
		explore(v,u,1,weight[e]);
	}
	sort(all(vertices),[](const int & a,const int & b){
		return tie(path_weight[a],path_len[a]) < tie(path_weight[b],path_len[b]);
	});
	loop(i,sz(vertices)) rev[vertices[i]] = i;
	build(1,0,sz(vertices)-1,0);
	update(1,0,sz(vertices)-1,rev[u],0);

	/*cerr << "root is " << root << endl;
	for(int v : vertices) {
		cerr << "(" << v << " ,";
		prp(mp(path_weight[v],path_len[v]));
		cerr << ")";
	}
	cerr << endl;
	*/
	// update answer
	for(int e : E[u]){
		int v = fr[e] + to[e] - u;
		if(v == p || dont[v]) continue;
		compute(v,u);
		insert(v,u);
	}

	//recurse
	for(int e : E[u]){
		int v = fr[e] + to[e] - u;
		if(v == p || dont[v]) continue;
		divide_conquer(v,u);
	}
}


int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d %d",&n,&max_l,&max_w);
	loop(e,n-1){
		to[e] = e + 2;
		scanf("%d %d",fr + e,weight + e);
		E[fr[e]].pb(e);
		E[to[e]].pb(e);
	}
	vertices.reserve(n);
	divide_conquer(1,0);
	cout << ans << endl;
	return 0;
}
