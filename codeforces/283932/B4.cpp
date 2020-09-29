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

const double eps = 1e-9;
const int MAXN = 100*1000 + 10;
int n, m;
vp E[MAXN];
int nxt[MAXN];
double dp[MAXN];



double solve(double avg){
	for(int u = n-1; u; u--){
		dp[u] = -1e6;
		for(auto [v, w] : E[u]){
			double tmp = dp[v] + avg - w;
			if(tmp > dp[u]){
				dp[u] = tmp;
				nxt[u] = v;
			}
		}
	}
	return dp[1];
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d", &n, &m);
	loop(t, m){
		int a, b, c; scanf("%d %d %d", &a, &b, &c);
		E[a].emplace_back(b, c);
	}
	double s = 0, e = 100;
	for(int t = 0; e-s > eps && t < 100; t++){
		double m = (s + e)/2.0;
		if(solve(m) >= 0) e = m;
		else s = m;
	}
	cerr << solve(s) << endl;
	vi path;
	for(int u = 1; u != n; u = nxt[u]) path.pb(u);
	path.pb(n);
	printf("%d\n", sz(path) - 1);
	for(int u : path) printf("%d ", u);
	puts("");
	return 0;
}
