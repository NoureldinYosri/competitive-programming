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


int n,g;
int D[60];
double dp[60][61][1000 + 5*63 + 10];

double solve(int i,int m,int L) {
	if(L > g + 5*(m+1)) return -2;
	if(i == -1) {
		double res = (L >= g) ? (L - g)/(m+1.0) : -2;
//		cout << m << " " << L << " " << res << endl;
		return res;
	}
	double & ret = dp[i][m][L];
	if(ret == ret) return ret;
	ret = max(solve(i-1,m,L),solve(i-1,m+1,L+D[i]));
	return ret;
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	cin >> n >> g;
	loop(i,n) cin >> D[i];
	sort(D,D + n);
	reverse(D,D + n);
	int s = accumulate(D,D + n,0);
	if(s + 10 < g) {
		puts("impossible");
		return 0;
	}
	memset(dp,-1,sizeof dp);
	double ans = solve(n-1,0,10);
	if(ans < 0 || ans > 5) puts("impossible");
	else printf("%.10f\n",ans);
	return 0;
}
#endif
