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

const int MAX = 200'010;
ll S[MAX],E[MAX];
int k;
ll n;
pl A[MAX];
ll dp[MAX];

ll solve(int p){
	if(p == k) return 0;
	if(dp[p] != -1) return dp[p];
	dp[p] = 1LL << 60;
	if(p != k - 1) dp[p] = solve(p + 1) + S[p + 1] - S[p];
	int j = upper_bound(S,S + k,E[p]) - S;
	if(j < k) {
	//	cerr << p << " -> " << j << " " << S[j] - E[p] - 1 << endl;
		dp[p] = min(dp[p],solve(j) + S[j] - E[p] - 1);
	}
	else {
	//	cerr << p << " to end " << n << " " << E[p] << endl;	
		dp[p] = min(dp[p],n - E[p]);	
	}
	return dp[p];
}

int main(){
	scanf("%lld %d",&n,&k);
	loop(i,k) scanf("%lld %lld",&A[i].xx,&A[i].yy);
	sort(A,A + k);
	loop(i,k) S[i] = A[i].xx,E[i] = A[i].yy;
	memset(dp,-1,sizeof dp);
	ll ans = 1LL << 60;
	loop(i,k) ans = min(ans,solve(i) + S[i] - 1);

	cerr << ans << endl;
	cout << ans << endl;
	return 0;
}
