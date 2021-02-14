#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
typedef std::vector<int> vi;
typedef std::pair<int,int> pi;
typedef std::vector<pi> vp;
typedef long long ll;
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
template<class A,class B>
std::ostream& operator << (std::ostream& st,const std::pair<A,B> p) {
	st << "(" << p.first << ", " << p.second << ")";
	return st;
}
using namespace std;

const int mod = 998244353 ;

int add(int a, int b){
	a += b;
	if(a >= mod) a -= mod;
	if(a < 0) a += mod;
	return a;
}
int mul(int a, int b){
	return (a*(ll)b)%mod;
}

const int MAXN = 200*1000 + 10;
int n, m;
int A[MAXN];
int dp[2][MAXN][3];

int W[3];

int solve(int m, int prv, int dp[MAXN][3]){
	if(m == 0) return prv != 2;
	int & ret = dp[m][prv];
	if(ret != -1) return ret;
	ret = 0;
	loop(k, 3) {
		if(k != prv) ret = add(ret, mul(W[k], solve(m - 1, k, dp)));
		else if(k == 1) ret = add(ret, mul(W[k] - 1, solve(m - 1, k, dp)));
	 }
//	cerr << m << " " << prv << ": " << ret << endl;
	return ret;
}

int f(int n, int a, int b){
	if(n == 0) return 1;
	int ret = 1;
	if(a == 0 && b == 0){
		ret = m;
		loop(i, n-1) ret = mul(ret, m - 1);
	} else {
		if(b == 0) swap(a, b);
		if(a == 0){
			loop(i, n) ret = mul(ret, m - 1);
		} else {
			if(a == b) {
				W[0] = 0;
				W[1] = m - 1;
				W[2] = 1;
				ret = solve(n, 2, dp[0]);
			} else {
				W[0] = 1;
				W[1] = m - 2;
				W[2] = 1;
//				cerr << endl;
				ret = solve(n, 0, dp[1]);
//				cerr << endl;
			}					
		}
	}
//	cout << n << " " << a << " " << b << ": " << ret << endl;
	return ret;
}

int solve(vi & A){
	int prv = 0, len = 0, ret = 1;
	for(int x : A){
		if(x == -1){
			len++;
		} else {
			ret = mul(ret, f(len, prv, x));
			len = 0;
			prv = x;
		}
	}
	ret = mul(ret, f(len, 0, prv));
	return ret;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d", &n, &m);
	loop(i, n) scanf("%d", A + i);
	for(int i = 1; i + 1 < n; i++)
		if(A[i - 1] == A[i + 1] && A[i - 1] != -1){
			puts("0");
			return 0;
		}

	vi U[2];
	loop(i, n) U[i & 1].push_back(A[i]);

	memset(dp, -1, sizeof dp);
	int ans = 1;
	loop(i, 2) ans = mul(ans, solve(U[i]));
	
	printf("%d\n", ans);
	return 0;
}
