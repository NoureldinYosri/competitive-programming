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

int A[1 << 20], n;

void tc() {
	scanf("%d", &n);
	loop(i, n) scanf("%d", A + i);
	sort(A, A + n);
	printf("%d\n", A[n-1] - A[1] - A[0] + A[n - 2]);
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	test_cases();	
	return 0;
}
