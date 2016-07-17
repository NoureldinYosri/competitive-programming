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

char s[100];
int dp[2][51][51];

int solve(){
	int n = strlen(s);
	loop(i,n + 1) loop(j,n + 1) dp[0][i][j] = 1 << 29;
	dp[0][0][0] = 0;
	range(p,1,n){
		int o = (p & 1)^1;
		loop(i,n + 1) loop(j,n + 1) {
			dp[p & 1][i][j] = 1 << 29;
			if(i) dp[p & 1][i][j] = min(dp[p & 1][i][j],dp[o][i - 1][j] + (s[p - 1] != '('));
			if(i + 1 <= n) dp[p & 1][i][j] = min(dp[p & 1][i][j],dp[o][i + 1][j] + (s[p - 1] != ')'));
			if(j) dp[p & 1][i][j] = min(dp[p & 1][i][j],dp[o][i][j - 1] + (s[p - 1] != '['));
			if(j + 1 <= n) dp[p & 1][i][j] = min(dp[p & 1][i][j],dp[o][i][j + 1] + (s[p - 1] != ']'));
		}
	}
	if(dp[n & 1][0][0] < (1 << 29)) return dp[n & 1][0][0];
	return -1;
}

int main(){
	scanf("%s",s);
	cout << solve() << endl;	
	return 0;
}