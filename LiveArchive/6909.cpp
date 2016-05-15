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
int n,m,k;
ll C[501][501],F[501],L[501];

ll g(int l,int q){
	if(l == 0) return q == 0;
	if(dp[l][q] != -1) return dp[l][q];
	dp[l][q] = 0;
	loop(i,q) dp[l][q] = (dp[l][q] + g(l - 1,i))%mod;
	return dp[l][q];
}

void init(){
	loop(i,501){
		F[i] = i ? (F[i] * i)%mod : 1;
		C[i][0] = 1;
		loop(j,i)
			C[i][j + 1] = (C[i - 1][j] + C[i - 1][j + 1])%mod;
		L[i] = 0;
		loop(j,501) L[i] = (L[i] + g(i,j))%mod;
	}
}


ll f(int pos,int mx){
	if(mx < k) return 0;
	if(pos - k - 1 > n - p) return 0; 
	int r = n - k;
	ll ans = (C[mx - 1][k - 1] * F[k])%mod;
	ans = (ans * F[n - pos])%mod;
	C[r][pos - k - 2]*(p - 1
	return 
}

int main(){
		
}
