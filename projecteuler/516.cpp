#ifdef ACTIVE
#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
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
using namespace std;

const int MAXA = 1000*1000;
const ll target = 1000000000000LL;
typedef tuple<int,int,int> state;
int prime[MAXA + 1];
vi primes;

void sieve(){
	for(int i = 2;i <= MAXA;i++)
		if(!prime[i]) {
			primes.pb(i);
			prime[i] = i;
			for(ll j = i*(ll)i;j <= MAXA;j += i)
				prime[j] = i;
		}
}

int phi(ll x) {
	assert(x <= MAXA);
	int r = x;
	while(x > 1) {
		int p = prime[x];
		r -= r/p;
		while(x%p == 0) x /= p;
	}
	return r;
}

bool is_hamming(int x) {
	assert(x <= MAXA);
	while(x > 1) {
		int p = prime[x];
		if(p > 5) return 0;
		while(x%p == 0) x /= p;
	}
	return 1;
}


uint bruteforce_S(uint n,bool verbose = 0) {
	static map<int,vector<uint> > table;
	uint res = 0;
	int ctr = 0;
	for(uint i = 1;i <= n;i++){
		int _phi = phi(i);
		if(is_hamming(_phi)){
			res += i;
			table[_phi].pb(i);
			ctr++;
		}
	}
	cerr << "##" << ctr << endl;
	return res;
}


bool is_prime(ll x) {
	static unordered_map<ll,bool> mem;
	if(x <= 0) return 0;
	if(x <= MAXA) return prime[x] == x;
	if(mem.count(x)) return mem[x];
	bool res = 1;
	for(int p : primes) {
		if(p*(ll)p > x) break;
		if(x%p == 0){
			res = 0;
			break;
		}
	}
	return mem[x] = res;
}


uint uval(ll x) {
	return x%(1LL << 32);
}

vector<ll> vals;

uint get(ll n,ll x,ll N) {
//	vals.pb(x);
	uint ret = 1;
	for(ll p2 = 1;p2 < n && x*(p2 + 1) <= N;p2 *= 2)
		for(ll p3 = 1;p2*p3 < n && x*(p2*p3 + 1) <= N;p3 *= 3)
			for(ll p5 = 1;p2*p3*p5 < n && x*(p2*p3*p5 + 1) <= N;p5 *= 5){
				ll v = p2*p3*p5 + 1;
				if(v > 5 && is_prime(v))
					ret += uval(v) * get(v-1,x*v,N);
			}
	return ret;
}

uint solve(ll n) {
	uint res = 0;
	for(ll p2 = 1;p2 <= n;p2 <<= 1)
		for(ll p3 = 1;p2*p3 <= n;p3 *= 3)
			for(ll p5 = 1;p2*p3*p5 <= n;p5 *= 5){
				ll u = p2*p3*p5;
				res += uval(u) * get(n,u,n);
//				get(n,u,n);
			}
//	sort(all(vals));
//	print(vals,ll);
//	cerr << "#" << sz(vals) << endl;
//	for(ll x : vals)
//		res += uval(x);
	return res;
}

int main(int argc,char **argv){
	sieve();
	ll n = target;
//	cout << bruteforce_S(n,1) << endl;
	cout << "answer = " << solve(n) << endl;;
	return 0;
}
#endif
