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

int n, m;
vi A, B;

void tc() {
	scanf("%d %d", &n, &m);
	A.resize(n);
	for(int & a : A) scanf("%d", &a);
	int k; scanf("%d", &k);
	B.resize(k);
	for(int & b : B) scanf("%d", &b);
	if(accumulate(all(A), 0LL) != accumulate(all(B), 0LL)) {
		puts("No");
		return;
	}
	static vector<pair<int, ll>> aux;
	aux.clear();
	for(int a : A) {
		int c = 1;
		while(a%m == 0) {
			c *= m;
			a /= m;
		}
		if(aux.empty() || aux.back().first != a) aux.emplace_back(a, c);
		else aux.back().second += c;
	}
	while(!B.empty()) {
		if(aux.empty()) break;
		int c = 1, b = B.back();;
		while(b%m == 0) {
			b /= m;
			c *= m;
		}
		if(c > aux.back().second || b != aux.back().first) {
			puts("No");
			return;
		}
 		B.pop_back();
 		aux.back().second -= c;
		if(aux.back().second == 0) aux.pop_back();
	}
	puts((aux.empty() && B.empty()) ? "Yes" : "No");
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	test_cases();
	return 0;
}
