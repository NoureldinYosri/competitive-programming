#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
typedef std::vector<int> vi;
typedef std::pair<int,int> pi;
typedef std::vector<pi> vp;
typedef long long ll;
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
template<class A,class B>
std::ostream& operator << (std::ostream& st,const std::pair<A,B> p) {
	st << "(" << p.first << ", " << p.second << ")";
	return st;
}
using namespace std;

int n, m;
vi A, B;
ll pref[1 << 20];


void tc(){
	scanf("%d %d", &n, &m);
	A.resize(n);
	B.resize(m);
	for(int & x : A) {
		scanf("%d", &x);
		x--;
	}
	for(int & y : B) scanf("%d", &y);
	loop(i, m) pref[i] = B[i] + (i ? pref[i - 1] : 0);
	sort(all(A));
	ll ans = 0;
	for(int a : A) ans += B[a];
	ll tmp = 0;
	loop(i, n) {
		if(n-i <= A[i]) {
			int need = n - i;
			ans = min(ans, tmp + pref[need - 1]);
		}
		tmp += B[A[i]];
	}
	printf("%lld\n", ans);
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--) tc();
	return 0;
}
