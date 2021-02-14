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

const int MAXN = 5 << 10;
int dist[2][MAXN], n, m, s, b;
vp G[MAXN], rG[MAXN];
priority_queue<pi, vector<pi>, greater<pi>> pq;
int f[MAXN];

void dijkstra(int root, int *dist, vp *G){
	fill(dist, dist + n + 1, 1 << 29);
	dist[root] = 0;
	while(!pq.empty()) pq.pop();
	pq.emplace(0, root);
	while(!pq.empty()){
		auto [d, u] = pq.top(); pq.pop();
		if(d > dist[u]) continue;
		for(auto [v, c] : G[u]){
			int nd = d + c;
			if(nd < dist[v]){
				dist[v] = nd;
				pq.emplace(nd, v);
			} 
		}
	}
}

ll dp[MAXN][MAXN];
ll pref[MAXN];


void DC(int k, int s, int e, int l, int r){
	if(s > e) return;
	int m = (s + e) >> 1;
	dp[k][m] = 1LL << 60;
	int best = l;
	for(int t = l; t <= r && t <= m; t++){
		int len = m - t + 1;
		ll tmp = dp[k-1][t - 1] + (len - 1) * (pref[m] - pref[t - 1]);
		if(tmp < dp[k][m]){
			dp[k][m] = tmp;
			best = t;
		}
	}
	
	DC(k, s, m - 1, l, best);
	DC(k, m + 1, e, best, r);	
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d %d %d", &n, &b, &s, &m);
	loop(e, m){
		int f, t, w; scanf("%d %d %d", &f, &t, &w);
		G[f].emplace_back(t, w);
		rG[t].emplace_back(f, w);
	}
	dijkstra(b + 1, dist[0], G);
	dijkstra(b + 1, dist[1], rG);
	for(int i = 1; i <= b; i++) {	
		f[i] = dist[0][i] + dist[1][i];
	}
	sort(f + 1, f + b + 1);
	dp[0][0] = 0;
	for(int i = 1; i <= b; i++){
		pref[i] = pref[i - 1] + f[i];
		dp[0][i] = 1LL << 60;
	}	
	for(int i = 1; i <= s; i++) {
		DC(i, 1, b, 1, b);
	//	prArr(dp[i], b + 1, ll);
	}
	printf("%lld\n", dp[s][b]);
	return 0;
}
