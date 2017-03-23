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

const int MAX = 100;
vi G[MAX];
int dp[MAX][2];
void solve(int u,int p){
	dp[u][1] = 0;
	dp[u][0] = -1000;
	for(int v : G[u]) if(v != p){
		solve(v,u);
		int t = max(dp[u][0] + dp[v][0] + 1,dp[u][1] + dp[v][1]);
		dp[u][1] = max(dp[u][1] + dp[v][0] + 1,dp[u][0] + dp[v][1]);
		dp[u][0] = t;
	}
//	cerr << u + 1 << " : "; prArr(dp[u],2,int);
}

int main(){
	int n,m; scanf("%d %d",&n,&m);
	assert(n == m + 1);
	loop(i,n-1){
		int a,b; scanf("%d %d",&a,&b);
		a--,b--;
		G[a].pb(b);
		G[b].pb(a);
	}
	solve(0,-1);
	cerr << dp[0][0] << endl;
	return 0;
}
