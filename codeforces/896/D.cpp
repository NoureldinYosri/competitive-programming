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

int add(ll a, int b, int m){
	a += b;
	if(a >= m) a -= m;
	if(a < 0) a += m;
	return a;
}

int mul(int a, int b, int m){
	return (a*(ll)b)%m;
}

vp primes;
vector<vi> cnt;
vector<vi> prod;
vi fact;

int powmod(int x, int p, int m){
	if(p == 0) return 1%m;
	int y = 1;
	for(; p > 1; p >>= 1){
		if(p & 1) y = mul(x, y, m);
		x = mul(x, x, m);
	}
	return mul(x, y, m);
}

int phi;

int inv(int x, int m){
	return powmod(x, phi - 1, m);
}

void factor(int x){
	for(int i = 2; i*i <= x; i++) if(x%i == 0) {
		int e = 0;
		while(x%i == 0) {
			x /= i;
			e++;
		}
		primes.emplace_back(i, e);
	}
	if(x > 1) primes.emplace_back(x, 1);
}

void init(int n, int m){
	factor(m);
	phi = m;
	loop(i, sz(primes)){
		int p = primes[i].first;
		phi -= phi/p;
	}
	
	cnt.resize(n + 1, vi(sz(primes), 0));
	fact.resize(n + 1, 1);
	for(int i = 1; i <= n; i++){
		int j = i;
		loop(k, sz(primes)){
			int p = primes[k].first;
			cnt[i][k] = cnt[i-1][k];
			while(j%p == 0) j /= p, cnt[i][k]++;
		}
		fact[i] = mul(fact[i-1], j, m);
	}
	prod.resize(sz(primes));
	loop(k, sz(primes)){
		int N = cnt[n][k], p = primes[k].first;
		prod[k].resize(N + 1, 1);
		for(int i = 1; i <= N; i++)
			prod[k][i] = mul(prod[k][i - 1], p, m); 
	}
}

int hC(int n, int k, int m){
	int res = 1;
	bool isZero = true;
	loop(i, sz(primes)){
		auto [p, e] = primes[i];
		int h = cnt[n][i] - cnt[k][i] - cnt[n-k][i];
		assert(h >= 0);
		isZero &= h >= e;
//		cerr << p << ": " << h << " " << e << "\t" << cnt[n][i] << " " << cnt[k][i] << " " << cnt[n-k][i] << endl;
		res = mul(res, prod[i][h], m);	
	}
	return isZero ? 0 : res;
}

int C(int n, int k, int m){
	if(k > n) return 0;
	if(k < 0) return 0;
	int res = 1;
	res = mul(res, fact[n], m);
	res = mul(res, inv(fact[k], m), m);
	res = mul(res, inv(fact[n - k], m), m);
	//cerr << "\t" << res << " " << hC(n, k, m) << endl;
	res = mul(res, hC(n, k, m), m);
	//cout << pi(n, k) << ": " << res << endl;
	return res;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int n, mod, l, r; cin >> n >> mod >> l >> r;
	if(mod == 1){
		puts("0");
		return 0;
	}
	init(n, mod);
	int res = 0;
	for(int m = 0; m <= n; m++){
		int A = C(m, (m - l) >> 1, mod);
		int B = C(m, ((m - r - 1) >> 1), mod);
		int tmp = add(A, -B, mod);
//		cerr << m << " " << ((m - l) >> 1) << ": " << tmp << "\t(" << A << " - " << B << ") * " << C(n, m, mod) << " C(" << n << ", " << m << ")" << endl;
		tmp = mul(tmp, C(n, m, mod), mod);
		res = add(res, tmp, mod);
	}
	cout << res << endl;

	return 0;
}
