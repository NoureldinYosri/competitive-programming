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


int n, K;
int l1, r1, l2, r2;

ll solve(){
	if(l1 > l2) {
		swap(l1, l2);
		swap(r1, r2);
	}
	int s = max(l1, l2), e = min(r1, r2);
	int I0 = max(e-s, 0);
	int d0 = max(l2-r1, 0);	
	int d1 = max(r1, r2) - min(l1, l2) - I0;

	ll I = I0*(ll)n;	
//	cerr << "\tintersection is " << I << endl;
//	cerr << "\td0 " << d0 << " d1 " << d1 << endl;
	if(I >= K) return 0;
	
	ll need = K - I;
		
	ll ans = LLONG_MAX;
	for(ll m = 1; m <= n; m++){
		ll tmp = m*d0;
		ll have = m*d1;
		if(have >= need) {
			tmp += need;
		} else {
			tmp += have;
			tmp += (need - have)*2;
		}
//		cerr << m << ": " << m*(ll)d0 << " " << min(need, have) << " " << max(need-have, 0LL)*2 << " " << tmp << endl;
		ans = min(ans, tmp);
	}
	return ans;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--){
		scanf("%d %d", &n, &K);
		scanf("%d %d", &l1, &r1);
		scanf("%d %d", &l2, &r2);
		printf("%lld\n", solve());
	}
	return 0;
}
