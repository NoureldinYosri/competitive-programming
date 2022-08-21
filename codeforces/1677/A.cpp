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


const int MAXN = 5 << 10;
int pref[MAXN][MAXN], suff[MAXN][MAXN];
int A[MAXN], n;

void tc() {
	scanf("%d", &n);
	loop(i, n) scanf("%d", A + i), A[i]--;
	loop(i, n) {
		fill(pref[i], pref[i] + n, 0);
		if(i) {
			loop(j, n) pref[i][j] = pref[i - 1][j];
		} 
		for(int v = A[i]; v < n; v++)
			pref[i][v]++;
	}
	for(int i = n-1; i >= 0; i--) {
		fill(suff[i], suff[i] + n, 0);
		if(i + 1 < n) {
			loop(j, n) suff[i][j] = suff[i + 1][j];
		}
		for(int v = A[i]; v < n; v++)
			suff[i][v]++;
	}
/*	loop(i, n) {
		prArr(pref[i], n, int);
		prArr(suff[i], n, int);
	}
*/	ll ans = 0;
	for(int b = 1; b < n; b++)
		for(int c = b + 1; c + 1 < n; c++) {
			ans += pref[b - 1][A[c]] * (ll)suff[c + 1][A[b]];
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
