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

int n,k;
ll dp[20][1 << 20];

ll solve(int last,int mask){
	if((mask + 1) == (1 << n)) return 1;
	if(dp[last][mask] != -1) return dp[last][mask];
	ll & r = dp[last][mask];
	r = 0;
	loop(i,n) if(!(mask & (1 << i)) && abs(i - last) <= k)
			r += solve(i,mask | (1 << i));
	return r;
}

int main(){
	pre();
	int T;
	cin >> T;
	while(T--){
		cin >> n >> k;
		fill(&dp[0][0],&dp[n][0],-1);
		ll ans = 0;
		loop(i,n) ans += solve(i,1 << i);	
		cout << ans << "\n";
	//	cout << flush;
	}	
	return 0;
}

