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
int powmod(int a, int p){
	if(!p) return 1;
	int b = 1;
	for(; p > 1; p >>= 1){
		if(p & 1) b = mul(a, b);
		a = mul(a, a);
	}
	return mul(a, b);
}


int n, s;
int A[1 << 20], B[1 << 20];
int I[1 << 20];
int inv[1 << 20];
int f[1 << 20];


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	inv[1] = 1;
	for(int i = 2; i < (1 << 20); i++){
		inv[i] = add(mod, -mul(mod/i, inv[mod%i]));
		assert(mul(i, inv[i]) == 1);
	}
	scanf("%d", &n);
	loop(i, n) {
		scanf("%d", I + i);
		s += I[i];
	}
	A[0] = 1;
	A[1] = 1;
	B[1] = add(0, -1);
	for(int a = 1; a < s; a++){
		A[a+1] = add(mul(s, A[a]), -mul(a, A[a-1]));
		A[a+1] = mul(A[a+1], inv[s-a]);
		
		B[a+1] = add(mul(s, B[a]), -mul(a, B[a-1]));
		B[a+1] = add(B[a+1], -s);
		B[a+1] = mul(B[a+1], inv[s-a]);
	}
	
	for(int i = 0; i <= s; i++){
		int x = B[i];
		char sgn = '+';
		if(add(0, -x) < x) x = add(0, -x), sgn = '-';
		cerr << i << " " << A[i] << " * f[0]  " << sgn << " " << x << endl;
	}

	f[0] = add(0, -mul(B[s], powmod(A[s], mod-2)));
	for(int a = 1; a < s; a++)
		f[a] = add(mul(A[a], f[0]), B[a]);
	prArr(f, s + 1, int);
	
	int scaler = inv[n];
	int ans = 0;
	loop(i, n) ans = add(ans, mul(f[I[i]], scaler));
	cout << ans << endl;
	return 0;
}
