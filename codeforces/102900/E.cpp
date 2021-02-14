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


const int mod = 998244353, MAX = 1e7 + 10 ;
int add(int a, int b){
	a += b;
	if(a >= mod) a -= mod;
	if(a < 0) a += mod;
	return a;
}
int mul(int a, int b){
	return (a*(ll)b)%mod;
}

int f[MAX], g[MAX], n, k;
int invInt[MAX];

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d", &n, &k);
	g[0] = f[0] = 1;
	for(int i = 1; i <= k; i++)
		g[i] = f[i] = mul(i, f[i - 1]);
	invInt[1] = 1;
	for(int i = 2; i < MAX;i ++)
		invInt[i] = mod - mul(mod/i, invInt[mod%i]);
		
	for(int i = k + 1; i <= n; i++){
		g[i] = mul(i, g[i - 1]);
		g[i] = mul(g[i], invInt[i - k]); 
	}
	for(int i = k + 1; i <= n; i++){
		f[i] = mul(i, f[i - 1]);
		f[i] = add(f[i], -mul(g[i - 1], f[i-k-1]));
	}
//	prArr(f, n + 1, int);
	cout << f[n] << endl;
	return 0;
}
