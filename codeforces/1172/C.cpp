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
 
 
const int mod = 998244353;
int add(int a, int b, int mod){
	a += b;
	if(a >= mod) a -= mod;
	if(a < 0) a += mod;
	return a;
}
int mul(int a, int b, int mod){
	return (a*(ll)b)%mod;
}
int powmod(int a, int p, int mod){
	if(p == 0) return 1;
	int b = 1;
	for(;p > 1; p >>= 1){
		if(p & 1) b = mul(a, b, mod);
		a = mul(a, a, mod);
	}
	return mul(a, b, mod);
}
int inv(int a, int mod){
	return powmod(a, mod - 2, mod);
}
 
 
const int MAXN = 55, MAXM = 55;
int IA[MAXN], IW[MAXN], n, m;
int S[2];
 
int W[3];
int dir;
int dp[MAXM][MAXM][MAXM];
 
int solve(int cnt0, int cnt1, int cntI){
	assert(cnt0 + cnt1 + cntI <= m);
	if(cnt0 + cnt1 + cntI == m) return 0;
	int & ret = dp[cnt0][cnt1][cntI];
	if(ret != -1) return ret;
	
	ret = 0;
	int a = W[0] - cnt0;
	int b = W[1] + cnt1;
	int c = W[2] + dir * cntI;
	int scaler = a + b + c;
	
	if(a) ret = add(ret, mul(a, solve(cnt0 + 1, cnt1, cntI), mod), mod);
	if(b) ret = add(ret, mul(b, solve(cnt0, cnt1 + 1, cntI), mod), mod);
	if(c) ret = add(ret, mul(c, add(dir, solve(cnt0, cnt1, cntI + 1), mod), mod), mod);
	ret = mul(ret, inv(scaler, mod), mod);
	return ret;
}
 
int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d", &n, &m);
	loop(i, n) scanf("%d", IA + i);
	loop(i, n) scanf("%d", IW + i);
	loop(i, n) S[IA[i]] += IW[i];
	
	loop(i, n){
		W[0] = S[0];
		W[1] = S[1];
		W[2] = IW[i];
		W[IA[i]] -= IW[i];
//		prArr(W, 3, int);
		memset(dp, -1, sizeof dp);
		dir = 2*IA[i] - 1;
		
		int ans = add(IW[i], solve(0, 0, 0), mod);
		printf("%d\n", ans);
		
	}
	
	return 0;
}
