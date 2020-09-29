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

const ll oo = 1LL << 60;
const int MAXN = 111;
ll A[MAXN][MAXN];
vector<ll> cand;
ll dp[MAXN][MAXN];
int n, m;
int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--){
		scanf("%d %d", &n, &m);
		loop(i, n) loop(j, m) scanf("%lld", &A[i][j]);
		cand.clear();
		loop(i, n) loop(j, m){
			ll v0 = A[i][j] - (i + j);
			if(v0 > A[0][0]) continue;
			if(v0 + n+m-2 > A[n-1][m-1]) continue;
			ll h = max((i+1 < n) ? A[i+1][j] : -oo, (j+1 < m) ? A[i][j+1] : -oo);
			if(i==n-1 && j==m-1) h = oo;
			if(A[i][j] + 1 > h) continue;
			cand.pb(v0);
		}
		sort(all(cand));
		cand.resize(unique(all(cand)) - cand.begin());
//		print(cand, ll);
		ll ans = LLONG_MAX;
		for(ll v0 : cand){
//			cerr << v0 << endl;
			loop(i, n) {
				loop(j, m){
					ll target = v0 + i + j;
					if(target > A[i][j]) {
						dp[i][j] = oo;
					} else {
						dp[i][j] = A[i][j] - target + ((i || j) ? min(i ? dp[i-1][j] : oo, j ? dp[i][j-1] : oo) : 0);
						dp[i][j] = min(dp[i][j], oo); 
					}
				}
//				prArr(dp[i], m, ll);
			}
			ans = min(ans, dp[n-1][m-1]);
		}
		
		printf("%lld\n", ans);
	}
	return 0;
}
