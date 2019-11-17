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

const int MAX = 300;
int A[MAX][MAX];
int m,n;
ll aux[MAX][MAX],dp[MAX][MAX];


ll solve(){
	loop(i,n) loop(j,n) aux[i][j] = dp[i][j] = 0;

	ll ans = LLONG_MIN;
	for(int r = m-1;r >= 0;r--) {
		for(int s = 0;s < n;s++){
			ll seg_sum = 0;
			for(int e = s;e < n;e++) {
				seg_sum += A[r][e];
				ll tmp = max(0LL,aux[e][s]);
				dp[s][e] = seg_sum + tmp;
				ans = max(ans,dp[s][e]);
			}
		}
		for(int s = 0;s < n;s++)
			for(int e = 0;e < n;e++){
				aux[s][e] = dp[s][e];
				dp[s][e] = 0;
			}
		for(int s = 0;s < n;s++)
			for(int e = n-1;e >= 0;e--) {
				if(e+1 < n) aux[s][e] = max(aux[s][e],aux[s][e+1]);
				if(s) aux[s][e] = max(aux[s][e],aux[s-1][e]);
			}
	}
	return ans;
}

int main(){
	freopen("livada2.in", "r", stdin);
	freopen("livada2.out","w",stdout);

	tc(){
		scanf("%d %d",&m,&n);
		loop(i,m) loop(j,n) scanf("%d",&A[i][j]);
		printf("%lld\n",solve());
	}
	return 0;
}
#endif
