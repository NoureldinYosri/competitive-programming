#include <bits/stdc++.h>
 
using namespace std;
 
//#define int long long
#define all(x)  x.begin(), x.end()
#define rall(x) (x).rbegin(), (x).rend()
#define MP make_pair
#define pb push_back
#define fs first
#define sc second
#define forn(i, n) for (int i = 0; i < n; i++)
#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define sz(x) (int)(x).size()
#define sqr(x) ((x) * (x))
 
long long ans = 0;
const int N = 2e5 + 100;
int a[N], sizes[N], used[N];
vector<int> g[N];
 
 
struct line {
	long long k, b;
	long long eval(int x) {
		return k * x + b;
	}
};
 
line t[4 * N];
 
long long get(int v, int l, int r, int x) {
	if (l + 1 == r)
		return t[v].eval(x);
	int mid = (l + r) / 2;
	if (x < mid)
		return max(t[v].eval(x), get(v * 2 + 1, l, mid, x));
	return max(t[v].eval(x), get(v * 2 + 2, mid, r, x));
}
 
void upd(int v, int l, int r, line nw) {
	int m = (l + r) / 2;
	bool lef = nw.eval(l) > t[v].eval(l);
	bool mid = nw.eval(m) > t[v].eval(m);
	if (mid)
		swap(t[v], nw);
	if (l + 1 == r)
		return;
	if (mid != lef)
		upd(v * 2 + 1, l, m, nw);
	else upd(v * 2 + 2, m, r, nw);
}
 
void getS(int v, int p) {
	sizes[v] = 1;
	for (auto u : g[v])
		if (!used[u] && u != p) {
			getS(u, v);
			sizes[v] += sizes[u];
		}
}
 
int centroid(int v, int p, int n) {
	for (auto u : g[v])
		if (!used[u] && u != p && sizes[u] > n / 2)
			return centroid(u, v, n);
	return v;
}
 
void dfs0(int v, int p, int depth, long long s, long long ts) {
	s += a[v];
	ts += s;
	long long res = get(0, 0, N, depth) + ts;
	ans = max(ans, res);
	for (auto u : g[v])
		if (u != p && !used[u])
			dfs0(u, v, depth + 1, s, ts);
}
 
void dfs1(int v, int p, int depth, long long s, long long ts) {
	s += a[v];
	ts += 1ll * a[v] * depth;
	line nw = { s, ts };
	upd(0, 0, N, nw);
	for (auto u : g[v])
		if (u != p && !used[u]) {
			dfs1(u, v, depth + 1, s, ts);
		}
}
 
void clear(int v, int l, int r) {
	if (t[v].k != 0) {
		t[v].k = t[v].b = 0;
		int mid = (l + r) / 2;
		if (l + 1 == r)
			return;
		clear(v * 2 + 1, l, mid);
		clear(v * 2 + 2, mid, r);
	}
}
 
void go(int v) {
	used[v] = 1;
	getS(v, -1);
 
	for (int tt = 0; tt < 2; tt++) {
		for (auto u : g[v]) {
			if (!used[u]) {
				dfs0(u, -1, 2, a[v], a[v]);
				dfs1(u, -1, 1, 0, 0);
			}
		}
		ans = max(ans, get(0, 0, N, 1) + a[v]);
		clear(0, 0, N);
		reverse(all(g[v]));
	}
 
	for (auto u : g[v])
		if (!used[u])
			go(centroid(u, v, sizes[u]));
}
 
 
signed main() {
	fastio;
 
	int n;
	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		int x, y;
		cin >> x >> y;
		x--; y--;
		g[x].pb(y);
		g[y].pb(x);
	}
	for (int i = 0; i < n; i++)
		cin >> a[i];
 
	go(centroid(0, 0, n));
 
	cout << ans << '\n';
}
