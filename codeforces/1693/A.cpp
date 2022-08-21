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


bool check(vi & A) {
	while(!A.empty() && A.back() == 0) A.pop_back();
	reverse(all(A));
	ll s = 0;
	bool first = true;
	for(auto a : A) {
		if(!first && s >= 0) return false;
		first = false;
		s += a;
	}
	return s == 0;
}

void tc() {
	static vi A;
	int n; scanf("%d", &n);
	A.resize(n);
	for(int & a : A) scanf("%d", &a);
	puts(check(A) ? "Yes" : "No");
}

int main(){
	freopen("in.in", "r", stdin);
	test_cases();
	return 0;
}
