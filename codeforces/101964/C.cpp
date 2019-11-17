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

const int MAXN = 111;
int n,m;
int color[MAXN];
vi G[MAXN];
int dp[MAXN][MAXN][MAXN];
int aux[MAXN][MAXN];

void dfs(int u,int p) {
	for(int v : G[u]) {
		if(v == p) continue;
		dfs(v,u);
	}
	for(int D = 0;D < n;D++) {
		for(int d = 0;d <= D;d++) dp[u][D][d] = color[u];
		for(int v : G[u]) {
			if(v == p) continue;
			for(int d = 0;d <= D;d++) aux[u][d] = dp[u][D][d];
			for(int l = 0;l < D;l++) {
				for(int r = 0;l+r+1 <= D;r++) {
					int val = dp[v][D][l] + dp[u][D][r];
					int d = max(l+1,r);
					aux[u][d] = max(aux[u][d],val);
				}
			}
			int val = 0;
			for(int d = 0;d <= D;d++) dp[u][D][d] = val = max(val,aux[u][d]);
		}
	}
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d",&n,&m);
	loop(i,n) scanf("%d",color +i + 1);
	loop(e,n-1) {
		int a,b; scanf("%d %d",&a,&b);
		G[a].push_back(b);
		G[b].push_back(a);
	}

	dfs(1,0);
	for(int d = 0;d < n;d++)
		for(int u = 1;u <= n;u++){
			if(dp[u][d][d] >= m) {
				printf("%d\n",d);
				exit(0);
			}
		}
	assert(0);
	return 0;
}
#endif
