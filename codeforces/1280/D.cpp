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

const ll oo = 1LL << 60;
using pl = pair<int,ll>;
const int MAX = 3111;
int n;
vi G[MAX];
pl dp[MAX][MAX],aux[MAX][MAX];
int wasb[MAX],ant[MAX];
int siz[MAX];

void dfs(int u,int p){
	dp[u][0] = pl(0,-oo);
	dp[u][1] = pl(0, wasb[u] - ant[u]);
	siz[u] = 1;
	for(int v : G[u]) if(v != p){
		dfs(v,u);
		loop(i,siz[u] + siz[v]+1) aux[u][i] = pl(0, -oo);
		for(int s = 1;s <= siz[u];s++){
			for(int k = 1;k <= siz[v];k++){
				pl A = dp[u][s], B = dp[v][k];
				aux[u][s+k] = max(aux[u][s+k], pl(A.first + B.first + (B.second > 0), A.second));
				int val = A.first + B.first;
				aux[u][s+k-1] = max(aux[u][s+k-1], pl(val, A.second + B.second));
			}
		}
		siz[u] += siz[v];
		copy(aux[u],aux[u] + siz[u] + 1,dp[u]);
	}
/*	cout << u << ": ";
	for(auto p : dp[u]) cout << p;
	cout << endl;
	* */
}



int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d",&T);
	while(T--){
		int m; scanf("%d %d",&n,&m);
		loop(i,n+1) G[i].clear();
		for(int i = 1;i <= n;i++) scanf("%d", ant+i);
		for(int i = 1;i <= n;i++) scanf("%d", wasb+i);
		loop(i,n-1){
			int a,b; scanf("%d %d",&a,&b);
			G[a].pb(b);
			G[b].pb(a);
		}
		dfs(1, 0);
		printf("%d\n", dp[1][m].first + (dp[1][m].second > 0));
	}
	return 0;
}
