#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
using vi = std::vector<int>;
using pi = std::pair<int,int>;
using vp = std::vector<pi>;
using ll = long long;
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
template<class A,class B>
std::ostream& operator << (std::ostream& st,const std::pair<A,B> p) {
	st << "(" << p.first << ", " << p.second << ")";
	return st;
}
void tc();
auto test_cases = [](){
	int T; scanf("%d", &T);
	while(T--) tc();
};
using namespace std;


int n, m, K;

ll dp[2][1 << 20], B[1 << 20];
vp adj[1 << 20];

vector<pair<ll, ll>> lines;


ll dot(pair<ll, ll> & p, ll x) {
	return p.first * x + p.second;
}


pair<ll, ll> line[1 << 20];

void insert(int cur, int s, int e, pair<ll, ll> nw) {
    int left = 2*cur + 1, right = left + 1, m = (s + e) / 2;
    bool lef = dot(nw, s) < dot(line[cur], s);
    bool mid = dot(nw, m) < dot(line[cur], m);
    if(mid) {
        swap(line[cur], nw);
    }
    if(e - s == 1) {
        return;
    } else if(lef != mid) {
        insert(left, s, m, nw);
    } else {
        insert(right, m, e, nw);
    }
}

void build(int cur, int s, int e) {
	line[cur] = pair<ll, ll>(0, 1LL << 60);
	if(e - s == 1) {
        return;
    }
    int left = 2*cur + 1, right = left + 1, m = (s + e) / 2;
	build(left, s, m);
	build(right, m, e);
}

ll query(int cur, int s, int e, int x) {
    int left = 2*cur + 1, right = left + 1, m = (s + e) / 2;
    if(e - s == 1) {
        return dot(line[cur], x);
    } else if(x < m) {
        return min(dot(line[cur], x), query(left, s, m, x));
    } else {
        return min(dot(line[cur], x), query(right, m, e, x));
    }
}

void CH(ll *f) {
	build(0, 0, n-1);
	loop(i, n) {
		insert(0, 0, n-1, pair<ll, ll>(-2*i, f[i] + i*(ll)i));
	}
	loop(i, n) {
		B[i] = query(0, 0, n-1, i) + i*(ll)i;
	}
	// loop(i, n) {
	// 	B[i] = 1LL << 60;
	// 	loop(j, n) {
	// 		auto p = pair<ll, ll>(-2*j, f[j] + j*(ll)j);
	// 		B[i] = min(B[i], dot(p, i));
	// 	}
	// 	B[i] += i*(ll)i;
	// }
	// prArr(B, n, ll);
}

ll dist[1 << 20];
priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;

void dijkstra() {
	loop(i, n)
		pq.emplace(dist[i], i);
	while(!pq.empty()) {
		auto [d, u] = pq.top(); pq.pop();
		if(d != dist[u]) continue;
		for(auto [v, w] : adj[u]) {
			if(d + w < dist[v]) {
				dist[v] = d + w;
				pq.emplace(dist[v], v);
			}
		}
	}
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d %d", &n, &m, &K);
	loop(e, m) {
		int u, v, w; scanf("%d %d %d", &u, &v, &w);
		u--, v--;
		adj[u].emplace_back(v, w);
		adj[v].emplace_back(u, w);
	}

	fill(dist, dist + n, 1LL << 60);
	dist[0] = 0;
	dijkstra();
	loop(i, n) dp[0][i] = dist[i];

	for(int k = 1; k <= K; k++) {
		int cur = k & 1;
		int other = cur ^ 1;
		loop(i, n) dp[cur][i] = dp[other][i];
		CH(dp[other]);
		loop(i, n) dp[cur][i] = min(dp[cur][i], B[i]);
		copy(dp[cur], dp[cur] + n, dist);
		dijkstra();
		copy(dist, dist + n, dp[cur]);
	}
	loop(i, n) printf("%lld ", dp[K & 1][i]);
	puts("");
	return 0;
}
