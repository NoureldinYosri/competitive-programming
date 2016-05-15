#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define print(A,t) cout << #A << ": "; copy(all(A),ostream_iterator<t>(cout," " )); cout << endl
#define pi pair<int,int>
#define point pi
#define vi vector<int>
#define ll long long
#define pl pair<ll,ll>
#define pre() cin.tie(0),cout.tie(0),ios_base::sync_with_stdio(0)
#define popcnt(x) __builtin_popcount(x)
using namespace std;


ll dp[20][20],F[20];

ll solve(int n,int k){
	if(dp[n][k] != -1) return dp[n][k];
	if(k == 0) return F[n];
	return dp[n][k] = solve(n,k - 1) - solve(n - 1,k  - 1);
}

int main(){
	int T,K,n,k;
	pre();
	fill(&dp[0][0],&dp[20][0],-1);
	F[0] = 1;
	loop(i,19) F[i + 1] = F[i] * (i + 1);
	cin >> T;
	while(T--){
		cin >> K >> n >> k;
		cout << K << " " << solve(n,k) << endl;
	}
	return 0;
}
