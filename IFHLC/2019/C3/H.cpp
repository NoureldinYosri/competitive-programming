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

const int MAXN = 210;
vi E[MAXN];
int fr[MAXN],to[MAXN],W[MAXN],n;

int cnt[MAXN];
ll sum[MAXN],depth[MAXN];

void dfs(int u,int p,ll dist) {
	cnt[u] = sum[u] = 0;
	depth[u] = dist;
	for(int e : E[u]){
		int v = fr[e] + to[e] - u;
		if(v == p) continue;
		dfs(v,u,dist + W[e]);
		cnt[u] += cnt[v];
		sum[u] += sum[v];
	}
	if(!cnt[u]) {
		cnt[u] = 1;
		sum[u] = dist;
	}
}


ll dp[MAXN];

ll solve(int u,int ie) {
//	ll & ret = dp[u];
//	if(ret != -1) return ret;
//	ret = 1LL << 60;
//	ll tot = sum[u] - cnt[u]*depth[u] + W[ie];
	ll ret = 0;
	// eagle eye but get back
	// go down then comeback
	// go down but don't comeback

	ll offset = 0;
	for(int e : E[u]) {
		if(e == ie) continue;
		int v = fr[e] + to[e] - u;
		ll eagleEye = sum[v] - cnt[v]*depth[u];
		ll goDown = solve(v,e);
		if(eagleEye <= goDown) {
			ret += eagleEye;
			continue;
		}
//		if(u == 2) cerr << goDown + depth[u] << " vs " << eagleEye << endl;
		ll tmp = min(goDown + depth[u],eagleEye);
		ret += tmp;
		ll diff = tmp - goDown;
		offset = max(offset,diff);
	}
//	cout << u << ": " << ret << " " << offset << " " << depth[u] << endl;
	ret -= offset;
	ret += W[ie];
//	cout << u << ": " << ret << " " << W[ie] << endl;
	return ret;
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	tc(){
		scanf("%d",&n);
		for(int u = 0;u <= n;u++) E[u].clear();
		loop(e,n-1) {
			scanf("%d %d %d",fr + e,to + e,W + e);
			E[fr[e]].push_back(e);
			E[to[e]].push_back(e);
		}
		W[n] = 0;
		dfs(1,0,0);
		memset(dp,-1,sizeof dp);
		ll ans = solve(1,n);
		printf("%lld\n",ans);
	}
	return 0;
}
#endif
