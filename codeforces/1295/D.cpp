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


vector<ll> getPrimes(ll x){
	vector<ll> ret;
	for(ll i = 2;i*i <= x;i++){
		if(x%i) continue;
		ret.pb(i);
		while(x%i == 0) x /= i;
	}
	if(x > 1) ret.pb(x);
	return ret;
}
ll solve(ll a, ll m){
	ll g = __gcd(a, m);
	ll m0 = m/g;
	ll a0 = a/g;
	ll lim = m0 - 1;
	ll res = 0;
	auto primes = getPrimes(m0);
	for(int msk = 0; msk < (1 << sz(primes)); msk++){
		int sgn = 1;
		ll f = 1;
		loop(i, sz(primes)) if(msk & (1 << i)) {
			f *= primes[i];
			sgn *= -1;
		}
		res += sgn * (lim / f);
	}
	
	return res;
}



int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d",&T);
	while(T--){
		ll a, m; scanf("%lld %lld", &a, &m);
		printf("%lld\n", solve(a, m));
	}
	return 0;
}
