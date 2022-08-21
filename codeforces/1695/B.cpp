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

int A[1 << 10];
int n;

void tc() {
		scanf("%d", &n);
		loop(i, n) scanf("%d", A + i);
		if(n & 1) {
			puts("Mike");
			return;
		}
		int m = *min_element(A, A + n);
		loop(i, n) A[i] -= m;
		static vi zeros[2];
		loop(c, 2) zeros[c].clear();
		loop(i, n) if(A[i] == 0) zeros[i & 1].push_back(i);
		if(zeros[0].empty()) {
			puts("Mike");
			return;
		}
		if(zeros[1].empty()) {
			puts("Joe");
			return;
		}
		puts((zeros[0][0] < zeros[1][0]) ? "Joe" : "Mike");
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	test_cases();
	return 0;
}
