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

int m;
ll n,k;
ll A[1 << 20];


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%lld %lld %d",&n,&m,&k);
	loop(i,m) scanf("%lld",A + i);
	ll e = 0;
	int j = 0,ans = 0;
	while(j < m) {
		ans ++;
		int ctr = 0;
		while(j < m && A[j]-e <= k) {
			ctr++;
			j++;
		}
		ll p = j ? A[j-1] : 0;
		ll len = p - e;
		e = p + k - len;
		if(j < m) {
			ll rem = A[j] - 1 - e;

		}
	}
	cout << ans << endl;
	return 0;
}
