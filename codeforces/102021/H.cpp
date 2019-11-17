#ifdef ACTIVE
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
#define tc() int T; scanf("%d",&T); for(int t = 1;t <= T;t++)
using namespace std;

ll mul(ll a,ll b) {
	if(a < LLONG_MAX/b) return a*b;
	return LLONG_MAX;
}
ll add(ll a,ll b) {
	if(a <= LLONG_MAX - b) return a+b;
	return LLONG_MAX;
}

ll POW(ll s,int p ){
	if(p == 0) return 1;
	ll y = 1;
	for(;p > 1;p >>= 1) {
		if(p & 1) y = mul(s,y);
		s = mul(s,s);
	}
	return mul(s,y);
}

ll f(int s,int n) {
	ll ret = 0;
	for(;s;s--) ret += POW(s,n-1);
	return ret;
}

int getS(int n,ll K) {
	int e = round(pow(K,1/(n - 1.0)));
	ll tot = 0;
	for(int s = 1;s <= e;s++) {
		tot = add(tot,POW(s,n-1));
		if(tot == K) return s;
		if(tot > K) return -1;
	}
	return -1;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	ll m; cin >> m;
	for(int n = 3;n <= 55;n++){
		int s = getS(n,m);
		if(s != -1) {
			printf("%d %d\n",n,s);
			return 0;
		}
	}
	puts("impossible");
	return 0;
}
#endif
