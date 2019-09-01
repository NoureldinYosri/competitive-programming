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

const int MAXN = 2*250*1000 + 10,MAXLG = 20;
vi E[MAXN];
int fr[MAXN],to[MAXN],W[MAXN];
int ord[MAXN],depth[MAXN],dfs_in[MAXN],dfs_out[MAXN],dfs_time;
int sparse[MAXN][MAXLG],lg[MAXN];
int n,K,m;
int f[MAXN];
vi roots;

void dfs(int u,int p) {
	dfs_in[u] = dfs_time;
	ord[dfs_time++] = u;
	depth[u] = depth[p] + 1;
	for(int e : E[u]) {
		int v = fr[e] + to[e] - u;
		if(v == p) continue;
		dfs(v,u);
		ord[dfs_time++] = u;
	}
	dfs_out[u] = dfs_time-1;
}

int argmin(int a,int b) {
	return min(pi(depth[a],a),pi(depth[b],b)).second;
}

void build(){
	for(int u = 1;u <= n;u++)
		if(!depth[u]){
			dfs(u,0);
			roots.push_back(u);
//			prArr(depth,n+1,int);
		}
//	print(roots,int);
	int m = dfs_time;
	lg[0] = -1;
	for(int i = 1;i < m;i++) lg[i] = lg[i-1] + (i == LSOne(i));
	loop(i,m) sparse[i][0] = ord[i];
	loop(k,MAXLG-1){
		loop(i,m) {
			int j = i + (1 << k);
			if(j >= m) j = i;
			sparse[i][k + 1] = argmin(sparse[i][k],sparse[j][k]);
		}
	}
}
int lca(int a,int b) {
	a = dfs_in[a],b = dfs_in[b];
	if(a > b) swap(a,b);
	int l = lg[b - a + 1];
	return argmin(sparse[a][l],sparse[b - (1 << l) + 1][l]);
}

void floodFill(int u,int p,int ctr) {
	ctr += f[u];
	assert(ctr >= 0);
	for(int e : E[u]){
		int v = fr[e] + to[e] - u;
		if(v == p) continue;
		W[e] = ctr > 0;
		floodFill(v,u,ctr);
	}
}

int dp[MAXN][2];
int solve(int u,int p,int c) {
	int & ret = dp[u][c];
	if(ret != -1) return ret;
	ret = c;
	for(int e : E[u]) {
		int v = fr[e] + to[e] - u;
		int tmp = 1 << 29;
		loop(c2,2) {
			int covered = c || c2;
			if(covered || W[e] == 0)
				tmp = min(tmp,solve(v,u,c2));
		}
		ret += tmp;
	}
//	cerr << u << " " << c << ": " << ret << endl;
	return ret;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d %d",&n,&K,&m);
	loop(e,K) {
		scanf("%d %d",fr + e,to + e);
		E[fr[e]].push_back(e);
		E[to[e]].push_back(e);
	}
	build();
	while(m--) {
		int a,b; scanf("%d %d",&a,&b);
		if(depth[a] > depth[b]) swap(a,b);
		int p = lca(a,b);
//		cerr << a << " " << b << ": " << p << endl;
		if(p == a) {
			f[a]++;
			f[b]--;
		}
		else {
			f[p]++;
			f[a]--; f[b]--;
		}
	}
	int ans = 0;
	memset(dp,-1,sizeof dp);
	for(int u : roots){
		floodFill(u,0,0);
//		prArr(W,K,int);
	}
	for(int u : roots)
		ans += min(solve(u,0,0),solve(u,0,1));
	printf("%d\n",ans);
	return 0;
}
