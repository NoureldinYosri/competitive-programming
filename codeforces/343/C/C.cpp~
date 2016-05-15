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

int n,m;
char s[1 << 20];
const ll mod = 1e9 + 7;

ll dp1[2001][2001],dp2[2001][2001];

ll solve(int L,int pre,ll dp[2001][2001]){
	if(pre > L) return 0;
	if(pre < 0) return 0;
	if(L == 0) return pre == 0;
	if(dp[L][pre] != -1) return dp[L][pre];
	return dp[L][pre] = (solve(L - 1,pre + 1,dp) + solve(L - 1,pre - 1,dp))%mod; 
}

int main(){
	loop(i,2001) loop(j,2001) dp1[i][j] = dp2[i][j] = -1;
	scanf("%d %d",&n,&m);
	scanf("%s",s);
	int pre = 0,f = 0,c = 0;
	loop(i,m){
		f += s[i] == '(';
		c += s[i] == ')';
		pre = max(pre,max(0,c - f));
	}
	f = max(f - c,0) + pre;
	ll ans = 0;
	n -= m;
	range(k,pre,n){
		if(n - k < f) break;
		loop(i,2001){
			ans += solve(k,pre + i,dp1) * solve(n - k,f + i,dp2);
			ans %= mod;
		}
	}
	cout << ans << endl;
	return 0;
}
