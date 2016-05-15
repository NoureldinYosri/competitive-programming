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

const int mod = 1e9 + 7;
ll dp[1001][1001];
int A[1001];
ll solve(int n,int k){
	if(n == -1) return 1;
	if(dp[n][k] != -1) return dp[n][k];
	
	return dp[n][k] = solve(n - 1,k - 1);
}
int main(){
	int T,N,K,a; ll ans;
	scanf("%d",&T);
	loop(t,T){
		ans = INT_MAX;
		scanf("%d %d",&N,&K);
		fill(&dp[0][0],&dp[N][0],-1);
		loop(i,N) scanf("%d",A + i);
		printf("%lld\n",solve(N - 1,K)); 
	}
	return 0;
}
