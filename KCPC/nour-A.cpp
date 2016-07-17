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

bool is_prime(int n){
	for(int i = 2;i*i <= n;i++)
		if(n%i == 0) 
			return 0;
	return n > 1;
}

int A[1000],n,dp[1000];

int solve(int i){
	if(dp[i] != -1) return dp[i];
	dp[i] = 0;
	for(int j = i + 1;j < ::n;j++)
		if(A[i] <= A[j])
			dp[i] = max(dp[i],solve(j));
	return ++dp[i];
}

int main(){
	int T,n;
	cin >> T;
	while(T--){
		::n = 0;
		cin >> n;
		loop(i,n){
			scanf("%d",A + ::n);
			if(!is_prime(A[::n])) ::n++;
		}
		fill(dp,dp + ::n,-1);
		int ans = 0;
		loop(i,::n) ans = max(ans,solve(i));
		printf("%d\n",ans);
	}
	return 0;
}
