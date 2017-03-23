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

ll dp[1001][1001];
char line[1001];
int n,w[128],k,x;

ll solve(int i,int j){
	if(i == n && j == k) return 0;
	if(dp[i][j] != -1) return dp[i][j];
	dp[i][j] = 0;
	if(i != n) dp[i][j] = solve(i+1,j) + (i+j+1LL)*w[line[i]];
	if(j != k) dp[i][j] = max(dp[i][j],solve(i,j+1) + x*(i+j+1LL));
	return dp[i][j];
}

int main(){
	cin >> line >> k; n = strlen(line);	
	for(int i = 'a';i <= 'z';i++) cin >> w[i],x = max(x,w[i]);
	memset(dp,-1,sizeof dp);
	cerr << solve(0,0) << endl;
	cout << solve(0,0) << endl;
	
	return 0;
}
