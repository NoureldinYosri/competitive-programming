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


const int MAX = 1 << 20;
int n;
int fr[MAX],to[MAX],W[MAX];
int cnt[MAX];
vi E[MAX];
ll dp[MAX][2];
int K,visNum;
int visID[MAX][2];
vector<pair<ll,ll>> tmp[MAX][2];

ll solve(int u,int p,int c) {
	ll & ret = dp[u][c];
	if(visID[u][c] == visNum) return ret;
	visID[u][c] = visNum;
	ret = 0;

	auto & V = tmp[u][c];
	V.clear();
	for(auto e : E[u]) {
		int v = fr[e] + to[e] - u;
		if(v == p) continue;
		ll g1 = solve(v,u,1) + W[e],g2 = solve(v,u,0);
		V.emplace_back(g1 - g2,g2);
	}
	sort(all(V));
	reverse(all(V));
	int target = K - c;
	while(sz(V) > target) {
		auto p = V.back(); V.pop_back();
		ret += p.second;
	}
	for(auto p : V)
		ret += max(p.first + p.second,p.second);

//	cout << u << " " << c << " " << ret << endl;
	return ret;
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int Q; scanf("%d",&Q);
	while(Q--) {
		scanf("%d %d",&n,&K);
		for(int u = 1;u <= n;u++) E[u].clear();
		loop(e,n-1) {
			scanf("%d %d %d",fr + e,to + e,W + e);
			E[fr[e]].push_back(e);
			E[to[e]].push_back(e);
		}
		visNum++;
		printf("%lld\n",solve(1,0,0));
	}
	return 0;
}
/*
 * 2
4 1
1 2 5
3 1 2
3 4 3
7 2
1 2 5
1 3 4
1 4 2
2 5 1
2 6 2
4 7 3
 */
#endif
