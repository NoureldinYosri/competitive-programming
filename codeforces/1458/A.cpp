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

int n, m;
ll A[1 << 20], B[1 << 20];

ll GCD(ll x, ll y){
	while(y) {
		ll t = x%y;
		x = y;
		y = t;
	}
	return x;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d", &n, &m);
	loop(i, n) scanf("%lld", A + i);
	loop(i, m) scanf("%lld", B + i);
	ll g = 0;
	loop(i, n - 1) g = GCD(g, abs(A[i + 1] - A[i]));
	loop(i, m) printf("%lld ", GCD(g, A[0] + B[i]));
	puts(""); 
	return 0;
}
