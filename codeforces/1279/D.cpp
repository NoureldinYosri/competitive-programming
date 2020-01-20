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


const int mod = 998244353 ;
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
	if(p == 0) return 1;
	int b = 1;
	for(;p > 1; p >>= 1){
		if(p & 1) b = mul(a, b);
		a = mul(a, a);
	}
	return mul(a, b);
}
int inv(int a){
	return powmod(a, mod - 2);
}


vi kid_presents[1 << 20];
int present_child_cnt[1 << 20];

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int n;
	scanf("%d",&n);
	loop(i,n){
		int m; scanf("%d",&m);
		loop(j,m) {
			int x; scanf("%d",&x);
			kid_presents[i].push_back(x);
			present_child_cnt[x] ++;
		}
	}
	
	int in = inv(n);
	int ans = 0;
	loop(i,n) {
		int im = inv(kid_presents[i].size());
		int p = mul(in, im);
		for(int j : kid_presents[i]){
			int q = mul(p, mul(present_child_cnt[j], in));
			ans = add(ans, q);
		}
	}
	cout << ans << endl;
	return 0;
}
