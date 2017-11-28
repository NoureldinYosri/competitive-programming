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

const int mod = 1e9 + 7;
const int MAX = 300*1000 + 10;
ll BIT[2][MAX];
vi G[MAX];
int parent[MAX],dfs_in[MAX],dfs_out[MAX],dfs_time,n,depth[MAX];

int add(ll a,ll b){
	ll ret = a + b;
	ret = (ret%mod + mod)%mod;
	return ret;
}

void add(int p,ll v,ll *T){
	for(;p <= n;p += LSOne(p)) T[p] = add(T[p],v);
}

ll get(int p,ll *T){
	ll ret = 0;
	for(;p;p ^= LSOne(p)) ret = add(ret,T[p]);
	return ret;
}

void dfs(int u) {
	depth[u] = depth[parent[u]] + 1;
	dfs_in[u] = ++dfs_time;
	for(int v : G[u]) dfs(v);
	dfs_out[u] = dfs_time;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d",&n);
	range(i,2,n) {
		scanf("%d",parent + i);
		G[parent[i]].pb(i);
//		cerr << parent[i] << " " << i << endl;
	}
	dfs(1);
	assert(dfs_time == n);
	int m; scanf("%d",&m);
	while(m--) {
		int type; scanf("%d",&type);
		if(type == 1) {
			int u,x,k; scanf("%d %d %d",&u,&x,&k);
			int v = (x + k*1LL*depth[u])%mod;
			add(dfs_in[u],v,BIT[0]);
			add(dfs_out[u]+1,-v,BIT[0]);

			add(dfs_in[u],k,BIT[1]);
			add(dfs_out[u]+1,-k,BIT[1]);
		}
		else {
			int u; scanf("%d",&u);
			int a = get(dfs_in[u],BIT[0]);
			int b = get(dfs_in[u],BIT[1]);
			int c = (b*1LL*depth[u])%mod;
			int ans = add(a,-c);
		//	cerr << a << " - " << depth[u] << " * " << b << endl;
			printf("%d\n", ans);
		}
	}
	return 0;
}
