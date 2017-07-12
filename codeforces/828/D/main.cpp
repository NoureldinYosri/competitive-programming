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
int id[MAX],W[MAX],mx[MAX];
bool is_MST[MAX];
int fr[MAX],to[MAX],cost[MAX],ord[MAX],n,m;
vi adj[MAX];
int siz[MAX],pref_child[MAX],dfs_in[MAX],dfs_out[MAX],euler[MAX],dfs_time;


int find(int a){
	return id[a] = (a == id[a]) ? a : find(id[a]);
}

void join(int a,int b){
	a = find(a),b = find(b);
	if(a == b) return;
	if(W[a] < W[b]) swap(a,b);
	W[a] += W[b];
	id[b] = a;
}



void dfs(int u,int p){
	dfs_in[u] = dfs_time;
	euler[dfs_time++] = u;
	siz[u] = 1;
	pref_child[u] = -1;
	for(int e : adj[u]) {
		int v = fr[e] + to[e] - u;
		if(v == p) continue;
		dfs(v,u);
		siz[u] += siz[v];
		if(pref_child[u] == -1 || siz[pref_child[u]] < siz[v]) siz[pref_child[u]] = v;
	}
	dfs_out[u] = dfs_time - 1;
}

void dsu(int u,int p,bool keep){

}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	memset(mx,-1,sizeof mx);
	scanf("%d %d",&n,&m);
	range(i,1,n) id[i] = i,W[i] = i;
	loop(i,m) scanf("%d %d %d",fr + i,to + i,cost + i),ord[i] = i;
	sort(ord,ord + m,[](const int & a,const int &b){
		return cost[a] < cost[b];
	});

	loop(e,m) {
		int a = fr[e],b = to[e];
		if(find(a) == find(b)) continue;
		is_MST[e] = 1;
		join(a,b);
		adj[a].pb(e);
		adj[b].pb(e);
	}
	dfs(1,0);

	loop(i,m) printf("%d%c",mx[i]," \n"[i==m-1]);
	return 0;
}
