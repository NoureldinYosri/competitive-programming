#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define popcnt(x) __builtin_popcountll(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
using namespace std;

const int mod = 1e9 + 7;
int dp[51][51][51][51];
int dp2[51][51];

int add(int a,int b){
	a += b;
	if(a >= mod) a -= mod;
	if(a < 0) a += mod;
	return a;
}

int mul(int a,int b){
	return (a*1LL*b)%mod;
}

int solve(int,int);

int solve2(int n,int m){
	if(dp2[n][m] != -1) return dp2[n][m];
	int & ret = dp2[n][m];
	ret = 0;
	for(int i = 0;i <= n;i++)
		for(int tm = m;tm <= 50;tm++){
			int tmp = mul(solve(i,m),solve(n-i,tm));
			if(tm != m){
				tmp = add(tmp,mul(solve(i,tm),solve(n-i,m)));
			}
			ret = add(ret,tmp);
		}
//	cerr << n << " " << m << " -> " << ret << endl;
	return ret;
}


int solve4(int n,int m,int lstn,int lstm){
	int res = 0;
	if(dp[n][m][lstn][lstm] != -1) return dp[n][m][lstn][lstm];
	if(n == 0) return dp[n][m][lstn][lstm] = m == 1;
	if(m == 0) return dp[n][m][lstn][lstm] = 0;
	if(m > n + 1) return dp[n][m][lstn][lstm] = 0;
	if(lstn >= n || lstm > m) return dp[n][m][lstn][lstm] = 0;
//	cerr << "calling " << n << " " << m << endl;
	int & ret = dp[n][m][lstn][lstm];
	if(n == 0) res = ret = (m == 1);
	else {
		ret = add(solve4(n,m,lstn + 1,lstm),solve4(n,m,lstn,lstm + 1));
		ret = add(ret,-solve4(n,m,lstn+1,lstm+1));
		int tmp = solve4(n-1-lstn,m-lstm,lstn,lstm);
		tmp = mul(tmp,solve2(lstn,lstm));
		ret = add(ret,tmp);
		res = ret;
	}
//	cerr << n << " " << m << " " << lstn << " " << lstm << " -> " << res << endl;
	return res;
}

int solve(int n,int m){
	if(dp[n][m][0][1] != -1) return solve4(n,m,0,1);
	int res = solve4(n,m,0,1);
	if(res) cerr << n << " " << m << " -> " << res << endl;
	return res;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	int n,m; cin >> n >> m;
	memset(dp,-1,sizeof dp);
	memset(dp2,-1,sizeof dp2);
	cout << solve(n,m) << endl;
	return 0;
}
