#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define vi vector<int>
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
#define pre() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

int D[300][300],G[300][300],n;
const int inf = 1 << 29;
int dp[300][300];
int target;


int solve(int u,int k){
	if(k == n) return inf;	
	if(dp[u][k] != -1) return dp[u][k];
	dp[u][k] = solve(u,k + 1);
	if(u != target) dp[u][k] = min(dp[u][k],solve(k,k + 1) + D[u][k]);
	if(target > k) dp[u][k] = min(dp[u][k],D[u][target]);
	cerr << u << " " << k << " " << dp[u][k] << endl;
	return dp[u][k];
}

int main(){
	scanf("%d",&n);
	loop(i,n)loop(j,n) {
		scanf("%d",&D[i][j]);
		if(D[i][j] == -1) D[i][j] = inf;
		G[i][j] = D[i][j];	
	}
	loop(k,n) loop(i,n) loop(j,n) D[i][j] = min(D[i][j],D[i][k] + D[k][j]);
	loop(i,n) {prArr(D[i],n,ll);}
	loop(k,n){
		int ans = inf;
		loop(i,n) loop(j,n) {
			if(i == j || i == k || j == k) continue;
			if(k == 0) cerr << i << " " << j << " " << G[k][i] + D[i][j] + G[j][k] << endl;		
			ans = min(ans,G[k][i] + D[i][j] + G[j][k]);
		}
		if(ans == inf) ans = -1;
		cerr << ans << endl;
	}
	return 0;
}
