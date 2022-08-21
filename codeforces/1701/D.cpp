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

int n;
int A[1 << 20], P[1 << 20];

void tc() {
	static vector<tuple<int, int, int>> I;
	scanf("%d", &n);
	loop(i, n) scanf("%d", A + i + 1);
	I.clear();
	for(int i = 1; i <= n; i++) {
		// k = A[i]
		int s = -1, e = -1;
		if(A[i] == 0) {
			s = i + 1;
			e = n;
		} else {
			s = i / (A[i] + 1) + 1;
			e = i / A[i];
		}
		I.emplace_back(s, e, i);
		// cerr << i << ": " << pi(s, e) << endl;
	}
	sort(all(I));
	reverse(all(I));

	set<pi> RI;
	for(int s = 1; s <= n; s++) {
		while(!I.empty()) {
			auto [l, r, i] = I.back();
			if(l > s) break;
			I.pop_back();
			RI.emplace(r, i);
		}
		assert(!RI.empty());
		int i = RI.begin()->second;
		RI.erase(RI.begin());
		P[i] = s;
	}
	loop(i, n) printf("%d ", P[i + 1]);
	puts("");
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	test_cases();
	return 0;
}
