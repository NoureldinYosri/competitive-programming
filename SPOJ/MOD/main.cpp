#pragma GCC optimize ("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define popcnt(x) __builtin_popcountll(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
using namespace std;


const int MAX = 1000*1000;
int prime[MAX + 1];

vi getPrimes(int n) {
	static map<int,vi> memo;
	if(memo.find(n) != memo.end()) return memo[n];
	vi & primes = memo[n];
	for(int i = 2;i*i <= n;i++)
		if(n%i == 0){
			primes.push_back(i);
			while(n%i == 0) n /= i;
		}
	if(n > 1) primes.pb(n);
	return primes;
}

vi getDivs(int n) {
	static map<int,vi> memo;
	if(memo.find(n) != memo.end()) return memo[n];
	vi & divs = memo[n];
	for(int i = 1;i*i <= n;i++)
		if(n%i == 0){
			divs.push_back(i);
			if(i*i != n) divs.push_back(n/i);
		}
	return divs;
}

bool IsDivisible(int a,int m) {
	bool everyPrime = 1;
	for(int p : getDivs(m)) everyPrime &= a%p == 0;
	return everyPrime;
}

int solveZero(int a,int m) {
	if(!IsDivisible(a,m)) return -1;
	if(a==0) return -1; // 0^0 is undefined
	int i = 0,p = 1;
	while(p) {
		p = (p*1LL*a)%m;
		i++;
	}
	return i;
}

int solveCoPrime(int a,int m,int b) {
	return 0;
}

int solveCaseOfEveryPrime(int a,int m,int b) {
	int g = 0,at = a;
	for(int p : getPrimes(a)) {
		int e = 0;
		while(at%p == 0) {
			e++;
			at /= p;
		}
		g = __gcd(g,e);
	}
	for(int p : getPrimes(a)){
		loop(i,g) {
			assert(a%p == 0);
			a /= p;
		}
	}
	return a;
}

int solveQ(int a,int p,int q,int ep,int b) {
	if(a%p == 0) {
		int e = 0;
		while(a%p == 0) e++,a/=p;
		if(b == 0) {
			if(e >= ep) return q;
			int te = (e + ep - 1)/ep;
			return (e + ep - 1)/ep;
		}
	}
	if(b == 0) return -1;
}

int mul(int a,int b,int m) {
	return (a*1LL*b)%m;
}

int powmod(int a,int p,int m) {
	a %= m;
	if(p == 0) return 1%m;
	int b = 1;
	for(;p > 1;p >>= 1) {
		if(p & 1) b = mul(a,b,m);
		a = mul(a,a,m);
	}
	return mul(a,b,m);
}

int solve(int a,int m,int b) {
	if(b >= m || b < 0) return -1;
	if(m == 1) return (b == 0) ? 0 : -1;

	int ret = 0,phi = m;
	for(int p : getPrimes(m))
		phi = (phi/p) * (p - 1);

	for(int p : getPrimes(a)) {
		int e = 0,q = 1;
		while(a%q == 0) {
			q *= p;
			a++;
		}
		int x = solveQ(a,p,q,e,b%q);
		if(x == -1) return -1;
		int ad = a/q,cphi = (phi*p)/(p-1);
		int xt = mul(ad,powmod(ad,cphi-1,q),m);
		xt = mul(xt,x,m);
		ret += xt;
		if(ret >= m) return ret;
	}


	return ret;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	int x,z,k;
	while(scanf("%d %d %d",&x,&z,&k) == 3 && !(x==0 && z==0 && k==0)) {
		int y = solve(x,z,k);
		if(y == -1) puts("No Solution");
		else printf("%d\n",y);
	}
	return 0;
}
