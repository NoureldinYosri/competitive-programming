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

int K;
ll dp[151][2][1 << 10];
int visID[151][2][1 << 10];
int visNum;

ll solve(int n, bool is_first, int msk){
	if(n == 0) return (msk == 0) ? 0 : LLONG_MAX;
	if(n < 0) return LLONG_MAX;
	ll & ret = dp[n][is_first][msk];
	if(visID[n][is_first][msk] == visNum) return ret;
	visID[n][is_first][msk] = visNum;
	
	ret = LLONG_MAX;
	for(int d = 0; d < 10; d++){
		int m = n;
		int nmsk = 0;
		for(int k = 0; k <= K; k++){
			int v = d + ((msk >> k) & 1);
			if(is_first) v += k;
			m -= v%10;
			nmsk |= (v/10) << k;
		}
		ll tmp = solve(m, 0, nmsk);
		if(tmp != LLONG_MAX) tmp = tmp*10 + d;
		ret = min(ret, tmp);
	}
	return ret;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--){
		visNum++;
		int n; scanf("%d %d", &n, &K);
		ll ans = solve(n, 1, 0);
		if(ans == LLONG_MAX) ans = -1;
		printf("%lld\n", ans);
	}
	return 0;
}
