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

ll e_euclid(ll a, ll b, ll & x, ll & y){
	if(b == 0){
		x = 1;
		y = 0;
		return a;
	}
	ll g = e_euclid(b, a%b, y, x);
	
	//b*y + (a%b)*x = g
	//b*y + (a - (a/b)*b)*x = g
	//b*y + a*x - (a/b)*b*x = g
	//a*x + b*(y - (a/b)*x) = g
	y -= (a/b)*x;
	assert(x*(__int128)a + y*(__int128)b == g);
	return g;
}

bool CRT(ll & a, ll & m, ll b, ll n){
	ll g = __gcd(m, n);
	if(abs(a - b)%g) return 0;
	if(a < b) swap(a, b), swap(m, n);
	__int128 L = abs(a - b)/g;
	ll u, v;
	e_euclid(m, n, u, v);
	__int128 x = a - m*(u*L);
	ll M = m * (n/g);
	x = (x%M + M)%M;
	assert(x%m == a);
	assert(x%n == b);
	a = x;
	m = M;
	return 1;
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--){
		ll a, n, b, m;
		cin >> a >> n >> b >> m;
		if(CRT(a, n, b, m)) printf("%lld %lld\n", a, n);
		else puts("no solution");
	}
	return 0;
}
