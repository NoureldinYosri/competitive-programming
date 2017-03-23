#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define point pair<double,double>
#define pl pair<ll,ll>
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

const int MAX = 50010,mod = 1e9 + 7;
int n,K;
vi G[MAX];
int dp[MAX][101];
int color[MAX];
int ans ;

void dfs(int u,int p){
	fill(dp[u],dp[u + 1],0);
	dp[u][color[u]]++;
	vi aux(K+1);
	for(int v : G[u]) if(v != p){
		dfs(v,u);
		copy(dp[u],dp[u] + K + 1,aux.begin());
		fill(dp[u],dp[u] + K + 1,0);
		for(int k = 0;k <= K;k++)
			for(int k1 = 0;k1 <= K - k;k1++){
				dp[u][k + k1] += (aux[k]*1LL*dp[v][k1])%mod;
				dp[u][k + k1] -= (dp[u][k + k1] >= mod) ? mod : 0;
			}
	}
//	cerr << u << " : "; prArr(dp[u],K+1,int);
	ans += dp[u][K];
	ans -= (ans >= mod) ? mod : 0;
	dp[u][0]++;
}

int main(){
	int T; scanf("%d",&T);
	while(T--){
		scanf("%d %d",&n,&K);
		range(i,1,n) scanf("%d",color + i),G[i].clear();
		loop(i,n-1){
			int a,b; scanf("%d %d",&a,&b);
			G[a].pb(b);
			G[b].pb(a);
		}
		ans = 0;
		dfs(1,0);
		cerr << ans << endl;
	}
	
	
	return 0;
}
