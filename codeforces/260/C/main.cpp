#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0,_ = (n);i < _;i++)
#define range(i,a,b) for(int i = (a),_ = (b);i <= _;i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b),_ = (a);i >= _;i--)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define vi vector<int>
#define vl vector<long>
#define vd vector<double>
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

const int MAX = 1e5;
int A[1 << 20],CTR[1 << 20],n;
ll dp[1 << 20][2];

ll solve(int n,int used = 0){
	if(n > MAX) return 0;
	if(dp[n][used] != -1) return dp[n][used];
	dp[n][used] = solve(n + 1,0);
	if(!used) dp[n][used] = max(dp[n][used],solve(n + 2,used) + CTR[n + 1]*(n + 1LL));
	return dp[n][used];
}

int main(){
	scanf("%d",&n);
	loop(i,n) scanf("%d",A + i),CTR[A[i]]++;
	fill(&dp[0][0],&dp[MAX + 10][0],-1);
	cerr << solve(0) << endl;
	cout << solve(0) << endl;	
	return 0;
}
