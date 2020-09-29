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

const int MAX = 500*1000 + 10, MAXST = 1 << 22;

int n, m;
vi children[MAX], queries[MAX];
int parent[MAX], cost[MAX], big[MAX];
ll depth[MAX], ans[MAX];
ll ST[MAXST], LA[MAXST];
int L[MAX], R[MAX], V[MAX];



void build(int cur, int s, int e) {
	if (s == e) {
		ST[cur] = depth[s];
		return;
	}
	int m = (s + e) >> 1, left = 2*cur + 1, right = left + 1;
	build(left, s, m);
	build(right, m + 1, e);
	ST[cur] = min(ST[left], ST[right]);
}

void update(int cur, ll v) {
	ST[cur] += v;
	LA[cur] += v;
}

void push_down(int cur) {
	if (LA[cur] == 0) return;
	int left = 2*cur + 1, right = left + 1;
	update(left, LA[cur]);
	update(right, LA[cur]);
	LA[cur] = 0;
}

void update(int cur, int s, int e, int l, int r, ll v) {
	if (r < l) return;
	if (l <= s && e <= r) {
		update(cur, v);
		return;
	}
	push_down(cur);
	int m = (s + e) >> 1, left = 2*cur + 1, right = left + 1;
	if (r <= m) update(left, s, m, l, r, v);
	else if (m < l) update(right, m+1, e, l, r, v);
	else {
		update(left, s, m, l, m, v);
		update(right, m+1, e, m+1, r, v);
	}
	ST[cur] = min(ST[left], ST[right]);
}

ll query(int cur, int s, int e, int l, int r) {
	if (l <= s && e <= r) return ST[cur];
	push_down(cur);
	int m = (s + e) >> 1, left = 2*cur + 1, right = left + 1;
	if (r <= m) return query(left, s, m, l, r);
	else if (m < l) return query(right, m+1, e, l, r);
	else {
		ll a = query(left, s, m, l, m);
		ll b = query(right, m+1, e, m+1, r);
		return min(a, b);
	}
}

void dfs(int u) {
	for (int q : queries[u])
		ans[q] = query(0, 1, n, L[q], R[q]);
	for (int v : children[u]) {
		update(0,1,n,1,v-1, cost[v]);
		update(0, 1, n, v, big[v], -cost[v]);
		update(0, 1, n, big[v]+1, n, cost[v]);
		dfs(v);
		update(0,1,n,1,v-1, -cost[v]);
		update(0, 1, n, v, big[v], cost[v]);
		update(0, 1, n, big[v]+1, n, -cost[v]);
	}

}

int main(int argc, char **argv){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d", &n, &m);
	for (int i = 2; i <= n; i++) {
		int p, c; scanf("%d %d", &p, &c);
		children[p].pb(i);
		cost[i] = c;
		parent[i] = p;
		depth[i] = depth[p] + c;
	}


	for (int q = 0; q < m; q++){
		scanf("%d %d %d", V + q, L + q, R + q);
		queries[V[q]].pb(q);
	}

	for (int i = 1; i <= n; i++)
		if (!children[i].empty())
			depth[i] = 1LL << 60;
	for (int i = n; i >= 1; i--) {
		big[i] = max(big[i], i);
		big[parent[i]] = max(big[parent[i]], big[i]);
	}

	build(0, 1, n);
	dfs(1);
	for (int q = 0; q < m; q++)
		printf("%lld\n", ans[q]);

	return 0;
}
