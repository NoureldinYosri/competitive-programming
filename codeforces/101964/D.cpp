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

const int MAXE = 2 << 20,MAXN = 3 << 10;
const ll oo = 1LL << 60;
int N,M,K;
int fr[MAXE],to[MAXE],cap[MAXE],W[MAXE];
ll dist[MAXN];
vp G[MAXN],E[MAXN];

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	tc(){
		scanf("%d %d %d",&N,&M,&T);
		loop(i,N+1) G[i].clear();
		ll ans = 0;
		loop(e,N-1) {
			int a,b,c; scanf("%d %d %d",&a,&b,&c);
			G[a].emplace_back(b,c);
			G[b].emplace_back(a,c);
		}
		for(int u = 1;u <= n;u++) dfs(u,0);

	}
	return 0;
}
