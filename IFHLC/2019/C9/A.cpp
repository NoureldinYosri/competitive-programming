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

const ll oo = 1LL << 60;

ll dp[11][9*11][9*11][2];
ll p10[11];
bool vis[11][9*11][9*11][2];

ll solve(int d,int s1,int s2,bool f) {
	if(d == 0) return (s1 == s2) ? 0 : -oo;
	ll & ret = dp[d][s1][s2][f];
	if(vis[d][s1][s2][f]) return ret;
	ret = -oo;
	vis[d][s1][s2][f] = 1;
	for(int a = f;a <= 9;a++)
		for(int b = f;b <= 9;b++)
			ret = max(ret,solve(d-1,s1+a,s2+b,0) + (a-b)*p10[d-1]);
	return ret;
}

ll solve(int D) {
	memset(vis,0,sizeof vis);
	p10[0] = 1;
	loop(i,10) p10[i + 1] = p10[i] * 10;
	return solve(D,0,0,1);
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int D; cin >> D;
	cout << solve(D) << endl;
	return 0;
}
#endif
