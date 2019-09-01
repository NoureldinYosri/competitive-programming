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


ll raise(ll x,int p) {
	if(!p) return 1;
	ll y = 1;
	for(;p > 1;p >>= 1) {
		if(p&1) y *= x;
		x *= x;
	}
	return x*y;
}

const int B = 31,MAX = 100*1000 + 10;
const int mod = 1000000000;
int A[MAX],n,m;
int P[MAX];
ll pref[B][MAX];


ll solve(){
	sort(A,A + n);
	for(int b = 1;b < B;b++) {
		ll s = 0;
		for(int i = 0;i < n;i++) {
			s += A[i]/b;
			pref[b][i] = s;
		}
	}
	ll ans = 0;
	loop(i,m) {
		ll z = 0;
		ll q = 1;
		int j = 0;
		for(int k = 1;j < n;k++){
			q *= P[i];
			int nj = upper_bound(A + j,A + n,q) - A;
			ll s = nj ? pref[k][nj-1] : 0;
			s -= j ? pref[k][j-1] : 0;
			z += s%mod;
			j = nj;
		}
		ans += (i+1)*z;
		ans %= mod;
	}
	return ans;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	tc(){
		scanf("%d %d",&n,&m);
		loop(i,n) scanf("%d",A + i);
		loop(i,m) scanf("%d",P + i);
		printf("%lld\n",solve());
	}
	return 0;
}
#endif
