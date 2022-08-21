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

const int mod = 1e9 + 7;
int add(int a, int b) {
	a += b;
	if(a >= mod) a -= mod;
	return a;
}
int mul(int a, int b) {
	return (a*(ll)b)%mod;
}

const int MAX = 1 << 20;

int n;
int A[1 << 20];
int fact[MAX], invInt[MAX], invFact[MAX];
// int solve(int i, int h) {
// 	if(h >= A[i]) return 0;
// 	return solve(i + 1, h) + solve(i, h + 1) + 1;
// }


int C(int n, int k) {
	if(k > n) return 0;
	return mul(fact[n], mul(invFact[k], invFact[n - k]));
}
int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d", &n);
	loop(i, n + 1) scanf("%d", A + i);
	// cout << solve(0, 0) << endl;
	invInt[1] = 1;
	for(int i = 2; i < MAX; i++)
		invInt[i] = mod - mul(mod/i, invInt[mod%i]);

	fact[0] = invFact[0] = 1;
	for(int i = 1; i < MAX; i++) {
		fact[i] = mul(fact[i - 1], i);
		invFact[i] = mul(invFact[i - 1], invInt[i]);
	}

	int ans = 0;
	loop(i, n + 1) if(A[i]) {
		ans = add(ans, C(i + A[i], i + 1));
	}
	cout << ans << endl;
	return 0;
}
