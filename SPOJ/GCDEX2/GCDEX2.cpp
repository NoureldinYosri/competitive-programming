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


const int MAX = 1 << 20;
using bigint = unsigned long long;

int prime[MAX];
int f[MAX];
bigint phi[MAX];

void sieve(){
	phi[1] = 1;
	for(int i = 2;i < MAX;i++){
		if(prime[i] == 0){
			prime[i] = i;
			for(ll j = i*(ll)i;j < MAX;j += i)
				prime[j] = i;
		}
		int p = prime[i],x = i,q = 1;
		while(x%p == 0){
			x /= p;
			q *= p;
		}
		phi[i] = phi[x] * (q - q/p);
	}
}

int solvef(int n){
	if(n == 1) return f[1] = 1;
	if(f[n]) return f[n];
	int p = prime[n],e = 0;
	int m = n,q = 1;
	while(m%p == 0){
		m /= p;
		q *= p;
		e++;
	}
	int g = (e+1)*q - e*(q/p);
	return f[n] = solvef(m) * g;
}


struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};



inline bigint C(bigint n){
	if(n&1) return n*((n+1) >> 1);
	return (n>>1)*(n+1);
}


unordered_map<long long, bigint, custom_hash> mem;

bigint sumPhi(bigint n){
	if(n <= 1) return n;
	if(mem.count(n)) return mem[n];

	bigint ret = C(n);
	
	for(bigint m = 2;m*m <= n;m++)
		ret -= sumPhi(n/m);
	for(bigint d = 1;d*d <= n;d++){
		if(d == n/d)break;
		bigint tmp = ((n/d) - n/(d+1))*sumPhi(d);
		ret -= tmp;
	}
	mem[n] = ret;
	return ret;
}



void init(){
	mem.max_load_factor(0.25);
	mem.reserve(1<<20);
}



unordered_map<long long, bigint, custom_hash> dp;


bigint psi(ll N){
	if(dp.count(N)) return dp[N];
	bigint ans = 0;
	
	
	ll u = sqrt(N) + 2;
	while(u*u > N) u--;
	
	for(ll a = 1;a <= u;a++){
		bigint tmp = a * sumPhi(N/a);
		ans += tmp;
	}
	
	for(ll b = 1;b <= u;b++){
		ll a = N/b;
		bigint tmp = C(a)*phi[b];
		ans += tmp;
	}
	

	ans -= C(u) * sumPhi(u);
	ans -= C(N);
	
	dp[N] = ans;
	return ans;	
}


int main(){
	init();
	sieve();
	int T; scanf("%d",&T);
	while(T--){
		ll N; scanf("%lld",&N);
		printf("%llu\n",psi(N));
	}
	
	return 0;
}


