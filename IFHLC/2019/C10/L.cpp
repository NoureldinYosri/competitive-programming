#ifdef ACTIVE
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
#define tc() int T; scanf("%d",&T); for(int t = 1;t <= T;t++)
using namespace std;

const int MAX = 10*1000,mod = 1e9 + 9;
vi primes;
int isPrime[MAX];

int mul(int a,int b) {
	return (a*(ll)b)%mod;
}
int EXP(int a,int p){
	if(!p) return 1;
	int b = 1;
	for(;p > 1;p >>= 1) {
		if(p&1) b = mul(a,b);
		a = mul(a,a);
	}
	return mul(a,b);
}
int inv(int a) {
	return EXP(a,mod-2);
}

unordered_map<int,pi> prod,quot;

void sieve(){
	loop(i,MAX) isPrime[i] = 1;
	for(int i = 2;i < MAX;i++) {
		if(isPrime[i]) {
			primes.push_back(i);
			for(int j = i*i;j < MAX;j += i)
				isPrime[j] = 0;
		}
	}
	for(int q : primes)
		for(int p : primes) {
			if(p == q) break;
			int a = mul(p,q);
			int b = mul(q,inv(p));
			assert(!prod.count(a));
			prod[a] = pi(p,q);
			assert(!quot.count(b));
			quot[b] = pi(p,q);
		}
}

int ask(int l,int r) {
	cout << "? " << l << " " << r << endl;
	fflush(stdout);
	int res; cin >> res;
	if(res==-1) exit(0);
	return res;
}

void answer(vi ans) {
	cout << "!";
	for(int x : ans) cout << " " << x;
	cout << endl;
	fflush(stdout);
}

void solve2(){
	int a = ask(1,2);
	assert(prod.count(a));
	pi res = prod[a];
	vi ans{res.first,res.second};
	answer(ans);
}
void solve3(){
	int a = ask(1,2);
	int b = ask(1,3);
	int x3 = mul(b,inv(a));
	assert(prod.count(a));
	pi res = prod[a];
	vi ans{res.first,res.second,x3};
	answer(ans);
}
void solve4(){
	int a = ask(1,3);
	int b = ask(2,4);
	int x4_x1 = mul(b,inv(a));
	assert(quot.count(x4_x1));
	pi res = quot[x4_x1];
	int x1 = res.first,x4 = res.second;
	int x23 = mul(a,inv(x1));
	assert(prod.count(x23));
	res = prod[x23];
	int x2 = res.first,x3 = res.second;
	vi ans{x1,x2,x3,x4};
	answer(ans);
}

int main(){
	sieve();
	int n; cin >> n;
	if(n == 2) solve2();
	else if(n == 3) solve3();
	else if(n == 4) solve4();
	else {
		int k = (n + 1)/2;
		vi ans(n,0),Q(n,0);
		for(int i = 0;i <= n-k;i++)
			Q[i] = ask(i+1,i+k);
		for(int i = 0;i < n-k;i++) {
			int xk_x1 = mul(Q[i+1],inv(Q[i]));
			assert(quot.count(xk_x1));
			pi res = quot[xk_x1];
			ans[i] = res.first;
			ans[i + k] = res.second;
		}
		int aux = 1;
		for(int i = 0;i+1 < k;i++)
			aux = mul(aux,ans[i]);
		ans[k-1] = mul(Q[0],inv(aux));
		answer(ans);
	}
	return 0;
}
#endif
