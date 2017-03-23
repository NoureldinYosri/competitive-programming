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

int dp[10][1001],n,m,c0,d0;
int A[10],B[10],C[10],D[10];

int solve(int p,int r){
	if(p == m) return (r/c0)*d0;
	if(dp[p][r] != -1) return dp[p][r];
	int & ret = dp[p][r]; ret = 0;
	for(int i = 0;i*B[p] <= A[p] && i*C[p] <= r;i++)
		ret = max(ret,solve(p + 1,r - i*C[p]) + i*D[p]);
	return ret;
}

int main(){
	cin >> n >> m >> c0 >> d0;
	loop(i,m) cin >> A[i] >> B[i] >> C[i] >> D[i];
	memset(dp,-1,sizeof dp);
	cout << solve(0,n) << endl;
	
	
	return 0;
}
