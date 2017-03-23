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

const int mod = 1e9 + 7;
int dp[5010][26];
int sum[5010];
int C[5010][5010];
int L;
string S;

int main(){
	loop(i,5000+1){
		C[i][0] = C[i][i] = 1;
		range(j,1,i-1) {
			C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
			if(C[i][j] >= mod) C[i][j] -= mod;
		}
	}
	cin >> L >> S;
	for(char ch : S){
		int c = ch - 'a';
		for(int l = L;l >= 1;l--){
			sum[l] -= dp[l][c];
			dp[l][c] = (l == 1);
			dp[l][c] += sum[l - 1] - dp[l - 1][c];
			if(dp[l][c] < 0) dp[l][c] += mod;
			sum[l] += dp[l][c];
			if(sum[l] >= mod) sum[l] -= mod;
			if(sum[l] < 0) sum[l] += mod;
		}
	}
	int ans = 0;
	range(l,1,L) {
		//prArr(dp[l],26,int);	
		ll c = C[L - 1][l - 1];
		loop(i,26){
			ans += (c*dp[l][i])%mod;
			if(ans >= mod) ans -= mod;
		}
	}
	cerr << ans << endl;
	cout << ans << endl;
	return 0;
}
