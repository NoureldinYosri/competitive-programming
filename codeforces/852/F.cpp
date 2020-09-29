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


int N, M, a, Q, mod;

int add(int a, int b, int m){
	a += b;
	if(a >= m) a -= m;
	if(a < 0) a += m;
	if(a < 0 || a >= m) a = (a%m + m)%m;
	return a;
}
int mul(int a, int b, int m){
	return (a*(ll)b)%m;
}
int powmod(int a, int x, int m){
	if(!x) return 1;
	int b = 1;
	for(; x > 1; x >>= 1){
		if(x&1) b = mul(a, b, m);
		a = mul(a, a, m);
	}
	return mul(a, b, m);
}


int phi(int n){
	int ret = n;
	for(int i = 2; i*i <= n; i++) if(n%i == 0){
		ret -= ret/i;
		while(n%i == 0) n /= i;
	}
	if(n > 1) ret -= ret / n;
	return ret;
}

vi getPrimes(int x){
	vi P;
	for(int i = 2; i*i <= x; i++)if(x%i == 0) {
		P.pb(i);
		while(x%i == 0) x /= i;
	}
	
	if(x > 1) P.pb(x);
	return P;
}

int getOrder(int a, int m){
	vi P = getPrimes(phi(m));
	for(int p : P)
		if(powmod(a, p, m) == 1)
			return p;
	assert(0);
	return -1;
}

vi getC(){
	vi fact(M + 1, 1), invInt(M + 1, 1), invFact(M + 1, 1);
	for(int i = 1; i < sz(fact); i++) fact[i] = mul(fact[i-1], i, mod);
	for(int i = 2; i < sz(invInt); i++) invInt[i] = mod - mul(mod/i, invInt[mod%i], mod);
	for(int i = 1; i < sz(invFact); i++) invFact[i] = mul(invFact[i-1], invInt[i], mod);
	vi C(M + 1, 0);
	for(int i = 0; i < sz(C); i++){
		int c = fact[M];
		c = mul(c, invFact[i], mod);
		c = mul(c, invFact[M - i], mod);
		C[i] = c;
	}
	return C;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	cin >> N >> M >> a >> Q;
	mod = getOrder(a, Q);
	vi C = getC();
	int tot = 0;
	vi X(N);
	for(int i = 0; i < N; i++){
		if(i < sz(C)) tot = add(tot, C[i], mod);
		X[i] = tot;
	}
	vi A(N);
	loop(i, N) A[i] = powmod(a, X[i], Q);
	reverse(all(A));
	loop(i, N) printf("%d%c", A[i], " \n"[i==N-1]);
	return 0;
}
