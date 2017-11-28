#pragma GCC optimize ("O3")
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

const int MAX = 1000;
vi primes;
vi cnt;
map<ll,ll> MP;
vi prime_fact;
void get_primes(){
	vi vis(MAX,0);
	for(int i = 2;i < MAX;i++)
		if(!vis[i]){
			primes.pb(i);
			cnt.pb(0);
			prime_fact.pb(0);
			for(ll j = i*1LL*i;j < MAX;j += i)
				vis[j] = 1;
		}
//	cerr << sz(primes) << endl;
}

bool mul(ll x,ll y,ll & res){
	if(x <= LLONG_MAX/y) {
		res = x*y;
		return 1;
	}
	return 0;
}

void factorize(int n,int s){
	static map<int,vi> memo;
	vi aux;
	if(memo.find(n) != memo.end()) aux = memo[n];
	else {
		aux = vi(sz(primes));
		int m = n;
		loop(i,sz(primes)) {
			int p = primes[i];
			while(m%p == 0) m/=p,aux[i]++;
		}
		memo[n] = aux;
	}
	loop(i,sz(primes)) prime_fact[i] += s*aux[i];
}

void factorize_fact(int n,int s){
	static map<int,vi> memo;
	vi aux;
	if(memo.find(n) != memo.end()) aux = memo[n];
	else {
		aux = vi(sz(primes),0);
		aux.swap(prime_fact);
		range(i,2,n) factorize(i,1);
		aux.swap(prime_fact);
		memo[n] = aux;
	}
	loop(i,sz(primes)) prime_fact[i] += s*aux[i];
}

bool save(int cur,ll prod){
	int sum = 0;
	loop(i,cur) sum += cnt[i];
	assert(primes.back()*1LL*primes.back() >= sum);
	loop(i,sz(primes)) prime_fact[i] = 0;
	factorize_fact(sum,1);
	loop(i,cur) factorize_fact(cnt[i],-1);
	ll k = 1;
	loop(i,sz(primes)){
		int p = primes[i];
		loop(j,prime_fact[i]) {
			if(!mul(k,p,k)) return 0;
		}
	}
	if(MP.find(k) != MP.end()) prod = min(prod,MP[k]);
	MP[k] = prod;
	return 1;
}


void gen(int cur,int lste,ll prod) {
	if(prod > 1) save(cur,prod);
	//if(!save(cur,prod)) return;
	if(cur == sz(primes)) return;
	assert(cur < sz(primes));
	for(int i = 1;i <= lste;i++){
		cnt[cur] = i;
		if(mul(prod,primes[cur],prod))
			gen(cur+1,i,prod);
	}
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	get_primes();
	gen(0,63,1);
	ll n;
	while(scanf("%lld",&n) == 1){
		assert(MP.find(n) != MP.end());
		printf("%lld %lld\n",n,MP[n]);
	}
	return 0;
}
