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

int f[MAXA];

void update(int x, int v){
	const vi & P = primes[x];
	int m = sz(P);
	for(int msk = 0;msk < (1 << m); msk++){
		int g = 1;
		for(int i = 0;i < m;i++)
			if(msk & (1 << i))
				g *= P[i];
		f[g] += v;
	}
}
int get(int x){
	const vi & P = primes[x];
	int m = sz(P);
	int ret = 0;
	for(int msk = 0;msk < (1 << m); msk++){
		int g = 1,sgn = 1;
		for(int i = 0;i < m;i++)
			if(msk & (1 << i))
				g *= P[i],sgn *= -1;
		ret += sgn * f[g];
	}	
	return ret;
}
 
int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	sieve();
	scanf("%d",&n);
	loop(i,n) {
		scanf("%d",A + i);
		cnt[A[i]] ++;
	}
	ll ans = -1;
	sort(A, A + n);
	n = unique(A, A + n) - A;
	pi mx(0,0),mx2(0,0);
	
	loop(k,n) {
		int x = A[k];
		if(cnt[x] > 1) ans = max(ans, x + 0LL);
	}
	vi V;
	vi best;
	for(int g = 1; g < MAXA; g++){
		V.clear();
		for(int i = MAXA-MAXA%g;i >= g ;i -= g) {
			if(i >= MAXA) continue;
			int x = i/g;
			if(cnt[i] && !taken[x]){
				V.pb(x);
				taken[canon[x]] = 1;
			}
		}
		for(int i = MAXA-MAXA%g;i >= g ;i -= g) {
			if(i >= MAXA) continue;
			taken[canon[i/g]] = 0;
		}
		if(sz(V) <= 1) continue;
		ll ret = 0;

		for(int v : V){
			int lst = 0;
			while(get(v) > 0){
				int u = best.back();
				lst = u;
				best.pop_back();
				update(u, -1);
			}
			if(lst) {
				best.pb(lst);
				update(lst, 1);
			}
			best.pb(v);
			update(v, 1);
			ret = max(ret, v*(ll)lst);
		}
		while(!best.empty()){
			update(best.back(), -1);
			best.pop_back();
		}

		ans = max(ans, g * ret);
	}
	cout << ans << endl;
	return 0;
}
