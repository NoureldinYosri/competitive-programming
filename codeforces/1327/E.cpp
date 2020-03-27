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
	if(!p) return a;
	int b = 1;
	for(; p > 1; p >>= 1){
		if(p & 1) b = mul(a, b);
		a = mul(a, a);
	}
	return mul(a, b);
}
int inv(int a){
	return powmod(a, mod-2);
}

int p10[1 << 20], n;

int solve(int len){
	if(len == n) return 10;
	if(len == n-1) return 10*9*2;
	
	assert(n-len >= 2);
	int ret = mul(810, p10[n-len-2]);
	ret = mul(ret, n - len - 1);
	
	int tmp = mul(180, p10[n-len-1]);
	ret = add(ret, tmp);
	return ret;
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif

	cin >> n;
	p10[0] = 1;
	for(int i = 1; i <= n;i++)
		p10[i] = mul(10, p10[i-1]);
	
	for(int i = 1; i <= n; i++){
		printf("%d%c", solve(i), " \n"[i==n]);
	}
	
	return 0;
}
