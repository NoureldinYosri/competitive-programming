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

const int MAXA = 100*1000 + 1;

int prime[MAXA];
vi primes[MAXA];
int prime_cnt[MAXA];
int canon[MAXA];

void sieve(){
	canon[1] = 1;
	for(int i = 2;i < MAXA;i++){
		if(!prime[i]){
			prime[i] = i;
			for(ll j = i*(ll)i;j < MAXA;j += i)
				prime[j] = i;
		}
		int p = prime[i];
		int n = i,e = 0;
		while(n%p == 0) n /= p, e++;
		prime_cnt[i] = prime_cnt[n] + 1;
		for(int q : primes[n])
			primes[i].pb(q);
		primes[i].pb(p);
		sort(all(primes[i]));
		canon[i] = canon[n] * p;
	}
//	cerr << "#p " << *max_element(prime_cnt, prime_cnt + MAXA) << endl;
}

int cnt[MAXA];
int A[1 << 20], n;

bool bad[MAXA];
bool taken[MAXA];

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d",&n);
	loop(i,n) {
		scanf("%d",A + i);
	}
	ll ans = -1;
	loop(i,n) loop(j, i){
		ll g = A[i]*(ll)(A[j]/__gcd(A[i], A[j]));
		ans = max(ans, g);
	}
	cout << ans << endl;
	return 0;
}
