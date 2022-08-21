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

char txt[1 << 20];
vector<ll> lens;
vector<pair<ll, ll>> substrings;
int n;

char solve(ll k) {
	if(k < n) return txt[k];
	auto i = upper_bound(all(lens), k) - lens.begin();
	while(k >= n) {
		while(lens[i - 1] > k) i--;
		k -= lens[i - 1];
		k += substrings[i - 1].first;
	}
	return txt[k];
}

void tc() {
	int c, q;
	scanf("%d %d %d %s", &n, &c, &q, txt);
	lens.clear();
	lens.push_back(n);
	substrings.resize(c);
	for(auto & [l, r] : substrings) {
			scanf("%lld %lld", &l, &r);
			l--, r--;
			lens.push_back(lens.back() + r - l + 1);
	}
	loop(i, q) {
		ll k; scanf("%lld", &k);
		putchar(solve(k - 1));
		puts("");
	}
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	test_cases();
	return 0;
}
