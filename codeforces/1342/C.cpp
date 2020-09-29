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


int A, B, L;
vi good;

ll get(ll n, int r, int m){
	ll ret = n/m + (r > 0) * (r <= n%m);
	return ret;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--){
		int m; scanf("%d %d %d", &A, &B, &m);
		L = A*(B/__gcd(A, B));
		good.clear();
		loop(i, L) {
			int x = (i%A)%B;
			int y = (i%B)%A;
			if(x == y) good.pb(i);
		}
		while(m--){
			ll s, e; scanf("%lld %lld", &s, &e);
			ll ans = 0;
			for(int r : good) ans += get(e, r, L) - get(s-1, r, L);
			ans = e-s+1 - ans;
			printf("%lld ", ans);
		}
		puts("");
	}
	return 0;
}
