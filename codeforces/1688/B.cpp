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

const int K = 5;
vi A;

int f(ll x) {
	int ret = 0;
	while(x%2 == 0) {
		x >>= 1;
		ret++;
	}
	return ret;
}

int maybe(int ) {
	int ans = 0;


	return ans;
}

ll solve(bool anyOdd) {
	if(A.empty()) return 0;
	if(anyOdd) return sz(A);
	sort(all(A));
	int ans = INT_MAX;
	loop(i, sz(A)) {
		ll sum = 0;
		for(int j = i; j < sz(A) && j-i+1 <= K; j++) {
			sum += A[j];
			int s = f(sum), len = j - i + 1;
			int tmp = (len - 1) + (s + (s > 1)) +  (sz(A) - len);
			ans = min(ans, tmp);
		}
	}
	ans = min(ans, sz(A) - 1 + f(accumulate(all(A), 0LL)));
	int s = f(A[0] + A.back());
	ans = min(ans, 1 + (s + (s > 1)) + sz(A) - 2);
	ans = min(ans, maybe());
	return ans;
}

void tc() {
	int n; scanf("%d", &n);
	A.clear();
	bool anyOdd = false;
	loop(i, n) {
		int x; scanf("%d", &x);
		if(x & 1) {
			anyOdd = true;
			continue;
		}
		A.push_back(x);
	}
	printf("%lld\n", solve(anyOdd));
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	test_cases();
	return 0;
}
