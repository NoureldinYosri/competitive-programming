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



int M, D, W;

ll bf(){
	if(min(M, D) > 1e5) return -1;
	int ret = 0;
	loop(y, min(M, D)) loop(x, y){
		int a = (x + y*D)%W;
		int b = (y + x*D)%W;
		ret += a == b;
	}
	return ret;
}

ll S(ll n){
	return (n*(n+1)) >> 1;
}

ll solve(){
	if(D == 1) return 0;
	ll ret = 0;
	// x + y*D = y + x*D mod W
	// (y-x)*D = y-x mod W
	// (y-x)(D-1) = 0 mod W
	// W | (y-x)(D-1)
	
	ll g = __gcd(D-1, W);
	ll d = W/g;
	
	//d | (y-x) and y, x < min(M, D)
	
	ll L = min(M, D);
	
	//d | (y-x), x < y < L
	// y-x = v -> L - v
	
//	for(ll x = d; x < L; x += d){
//		ret += L - x;
//	}
	ret = L*(L/d) - d*S(L/d);
 	
	
	
	return ret;
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--){
		scanf("%d %d %d", &M, &D, &W);
		printf("%lld\n", solve());
	}
	return 0;
}
