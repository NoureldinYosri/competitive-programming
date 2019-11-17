#ifdef ACTIVE
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
#define tc() int T; scanf("%d",&T); for(int t = 1;t <= T;t++)
using namespace std;

const int MAX = 1 << 20,MAXLG = 20;
int n;
int fr[MAX],to[MAX],W[MAX];
vi E[MAX];
int dfs_in[MAX],dfs_out[MAX],dfs_time;
int val[MAX];
int P[MAX][MAXLG];
int depth[MAX];


void dfs(int u,int p,int w) {
	dfs_in[u] = ++dfs_time;
	depth[u] = depth[p] + 1;
	val[dfs_time] = w;
	P[u][0] = p;
	loop(k,MAXLG-1) P[u][k+1] = P[P[u][k]][k];

	for(int e : E[u]) {
		int v = fr[e] + to[e] - u;
		if(v == p) continue;
		fr[e] = u;
		to[e] = v;
		dfs(v,u,W[e]&1);
	}
	dfs_out[u] = ++dfs_time;
	val[dfs_time] = w;
}

int BIT[MAX];

void add(int p,int v) {
	for(;p <= dfs_time;p += LSOne(p))
		BIT[p] ^= v;
}
int get(int p) {
	int ret = 0;
	for(;p;p ^= LSOne(p))
		ret ^= BIT[p];
	return ret;
}


char out[2][50] = {"JAKANDA FOREVER","WE NEED BLACK PANDA"};


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

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d",&n);
	loop(e,n-1) {
		scanf("%d %d %d",fr + e,to + e,W + e);
		W[e] &= 1;
		E[fr[e]].push_back(e);
		E[to[e]].push_back(e);
	}
	dfs(1,0,0);
	dfs_out[0] = dfs_time;
	assert(dfs_time == 2*n);
	for(int i = 1;i <= 2*n;i++)
		add(i,val[i]);
//	prArr(val+1,n)
	int Q; scanf("%d",&Q);
	while(Q--) {
		int t; scanf("%d",&t);
		if(t == 1) {
			int u,v; scanf("%d %d",&u,&v);
			if(dfs_in[u] > dfs_in[v]) swap(u,v);
			int p = lca(u,v),res = 0;
			if(p == u) res = get(dfs_in[v]) ^ get(dfs_in[u]);
			else {
				res = get(dfs_in[v]) ^ get(dfs_out[u] - 1);
			}
			puts(out[res]);
		}
		else {
			int e,w; scanf("%d %d",&e,&w);
			w &= 1;
			e--;
			int u = to[e];
			int old = val[dfs_in[u]];
			if(old == w) continue;
			add(dfs_in[u],1);
			add(dfs_out[u],1);
			val[dfs_in[u]] = val[dfs_out[u]] = w;
		}
	}
	return 0;
}
#endif
