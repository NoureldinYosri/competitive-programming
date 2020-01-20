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


int add(int a, int b, int mod){
	a += b;
	if(a >= mod) a -= mod;
	if(a < 0) a += mod;
	return a;
}
int mul(int a, int b, int mod){
	return (a*(ll)b)%mod;
}
int powmod(int a, int p, int mod){
	if(p == 0) return 1;
	int b = 1;
	for(;p > 1; p >>= 1){
		if(p & 1) b = mul(a, b, mod);
		a = mul(a, a, mod);
	}
	return mul(a, b, mod);
}
int inv(int a, int mod){
	return powmod(a, mod - 2, mod);
}

const int mod = 998244353;
const int inv100 = inv(100, mod);

int n;
int P[1 << 20];

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d",&n);
	loop(i, n) scanf("%d",&P[i]);
	reverse(P, P + n);
	int a = 0, b = 0;
	loop(i, n){
		int p = mul(P[i], inv100, mod);
		a = mul(a, p, mod);
		b = mul(b, p, mod);
		int rp = add(1, -p, mod);
		a = add(a, rp, mod);
		b = add(b, 1, mod);
	}
	int e = mul(b, inv(add(1, -a, mod), mod), mod);
	cout << e << endl;
	return 0;
}
