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

int n, r1, r2, r3, d;
vi A;

const int MAXN = 1000*1000;
ll dp[MAXN][2];

ll solve(int i, bool tail){
	if(i == n-1) {
		ll ret, a = A[i];
		ret = tail*d + min(r1, r3)*a + r3;
		ll v0 = min(min(r1, r3)*(a + 1), r2 + 0LL) + min({r1, r2, r3});
		ret = min(ret, v0 + 2*d);
		return ret;
	}
	ll & ret = dp[i][tail];
	if(ret != -1) return ret;
	
	ll a = A[i];
	ret = 2*tail*d + min(r1, r3)*a + r3 + solve(i + 1, 0);
	ll v0 = min(min(r1, r3)*(a + 1), r2 + 0LL) + min({r1, r2, r3});
	if(tail) {
		ret = min(ret, v0 + 2*d + solve(i + 1, 0));
	} else {
		ret = min(ret, v0 + solve(i + 1, 1));
	}

	ret += d;
	return ret;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d %d %d %d", &n, &r1, &r2, &r3, &d);
	A.resize(n);
	for(int & a : A) scanf("%d", &a);
	
	memset(dp, -1, sizeof dp);
	cout << solve(0, 0) << endl;

	return 0;
}
