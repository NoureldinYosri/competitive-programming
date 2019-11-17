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
const int MAX = 3e5 + 20;
int n,m;
ll dist[MAX];
int inEdge[MAX];
int fr[MAX],to[MAX],W[MAX];
vi E[MAX];
bool done[MAX];

using edge = pair<ll,int>;
priority_queue<edge,vector<edge>,greater<edge>> pq;

void solve(){
	static vi ord;
	while(!pq.empty()) pq.pop();
	for(int u = 1;u <= n;u++){
		dist[u] = oo;
		inEdge[u] = 0;
	}
	dist[1] = 0;
	pq.emplace(0,1);
	ord.clear();
	while(!pq.empty()) {
		ll d = pq.top().first;
		int u = pq.top().second;
		pq.pop();
		if(d != dist[u]) continue;
		if(inEdge[u]) {
			ord.push_back(inEdge[u]);
			done[inEdge[u]] = 1;
		}
		for(int e : E[u]) {
			int v = to[e];
			if(d + W[e] < dist[v]) {
				dist[v] = d + W[e];
				inEdge[v] = e;
				pq.emplace(dist[v],v);
			}
		}
	}
	for(int e = 1;e <= m;e++)
		if(!done[e])
			ord.push_back(e);
	assert(sz(ord) == m);
	for(int i = 0;i < m;i++)
		printf("%d%c",ord[i]," \n"[i==m-1]);
}

int main(){
	freopen("algoritm.in", "r", stdin);
	freopen("algoritm.out", "w", stdout);
	int T; scanf("%d",&T);
	while(T--) {
		scanf("%d %d",&n,&m);
		for(int u = 1;u <= n;u++) E[u].clear();
		for(int e = 1;e <= m;e++) {
			scanf("%d %d %d",fr + e,to + e,W + e);
			done[e] = 0;
			E[fr[e]].push_back(e);
		}
		solve();
	}
	return 0;
}
#endif
