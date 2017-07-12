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
#define popcnt(x) __builtin_popcount(x)
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
int prime[MAX];
vi P;
void sieve(){
	for(int p = 2;p < MAX;p++)
		if(!prime[p]){
			P.pb(p);
			prime[p] = p;
			for(ll x = p*1LL*p;x < MAX;x += p)
				prime[x] = p;
		}
}

int seg0(int n){
	int ret = 1;
	for(;n > 1;){
		int p = prime[n],ctr = 1;
		while(n%p == 0){
			ctr++;
			n /= p;
		}
		ret *= ctr;
	}
	return ret;
}


ll mul(ll x,ll y,ll mod){
	if(x <= INT_MAX && y <= INT_MAX) return (x*y)%mod;
	if(!x) return 0;
	if(x > y) swap(x,y);
	ll t = 0;
	for(;x > 1;x >>= 1){
		if(x & 1) {
			t += y;
			if(t >= mod) t -= mod;
		}
		y <<= 1;
		if(y >= mod) y -= mod;
	}
	y += t;
	if(y >= mod) y -= mod;
	return y;
}

ll pow_mod(ll x,ll power,ll mod){
	if(!power) return 1%mod;
	ll y = 1;
	for(;power > 1;power >>= 1){
		if(power & 1) y = mul(x,y,mod);
		x = mul(x,x,mod);
	}
	return mul(x,y,mod);
}

bool is_prime(ll n){
	if(n <= 1) return 0;
	if(n <= 3) return 1;
	if(n%2 == 0 || n%3 == 0) return 0;
	for(int i = 0;i < 1000;i++){
		ll v = rand()%(n - 1) + 1;
		if(__gcd(v,n) != 1) return 0;
		if(pow_mod(v,n - 1,n) != 1) return 0;
	}
	return 1;
}

int solve(ll n){
	if(n < MAX) return seg0(n);
	int ret = 1;
	for(auto p : P){
		if(n%p == 0){
			int ctr = 1;
			while(n%p == 0){
				n /= p;
				ctr++;
			}
			ret *= ctr;
			if(n < MAX) {
				ret *= seg0(n);
				n = 1;
			}
		}
	}
	if( n == 1) return ret;
	if(is_prime(n)) ret *= 2;
	else {
		ll u = sqrt(n) + 10;
		while(u*u > n) u--;
		if(u*u == n && is_prime(u)) ret *= 3;
		else ret *= 4;
	}
	return ret;
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("input.in", "r", stdin);
		freopen("output.out", "w", stdout);
	#endif
	sieve();
	ll n; cin >> n;
	cout << solve(n) << endl;
	return 0;
}
