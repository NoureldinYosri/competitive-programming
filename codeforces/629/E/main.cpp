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


const int MAX = 100*1000 + 10,MAXLG = 20;
vi G[MAX];
int siz[MAX],depth[MAX],dfs_in[MAX],dfs_out[MAX],dfs_time,P[MAX][MAXLG],n,m;
ll sum_dist[MAX],sum_dist_up[MAX];

void dfs(int u,int p){
	depth[u] = depth[p] + 1;
	dfs_in[u] = dfs_time++;
	P[u][0] = p;
	loop(i,MAXLG-1) P[u][i + 1] = P[P[u][i]][i];
	siz[u] = 1;
	for(int v : G[u]) if (v != p) {
		dfs(v,u);
		siz[u] += siz[v];
		sum_dist[u] += sum_dist[v] + siz[v];
	}
	dfs_out[u] = dfs_time - 1;
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

void dfs(int u,int p,ll from_parent){
	sum_dist_up[u] = from_parent;
	ll tot = sum_dist[u] + from_parent;
	for(int v : G[u]) if(v != p){
		ll contrib = sum_dist[v] + siz[v];
		ll give = tot - contrib + n - siz[v];
		dfs(v,u,give);
	}
}

int get(int u,int d){
	int k = 0;
	while(d){
		int r = LSOne(d);
		while(r != (1 << k)) k++;
		u = P[u][k];
		d ^= r;
	}
	return u;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d",&n,&m);
	loop(i,n-1){
		int a,b; scanf("%d %d",&a,&b);
		G[a].pb(b);
		G[b].pb(a);
	}
	dfs(1,0);
	dfs_out[0] = n;
	dfs(1,0,0);

	while(m--){
		int a,b; scanf("%d %d",&a,&b);
		if(depth[a] > depth[b]) swap(a,b);
		int p = lca(a,b);

		if(a == p) {
			double ans = depth[b] - depth[a] + 1;
			int pp = get(b,depth[b] - depth[a] - 1);
			ll A = sum_dist[a] + sum_dist_up[a] - sum_dist[pp] - siz[pp];
			ans += A/(n - siz[pp] + 0.0) + sum_dist[b]*1.0/siz[b];
			printf("%.10f\n",ans);
		}
		else {
			double ans = depth[a] + depth[b] - 2*depth[p] + 1;
			ans += sum_dist[a]*1.0/siz[a] + sum_dist[b]*1.0/siz[b];
			printf("%.10f\n",ans);
		}
	}
	return 0;
}
