#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0,L = (n);i < L;i++)
#define range(i,a,b) for(int i = (a),L = (b);i <= L;i++)
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

int n;
pi A[100];
int dp[100][10001];

int solve(int p,int w){
	if(p == -1) return w;
	if(dp[p][w] != -1) return dp[p][w];
	dp[p][w] = solve(p - 1,w + A[p].yy);
	if(w >= A[p].xx) dp[p][w] = min(dp[p][w],solve(p - 1,w - A[p].xx) + A[p].xx);
	return dp[p][w];
}

int main(){
	PRESTDIO();
	cin >> n;
	loop(i,n) cin >> A[i].yy >> A[i].xx;
	sort(A,A + n);
	memset(dp,-1,sizeof dp);
	cout << solve(n - 1,0) << endl;	
	return 0;
}
