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

const int mod = 1e9 + 7, MAX = 1 << 20;
int add(int a, int b){
	a += b;
	if(a >= mod) a -= mod;
	if(a < 0) a += mod;
	return a;
}
int mul(int a, int b){
	return (a*(ll)b)%mod;
}

int fact[MAX], invInt[MAX], invFact[MAX];
int prime[MAX];
vi divs;

void init(){
	fact[0] = invFact[0] = 1;
	for(int i = 1; i < MAX; i++){
		if(i == 1) invInt[i] = 1;
		else invInt[i] = mod - mul(mod/i, invInt[mod%i]);
		
		fact[i] = mul(fact[i - 1], i);
		invFact[i] = mul(invFact[i - 1], invInt[i]);
	}
	
	for(int i = 2; i < MAX; i++)
		if(prime[i] == 0){
			prime[i] = i;
			for(ll j = i*(ll)i; j < MAX; j += i)
				prime[j] = i;
		}
		
}

int C(int n, int k){
	if(k > n) return 0;
	return mul(fact[n], mul(invFact[k], invFact[n - k]));
}



int numPrimes(int x){
	int ret = 0;
	while(x > 1) {
		int p = prime[x];
		while(x%p == 0) {
			x /= p;
			ret++;
		}
	}
	return ret;
}

int dp[MAX][22];

int f(int x, int s){
	if(s == 0) return x == 1;
	if(x == 1) return 0;
	int & ret = dp[x][s];
	if(ret != -1) return ret;
	ret = 0;
	for(int d : divs) {
		if(d > x) break;
		if(x%d == 0)
			ret = add(ret, f(x/d, s - 1));
	}
	return ret;
}

int powmod(int x, int p){
	if(p == 0) return 1;
	int y = 1;
	for(; p > 1; p >>= 1){
		if(p & 1) y = mul(x, y);
		x = mul(x, x);
	}
	return mul(x, y);
}

void genDivs(int x){
	divs.clear();
	divs.push_back(1);
	while(x > 1){
		int p = prime[x], e = 0;
		while(x%p == 0) {
			x /= p;
			e ++;
		}
		int s = sz(divs), st = 0;
		for(; e > 0; e--){
			loop(i, s) divs.push_back(divs[st + i] * p);
			st += s;
		}
	}
	sort(divs.rbegin(), divs.rend());
	divs.pop_back();
	reverse(all(divs));
}

void tc(){
	int x, y; scanf("%d %d", &x, &y);
	if(x == 1){
		printf("%d\n", powmod(2, y - 1));
		return;
	}
	genDivs(x);
	int ans = 0, m = numPrimes(x);
	for(int s = 1; s <= m && s <= y; s++){
		int tmp = mul(C(y, s), f(x, s));
		ans = add(ans, tmp);
	}
	ans = mul(ans, powmod(2, y - 1));
	printf("%d\n", ans);
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	init();
	memset(dp, -1, sizeof dp);
	int T; scanf("%d", &T);
	while(T--) tc();
	return 0;
}
