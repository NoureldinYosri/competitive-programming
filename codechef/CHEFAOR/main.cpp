#pragma GCC optimize("O3")
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


const ll oo = 1LL << 60;
const int MAX = 5001;
ll cost[MAX][MAX],dp[MAX][MAX];
int best[MAX][MAX],vis[MAX][MAX];
int A[MAX],k,n;

ll solve(int k,int n){
	//cerr << k << " " << n << endl;
	if(!k && !n) return 0;
	if(!k || !n) return -oo;
	if(vis[k][n]) return dp[k][n];
	vis[k][n] = 1;
	solve(k , n-1);
	int x = best[k][n - 1],y = n - 1;
	if(k != ::k) {
		solve(k + 1,n);
		y = best[k + 1][n];
	}
	dp[k][n] = -oo;
	for(int left = best[k][n - 1];left <= y;left++){
		ll v = solve(k-1,left) + cost[left + 1][n];
		if(v > dp[k][n]) {
			dp[k][n] = v;
			best[k][n] = left;
		}
	}
	return dp[k][n];
}

int main(){
	int T; scanf("%d",&T);
	while(T--){
		scanf("%d %d",&n,&k);
		range(i,1,n) scanf("%d",A + i);
		range(i,1,n) {
			ll cur = 0;		
			range(j,i,n)
				cost[i][j] = cur = cur | A[j];
		//	prArr(cost[i],n+1,ll);
		}
		memset(vis,0,sizeof vis);
		//range(i,0,k+1) range(j,0,n) best[i][j] = n;
		printf("%lld\n",solve(k,n));
	//	for(int i = 0;i <= k;i++){
//			prArr(best[i],n+1,int);	
	//		prArr(dp[i],n+1,ll);
	//	}
	//	cerr << solve(k,n) << endl;
//		break;
	}
	
	
	return 0;
}
