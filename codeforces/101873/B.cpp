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

int mod = 1e9 + 7;
int add(int a, int b){
	a += b;
	if(a >= mod) a -= mod;
	return a;
}
int mul(int a, int b){
	return (a*(ll)b)%mod;
}
int powmod(int a, int p){
	if(!p) return 1;
	int b = 1;
	for(; p > 1; p >>= 1){
		if(p&1) b = mul(a, b);
		a = mul(a, a);
	}
	return mul(a, b);
}
int inv(int x){
	return powmod(x, mod - 2);
}

int f(int m, int c){
	int ret = 0;
	for(int k = 0; k < m; k++){
		vector<bool> vis(m, false);
		int pc = 1;
		for(int i = 0; i < m; i++) if(!vis[i]) {
			pc = mul(pc, c);
			for(int j = i; !vis[j]; j = (j + k)%m)
				vis[j] = true;
		}
		ret = add(ret, pc);
	}
//	cerr << pi(m, c) << ": " << ret << "/" << m << " = ";
	ret = mul(ret, inv(m));
//	cerr << ret << endl;
	return ret;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int n, m, c;
	cin >> n >> m >> c;
	cout << f(m, powmod(c, n*n)) << endl;
	return 0;
}
