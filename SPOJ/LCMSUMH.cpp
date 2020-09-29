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

const int mod = 1e9 + 7, i2 = 500000004;
mt19937 rng1(chrono::steady_clock::now().time_since_epoch().count());
mt19937 rng2(chrono::steady_clock::now().time_since_epoch().count());

int add(int a, int b, int mod){
	a += b;
	if(a >= mod) a -= mod;
	if(a < 0) a += mod;
	return a;
}
int mul(int a, int b, int mod){
	return (a*(ll)b)%mod;
}
int powmod(int a, int p, int mod){
	if(p == 0) return 1;
	int b = 1;
	for(;p > 1; p >>= 1){
		if(p & 1) b = mul(a, b, mod);
		a = mul(a, a, mod);
	}
	return mul(a, b, mod);
}
int inv(int a, int mod){
	assert(a != 0);
	return powmod(a, mod - 2, mod);
}

long long mult(long long a, long long b, long long mod) {
    long long result = 0;
    while (b) {
        if (b & 1)
            result = (result + a) % mod;
        a = (a + a) % mod;
        b >>= 1;
    }
    return result;
}

long long f(long long x, long long c, long long mod) {
    return (mult(x, x, mod) + c) % mod;
}


long long rho(long long n, long long x0=2, long long c=1) {
    long long x = x0;
    long long y = x0;
    long long g = 1;
    while (g == 1) {
        x = f(x, c, n);
        y = f(y, c, n);
        y = f(y, c, n);
        g = __gcd(abs(x - y), n);
    }
    return g;
}

long long brent(long long n, long long x0=2, long long c=1) {
    long long x = x0;
    long long g = 1;
    long long q = 1;
    long long xs, y;

    int m = 128;
    int l = 1;
    while (g == 1) {
        y = x;
        for (int i = 1; i < l; i++)
            x = f(x, c, n);
        int k = 0;
        while (k < l && g == 1) {
            xs = x;
            for (int i = 0; i < m && i < l - k; i++) {
                x = f(x, c, n);
                q = mult(q, abs(y - x), n);
            }
            g = __gcd(q, n);
            k += m;
        }
        l *= 2;
    }
    if (g == n) {
        do {
            xs = f(xs, c, n);
            g = __gcd(abs(xs - y), n);
        } while (g == 1);
    }
    return g;
}
using u64 = uint64_t;
using u128 = __uint128_t;

u64 binpower(u64 base, u64 e, u64 mod) {
    u64 result = 1;
    base %= mod;
    while (e) {
        if (e & 1)
            result = (u128)result * base % mod;
        base = (u128)base * base % mod;
        e >>= 1;
    }
    return result;
}

bool check_composite(u64 n, u64 a, u64 d, int s) {
    u64 x = binpower(a, d, n);
    if (x == 1 || x == n - 1)
        return false;
    for (int r = 1; r < s; r++) {
        x = (u128)x * x % n;
        if (x == n - 1)
            return false;
    }
    return true;
};


//determnistic
bool MillerRabin(u64 n) { // returns true if n is prime, else returns false.
    if (n < 2)
        return false;

    int r = 0;
    u64 d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        r++;
    }

    for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n == (unsigned)a)
            return true;
        if (check_composite(n, a, d, r))
            return false;
    }
    return true;
}

vector<ll> primes;
map<ll, int> M;

int solve(ll p, int e){
	p %= mod;
	ll q = 1;
	loop(i, e) q = mul(q, p, mod);
	q = mul(q, q, mod);
	q = mul(q, p, mod);
	q = add(q, 1, mod);
	return mul(q, inv((p+1)%mod, mod), mod);
}

void work(ll n, int i){
	if(n <= 1) return;
	while(i < sz(primes)){
		while(n%primes[i] == 0){
			n /= primes[i];
			M[primes[i]]++;
		}
		i++;
	}
	if(n <= 1) return;
	if(MillerRabin(n)) {
		ll p = n;
		if(!M.count(p)) 
			primes.pb(n);
		M[p]++;
		return;
	}
	ll f = n;
	while(f == n)
		f = brent(n, rng1(), rng2());
	
	work(f, i);
	work(n/f, i);
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--){
		ll n; scanf("%lld", &n);
		M.clear();
		primes.clear();
		work(n, 0);
		int res = 1;
		for(auto pe : M){
			ll p; int e;
			tie(p, e) = pe;
			res = mul(res, solve(p, e), mod);
		}
		res = add(res, 1, mod);
		res = mul(res, n%mod, mod);
		res = mul(res, i2, mod);
		printf("%d\n", res);
	}
	return 0;
}
