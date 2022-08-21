#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
using vi = std::vector<int>;
using pi = std::pair<int,int>;
using vp = std::vector<pi>;
using ll = long long;
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
template<class A,class B>
std::ostream& operator << (std::ostream& st,const std::pair<A,B> p) {
	st << "(" << p.first << ", " << p.second << ")";
	return st;
}
void tc();
auto test_cases = [](){
	int T; scanf("%d", &T);
	while(T--) tc();
};
using namespace std;

int n, K;
ll A[1 << 20], pref[1 << 20];


ll f(ll m) {
	return (m*(m - 1)) >> 1;
}



ll g(int n, int m) {
	if(n == 1) {
		return m;
	}
	ll ret = 0;
	while(m >= n) {
		for(int i = 1; i < n; i++)
			ret += 2*i, m--;
	}
	for(int i = 1; i <= m; i++)
		ret += 2*i;	
	return ret;
}

void tc() {
	scanf("%d %d", &n, &K);
	loop(i, n) scanf("%lld", A + i);
	ll ans = 0;
	if(K >= n) {
		ans += accumulate(A, A + n, 0LL);
		ans += (n*(n - 1)) >> 1;
		K -= n;
		ans += g(n, K);
	} else {
		ans = (K*(K - 1LL)) >> 1;
		loop(i, n) pref[i + 1] = pref[i] + A[i];
		ll mx = 0;
		for(int i = K; i <= n; i++) mx = max(mx, pref[i] - pref[i - K]);
		ans += mx;
	}
	printf("%lld\n", ans);
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	test_cases();
	return 0;
}
