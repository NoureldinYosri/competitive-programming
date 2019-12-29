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

int add(int a,int b){
	a += b;
	if(a >= mod) a -= mod;
	if(a < 0) a += mod;
	return a;
}
int mul(int a,int b){
	return (a*(ll)b)%mod;
}

int powmod(int a,int p){
	if(!p) return 1;
	int b = 1;
	for(;p > 1;p >>= 1) {
		if(p&1) b = mul(a,b);
		a = mul(a,a);
	}
	return mul(a,b);
}
vi operator + (const vi & A,const vi & B){
	int n = max(sz(A),sz(B));
	vi C(n,0);
	loop(i,n){
		if(i < sz(A)) C[i] = add(C[i],A[i]);
		if(i < sz(B)) C[i] = add(C[i],B[i]);
	}
	return C;
}

vi operator - (const vi & A,const vi & B){
	int n = max(sz(A),sz(B));
	vi C(n,0);
	loop(i,n){
		if(i < sz(A)) C[i] = add(C[i],A[i]);
		if(i < sz(B)) C[i] = add(C[i],-B[i]);
	}
	return C;
}
vi operator * (const int & c,const vi & A){
	vi C;
	for(int a : A) C.push_back(mul(c,a));
	return C;
}

vi operator << (const vi & A,const int & k){
	if(A.empty()) return vi();
	int n = sz(A);
	vi C(n+k,0);
	copy(all(A),C.begin() + k);
	return C;
}

vi operator -- (const vi & A){
	vi C;
	for(int i = 1;i < sz(A);i++)
		C.push_back(mul(i,A[i]));
	return C;
}


int operator % (const vi & f,const int & x){
	int ret = 0;
	for(int i = sz(f)-1;i >= 0;i--){
		ret = mul(ret,x);
		ret = add(ret,f[i]);
	}
	return ret;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int n,m,K; cin >> n >> m >> K;
	int r = powmod(m,mod-2);
//	cout << r << endl;
	vi f{1};
	for(int k = 1;k <= K;k++){
		vi df = --f;
		f = (df << 1) - (df << 2) + n*(f << 1);
//		print(f,int);
	}
	cout << f%r << endl;
	return 0;
}
