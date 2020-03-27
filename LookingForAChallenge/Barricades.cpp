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

const int MAX = 3000 + 10;
vi G[MAX];
int siz[MAX];
int dp[MAX][MAX], aux[MAX];
int n;

void dfs(int u, int p){
	siz[u] = 1;
	for(int v : G[u]) if(v != p) {
		dfs(v, u);
		siz[u] += siz[v];
	}
	for(int s = 0; s <= siz[u]; s++) dp[u][s] = MAX;
	dp[u][0] = MAX;
	dp[u][1] = 0;
	siz[u] = 1;
	for(int v : G[u]) if(v != p) {
		fill(aux, aux + siz[u] + siz[v] + 1, MAX);
		for(int s1 = 0; s1 <= siz[u]; s1++)
			for(int s2 = 0; s2 <= siz[v]; s2++){
				int tmp = dp[u][s1] + (s2 ? dp[v][s2] : 1);
				aux[s1+s2] = min(aux[s1+s2], tmp);
			}
		siz[u] += siz[v];
		copy(aux, aux + siz[u] + 1, dp[u]);
	}
//	prArr(dp[u], n + 1, int);
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d" ,&n);
	loop(e, n-1){
		int a, b; scanf("%d %d", &a, &b);
		G[a].pb(b);
		G[b].pb(a);
	}
	dfs(1, 0);
//	prArr(dp[1], siz[1] + 1, int);
	int m; scanf("%d", &m);
	while(m--){
		int s; scanf("%d", &s);
		int ans = MAX;
		for(int u = 1; u <= n;u++) if(s <= siz[u]) ans = min(ans, dp[u][s] + (u != 1));
		printf("%d\n", ans);
	}
	return 0;
}
