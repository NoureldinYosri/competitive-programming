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

const int mod = 998244353;
int add(int a, int b){
	a += b;
	if(a >= mod) a -= mod;
	if(a < 0) a += mod;
	return a;
}
int mul(int a, int b){
	return (a*(ll)b)%mod;
}

const int MAXN = 200*1000 + 10;
int D[MAXN], n, m;
ll suff[MAXN];
int fact[MAXN], invFact[MAXN], invInt[MAXN];


void init(){
	invInt[1] = 1;
	for(int i = 2; i < MAXN; i++) invInt[i] = mod - mul(mod/i, invInt[mod%i]);
	invFact[0] = fact[0] = 1;
	for(int i = 1; i < MAXN; i++){
		fact[i] = mul(fact[i-1], i);
		invFact[i] = mul(invFact[i-1], invInt[i]);
	}
}

int C(int n, int k){
	if(k > n) return 0;
	return mul(fact[n], mul(invFact[k], invFact[n - k]));
}

int powmod(int a, int p){
	if(p == 0) return 1;
	int b = 1;
	for(; p > 1; p >>= 1){
		if(p & 1) b = mul(a, b);
		a = mul(a, a);
	}
	return mul(a, b);
}
int inv(int x){
	return powmod(x, mod - 2);
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	init();
	scanf("%d %d", &n, &m);
	loop(i, n) scanf("%d", D + i);
	sort(D, D + n);
	suff[n] = 0;
	for(int i = n-1; i >= 0; i--) suff[i] = suff[i + 1] + D[i];
	
	while(m--){
		int a, b; scanf("%d %d", &a, &b);
		int i = lower_bound(D, D + n, b) - D;
		int R = n - i;
		int ans = 0;
		if(R >= a){
			int q = mul(R + 1 - a, invInt[R + 1]);
			ans = mul((suff[0] - suff[i])%mod, q);
			int p = mul(C(R - 1, a), inv(C(R, a)));
			ans = add(ans, mul(suff[i]%mod, p));
		}
		printf("%d\n", ans);
	}
	
	return 0;
}
