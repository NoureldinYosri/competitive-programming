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
const int MAXN = 200*1000 + 10;
int n, A[MAXN], K;

int add(int a, int b){
	a += b;
	if(a >= mod) a -= mod;
	if(a < 0) a += mod;
	return a;
}
int mul(int a, int b){
	return (a*(ll)b)%mod;
}

int fact[MAXN];
int invFact[MAXN], invInt[MAXN];

void init(){
	fact[0] = 1;
	for(int i = 1; i < MAXN; i++) fact[i] = mul(fact[i-1], i);
	invInt[1] = 1;
	for(int i = 2; i < MAXN; i++) invInt[i] = mod - mul(mod/i, invInt[mod%i]);
	invFact[0] = 1;
	for(int i = 1; i < MAXN; i++) invFact[i] = mul(invFact[i-1], invInt[i]);
}

int C(int n, int k){
	if(k > n) return 0;
	int ret = fact[n];
	ret = mul(ret, invFact[k]);
	ret = mul(ret, invFact[n - k]);
	return ret;
}

map<int, vi> powers;
const int i2 = 499122177;

int f(int s){
	if(s == 0) return 0;
	if(s & 1){
		return powers[2][s-1];
	} else {
		return mul(i2, add(powers[2][s], -C(s, s >> 1)));
	}
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	init();
	scanf("%d %d", &n, &K);
	loop(i, n) scanf("%d", A + i);
	if(K == 1){
		puts("0");
		return 0;
	}
	
	int m = 0;
	int scaler = 1;
	loop(i, n){
		if(A[i] == A[(i+1)%n]) scaler = mul(scaler, K);
		else m++;
	}
	
	
	for(int x : {2, K-2}){
		vi P(n+1, 1);
		for(int i = 1; i <= n; i++)
			P[i] = mul(P[i-1], x);
		powers[x] = P;
	}

	int ans = 0;
	for(int s = 0; s <= m; s++){
		int tmp = f(s);
		tmp = mul(tmp, C(m, s));
		tmp = mul(tmp, powers[K-2][m-s]);
		ans = add(ans, tmp);
	}

	ans = mul(ans, scaler);
	cout << ans << endl;
	return 0;
}
