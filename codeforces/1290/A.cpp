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

const int MAXN = 3500  + 10;
int dp[MAXN][MAXN];
int n, m, K;
int A[MAXN];

int solve(int s, int e){
	if(s+n-e-1 == m-1) return max(A[s], A[e]);
	int & ret = dp[s][e];
	if(ret != -1) return ret;
	return ret = min(solve(s+1, e), solve(s, e-1));
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d",&T);
	while(T--){
		scanf("%d %d %d",&n, &m, &K);
		K = min(K, m-1);
		loop(i, n) scanf("%d",A + i);
		fill(dp[0], dp[n], -1);
		int ans = 0;
		loop(r, K+1) {
//			cout << r << " " << n-1-(K-r) << ". " << solve(r, n-1-(K-r)) << endl;
			ans = max(ans, solve(r, n-1-(K-r)));
		}
		printf("%d\n", ans);
	}
	return 0;
}
