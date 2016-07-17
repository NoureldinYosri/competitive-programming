#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long>
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

const int MAX = 1e5 + 1e3;
vi G[MAX];
int val[MAX],n;
ll dp[MAX][2];
ll ans = 0;

void dfs(int u,int p){
	ll mx = 0,mn = 0;	
	for(int v : G[u]) if (v != p){
		dfs(v,u);
		mx = max(mx,dp[v][0]);
		mn = max(mn,dp[v][1]);
	}
//	cerr << u << " " << val[u] << " ";
	val[u] += mx - mn;
	if(val[u] > 0) dp[u][0] = mx,dp[u][1] = val[u] + mn;
	else dp[u][0] = mx - val[u],dp[u][1] = mn;
//	cerr << " -> " << val[u] << " ";
//	prArr(dp[u],2,int);
}

int main(){
	int a,b;
	scanf("%d",&n);
	loop(i,n - 1){
		scanf("%d %d",&a,&b);
		G[a].pb(b);
		G[b].pb(a);
	}
	loop(i,n) scanf("%d",val + i + 1);
	dfs(1,0);
	ll ans = dp[1][0] + dp[1][1];
	cerr << ans << endl;
	cout << ans << endl;
	return 0;
}
