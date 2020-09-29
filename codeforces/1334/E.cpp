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

const int mod = 998244353;
int add(int a, int b){
	a += b;
	if(a >= mod) a -= mod;
	if(a < 0) a += mod;
	return a;
}
int mul(int a, int b){
	return (a*(ll)b)%mod;
}

ll D;
vector<ll> primes;

void factor(){
	for(ll x = 2; x*x <= D; x++) if(D%x == 0){
		primes.pb(x);
		while(D%x == 0) D /= x;
	}
	if(D > 1) primes.pb(D);
}

const int MAXN = 1024;

int C[MAXN][MAXN];
void init(){
	for(int n = 0; n < MAXN; n++){
		C[n][0] = C[n][n] = 1;
		for(int k = 1; k < n; k++){
			C[n][k] = add(C[n-1][k-1], C[n-1][k]);
		}
	}
}

int solve(ll a){
	static vi E;
	E.clear();
	int ret = 1, se = 0;
	for(ll p : primes) if(a%p == 0) {
		int e = 0;
		while(a%p == 0){
			e ++;
			a /= p;
		}
		E.pb(e);
		se += e;
	}
	for(int e : E){
		ret = mul(ret, C[se][e]);
		se -= e;
	}
	return ret;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	init();
	scanf("%lld", &D);
	factor();
	int m; scanf("%d", &m);
	while(m--){
		ll A, B; scanf("%lld %lld", &A, &B);
		ll g = __gcd(A, B);
		printf("%d\n", mul(solve(A/g), solve(B/g)));
	}
	return 0;
}
