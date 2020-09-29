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

const int MAX = 500*1000 + 10, MAXE = 2*MAX;
int head[MAX], nxt[MAXE], to[MAXE], edge_cnt;
int siz[MAX], deepest[MAX], depth[MAX], n;

void add_edge(int a, int b){
	int e = edge_cnt++;
	to[e] = b;
	nxt[e] = head[a];
	head[a] = e;
}


void dfs(int u, int p){
	siz[u] = 1;
	deepest[u] = 1;
	for(int e = head[u]; ~e; e = nxt[e]) if(to[e] != p) {
		int v = to[e];
		dfs(v, u);
		siz[u] += siz[v];
		deepest[u] = max(deepest[u], deepest[v] + 1);
	}
}

int get_furthest(int u, int p){
	depth[u] = depth[p] + 1;
	int g = u;
	for(int e = head[u]; ~e; e = nxt[e]) if(to[e] != p) {
		int v = to[e];
		int c = get_furthest(v, u);
		if(depth[c] > depth[g]) g = c;
	}
	return g;
}

pi get_gain(int v, int m){
	if(2*siz[v] - deepest[v] <= m) return pi(siz[v], 2*siz[v] - deepest[v]);
	if(deepest[v] > m) return pi(m, m);
	int s = siz[v] - deepest[v];
	return pi(s/2 + deepest[v], (s - s%2) + deepest[v]);
}

int dfs(int u, int p, int m){
	if(m < 0) return 0;
	int ret = 1;
		
	int best = -1, f = 0;
	for(int e = head[u]; ~e; e = nxt[e]) if(to[e] != p) {
		int v = to[e];
		auto [gain, cost] = get_gain(v, m);
		gain += min(siz[u] - siz[v] - 1, (m - cost)/2);
		if(gain > f){
			f = gain;
			best = v;
		}
	}
	
	if(best == -1) return ret;
	
	auto [_, cost] = get_gain(best, m);
	int rem = m - cost;
	
	for(int e = head[u]; ~e; e = nxt[e]) if(to[e] != p && to[e] != best) {
		int v = to[e];
		int k = min(siz[v], rem/2);
		ret += k;
		rem -= 2*k;
	}
	cost += rem;
	ret += dfs(best, u, cost - 1);
	return ret;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	memset(head, -1, sizeof head);
	int m; scanf("%d %d", &n, &m);
	loop(i, n-1){
		int a, b; scanf("%d %d", &a, &b);
		add_edge(a, b);
		add_edge(b, a);
	}
	int root = get_furthest(1, 0);
	root = get_furthest(root, 0);
	//cerr << "root is " << root << endl;
	dfs(root, 0);
	cout << dfs(root, 0, m) << endl;
	return 0;
}
