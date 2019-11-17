#ifdef ACTIVE
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
#define tc() int T; scanf("%d",&T); for(int t = 1;t <= T;t++)
using namespace std;


ll bf(int n) {
	ll ans = 0;
	for(int i = 1;i <= n;i++)
		ans += n/i;
	return ans;
}

ll solve(ll n) {
	ll l = 1;
	ll ans = 0;
	while(l <= n) {
		ll s = l,e = n;
		ll v = n/s;
		while(s < e) {
			ll m = s + (e-s+1)/2;
			if(v == n/m) s = m;
			else e = m-1;
		}
		ans += v*(s - l + 1);
		l = s + 1;
	}
	return ans;
}

ll solve2(ll n) {
	ll u = ceil(sqrt(n)) + 1;
	while(u*u > n) u --;
	ll ans = 0;
	for(int i = 1;i <= u;i++)
		ans += n/i;
	ans = 2*ans - u*u;
	return ans;
}

int main(){
	freopen("perechi3.in", "r", stdin);
	freopen("perechi3.out", "w", stdout);
	int T; scanf("%d",&T);
	while(T--) {
		ll n; scanf("%lld",&n);
		printf("%lld\n",solve2(n));
	}
	return 0;
}
#endif
