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

const int MAXN = 1000, mod = 1e9 + 7;

int add(int a, int b) {
	a += b;
	if(a >= mod) a -= mod;
	return a;
}
int mul(int a, int b) {
	return (a*(ll)b)%mod;
}


ll l, r, z;
int n;
int dp[60][MAXN][3];


int C[MAXN + 1][MAXN + 1];

void init() {
	for(int n = 0; n <= MAXN; n++) {
		C[n][0] = C[n][n] = 1;
		for(int k = 1; k < n; k++)
			C[n][k] = add(C[n-1][k], C[n-1][k-1]);
	}
}

ll h;
const int BITs = 60
;
int solve(int bit, int carry, int cmp){
	assert(carry < n);
	if(bit == BITs) return carry == 0 && cmp <= 1;
	int & ret = dp[bit][carry][cmp];
	if(ret != -1) return ret;
	ret = 0;
	int zBit = (z >> bit) & 1;
	int hBit = (h >> bit) & 1;
	
	for(int m = zBit; m <= n; m += 2) {
		int cBit = (carry + m) & 1;
		int ncmp = -1;
		
		if(cBit < hBit) ncmp = 0;
		else if(cBit == hBit) ncmp = cmp;
		else ncmp = 2;
		ret = add(ret, mul(C[n][m], solve(bit + 1, (carry + m) >> 1, ncmp)));
	}
	return ret;
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	init();
	cin >> n >> l >> r >> z;
	h = r;
	memset(dp, -1, sizeof dp);
	int ans = solve(0, 0, 1);
	memset(dp, -1, sizeof dp);
	h = l - 1;
	ans -= solve(0, 0, 1);
	if(ans < 0) ans += mod;
	cout << ans << endl;
	return 0;
}
