#pragma GCC optimize ("O3")
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
using namespace std;


const int MAX = 3 << 10;

vi E[MAX];
int P[MAX];
ll siz[MAX];
int fr[MAX], to[MAX], n, m;

void floodFill(int u,int p){
	P[u] = p;
	siz[u] = 1;
	for(int e : E[u]) {
		int v = fr[e] + to[e] - u;
		if(v != p){
			floodFill(v, u);
			siz[u] += siz[v];
		}
	}
}

int visNum;
int visID[MAX][MAX];
ll dp[MAX][MAX];
int G_in[MAX][MAX];
int G_out[MAX][MAX];
int dfs_time;


void dfs(int u, int p, int *dfs_in, int *dfs_out){
	dfs_in[u] = dfs_time++;
	for(int e : E[u]){
		int v = fr[e] + to[e] - u;
		if(v == p) continue;
		dfs(v, u, dfs_in, dfs_out);
	}
	dfs_out[u] = dfs_time;
}

void dfs(int u){
	dfs_time = 0;
	dfs(u, 0, G_in[u], G_out[u]);
}


bool onPath(int u, int v, int t){
	int *dfs_in = G_in[u];
	int *dfs_out = G_out[u];
	return dfs_in[t] <= dfs_in[v] && dfs_in[v] < dfs_out[t];
}

ll solve(int u, int v){
	if(visID[u][v] == visNum) return dp[u][v];
	ll & ret = dp[u][v];
	ret = 0;
	visID[u][v] = visNum;
	for(int e : E[u]){
		int t = fr[e] + to[e] - u;
		if(onPath(u,v,t)) continue;
		ret = max(ret, siz[t] * siz[v] + solve(t, v));
	}
	for(int e : E[v]){
		int t = fr[e] + to[e] - v;
		if(onPath(u,v,t)) continue;
		ret = max(ret, siz[u] * siz[t] + solve(u, t));
	}
//	cout << u << " " << v << " " << ret << endl;
	return ret;
}



int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d",&n);
	m = n-1;
	loop(e,m){
		scanf ("%d %d", fr + e, to +e);
		E[fr[e]].pb(e);
		E[to[e]].pb(e);
	}
	for(int u = 1;u <= n;u++) dfs(u);
	visNum++;
	ll ans = 0;
	for(int e = 0;e < m;e++){
		floodFill(fr[e], to[e]);
		floodFill(to[e], fr[e]);
		
		ans = max(ans, siz[fr[e]]*siz[to[e]] + solve(fr[e], to[e]));
	}
	cout << ans << endl;
	return 0;
}
