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

const int mod = 1e9 + 7;
int add(int a, int b){
	a += b;
	if(a >= mod) a -= mod;
	if(a < 0) a += mod;
	return a;
}
int mul(int a, int b){
	return (a*(ll)b)%mod;
}

const int MAXN = 5000 + 5, MAXK = 5000 + 5;
int dp[MAXN][MAXK], dp2[MAXN][MAXK];
int coef[MAXN];
int A[MAXN];
int n, K, Q;

int solve(int i, int k){
	if(k == K) return 1;
	int & ret = dp[i][k];
	if(ret != -1) return ret;
	ret = 0;
	if(i) ret = add(ret, solve(i - 1, k + 1));
	if(i + 1 < n) ret = add(ret, solve(i + 1, k + 1));
	return ret;
}

int solve2(int i, int k){
	if(k == 0) return 1;
	int & ret = dp2[i][k];
	if(ret != -1) return ret;
	ret = 0;
	if(i) ret = add(ret, solve2(i - 1, k - 1));
	if(i + 1 < n) ret = add(ret, solve2(i + 1, k - 1));
	return ret;
}




int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	memset(dp, -1, sizeof dp);
	memset(dp2, -1, sizeof dp2);
	scanf("%d %d %d", &n, &K, &Q);
	loop(i, n) scanf("%d", A + i);
	int tot = 0;
	loop(i, n){
		for(int k = 0; k <= K; k++) coef[i] = add(coef[i], mul(solve(i, k), solve2(i, k)));
		tot = add(tot, mul(A[i], coef[i]));
	}
	loop(q, Q){
		int i, x; scanf("%d %d", &i, &x);
		i--;
		tot = add(tot, -mul(A[i], coef[i]));
		A[i] = x;
		tot = add(tot, mul(A[i], coef[i]));
		printf("%d\n", tot);
	}
	return 0;
}
