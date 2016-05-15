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


ll bus[1 << 20],train[1 << 20],ctrain[1 << 20];
ll dp[1 << 20];
int N;

ll solve(int n){
	if(n >= N) return 0;
	if(dp[n] != -1) return dp[n];
	dp[n] = LLONG_MAX;
	dp[n] = min(dp[n],bus[n] + train[n]*2 + solve(n + 1));
	dp[n] = min(dp[n],3 + train[n]*2 + solve(n + 1));
	dp[n] = min(dp[n],6 + solve(n + 1));
	dp[n] = min(dp[n],18 + (ctrain[n + 7] - ctrain[n])*2 + solve(n + 7));
	dp[n] = min(dp[n],36 + solve(n + 7));
	dp[n] = min(dp[n],45 + (ctrain[n + 30]- ctrain[n])*2 + solve(n + 30));
	dp[n] = min(dp[n],90 + solve(n + 30));
	return dp[n];
}

int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%d",&N);
		ctrain[0] = 0;
		loop(i,N){
			scanf("%lld %lld",bus + i,train + i);
			ctrain[i + 1] = train[i] + ctrain[i];
		}
		loop(i,(1 << 20) - N - 1) ctrain[i + N + 1] = ctrain[N];
		fill(dp,dp + (1 << 20),-1);
		printf("%lld\n",solve(0));
	}
	return 0;
}
