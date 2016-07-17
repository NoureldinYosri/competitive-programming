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

int val[3000][3],n;
int dp[3000][2];

int solve(int p = 0,int s = 0){
	if(p == n - 1) return val[p][s];
	if(dp[p][s] != -1) return dp[p][s];
	int & ans = dp[p][s];
	ans = val[p][s] + solve(p + 1,1);
	ans = max(ans,val[p][s + 1] + solve(p + 1,0));
	return ans;
}

int main(){
	memset(dp,-1,sizeof dp);
	scanf("%d",&n);
	loop(j,3) loop(i,n) scanf("%d",&val[i][j]);
	int ans = solve();	
	cerr << ans << endl;
	cout << ans << endl;
	return 0;
}
