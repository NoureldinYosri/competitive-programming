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


ll C2(ll m) {
	return (m*(m-1)) >> 1;
}
ll C3(ll m) {
	return (m*(m-1)*(m-2)) / 6;
}

ll f[1 << 20];

void work(int l, int r) {
	for(int a = r; a; a--) {
		int low = (l + a - 1)/a, high = r/a;
		f[a] = C2(high - low);
		for(int k = 2*a; k <= r; k += a)
			f[a] -= f[k];
	}
}

void tc() {
	int l, r; scanf("%d %d", &l, &r);
	ll ans = C3(r - l + 1);
	work(l, r);
	prArr(f + 1, r, ll);
	for(int a = 1; a <= r; a++)
		ans -= f[a];
	printf("%lld\n", ans);
	exit(0);
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	test_cases();
	return 0;
}
