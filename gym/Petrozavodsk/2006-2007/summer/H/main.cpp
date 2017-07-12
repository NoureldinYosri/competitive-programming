#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define pl pair<ll,ll>
#define popcnt(x) __builtin_popcountll(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
using namespace std;

int n,m,k;
ll dp[60][1 << 15];

ll solve(int cur,int msk){
	if(cur == n) return 1;
	if(dp[cur][msk] != -1) return dp[cur][msk];
	ll & ret = dp[cur][msk];
	ret = 0;
	if(cur < m - 1) ret = solve(cur + 1,msk << 1) + solve(cur + 1,(msk << 1) | 1);
	else{
		int nmsk = (msk << 1) & ~(1 << m);
		if(popcnt(nmsk | 1) >= k) ret = solve(cur + 1,nmsk | 1);
		if(popcnt(nmsk) >= k) ret += solve(cur + 1,nmsk);
	}
	return ret;
}
int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	cin >> n >> m >> k;
	memset(dp,-1,sizeof dp);
	cout << solve(0,0) << endl;
	return 0;
}
