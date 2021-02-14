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

const int maxnode = 30000 + 5;
const int maxedge = 2100000 + 5;
const int oo = 1000000000;
int node, src, dest, nedge;
int head[maxnode], point[maxedge], nxt[maxedge], flow[maxedge],
capa[maxedge];
int dist[maxnode], Q[maxnode], work[maxnode];

void init(int _node, int _src, int _dest) {
	node = _node;
	src = _src;
	dest = _dest;
	for (int i = 0; i < node; i++)
		head[i] = -1;
	nedge = 0;
}
int addedge(int u, int v, int c1, int c2) {
	point[nedge] = v, capa[nedge] = c1, flow[nedge] = 0,
	nxt[nedge] = head[u], head[u] =(nedge++);
	point[nedge] = u, capa[nedge] = c2, flow[nedge] = 0,
	nxt[nedge] = head[v], head[v] =(nedge++);
	return head[v];
}
bool dinic_bfs() {
	memset(dist, 255, sizeof(dist));
	dist[src] = 0;
	int sizeQ = 0;
	Q[sizeQ++] = src;
	for (int cl = 0; cl < sizeQ; cl++)
		for (int k = Q[cl], i = head[k]; i >= 0; i = nxt[i])
			if (flow[i] < capa[i] && dist[point[i]] < 0) {
				dist[point[i]] = dist[k] + 1;
				Q[sizeQ++] = point[i];
			}
	return dist[dest] >= 0;
}
int dinic_dfs(int x, int exp) {
	if (x == dest)
		return exp;
	for (int &i = work[x]; i >= 0; i = nxt[i]) {
		int v = point[i], tmp;
		if (flow[i] < capa[i] && dist[v] == dist[x] + 1 && (tmp = dinic_dfs(v, min(exp, capa[i] - flow[i]))) > 0) {
			flow[i] += tmp;
			flow[i ^ 1] -= tmp;
			return tmp;
		}
	}
	return 0;
}
int dinic_flow() {
	int result = 0;
	while (dinic_bfs()) {
		for (int i = 0; i < node; i++)
			work[i] = head[i];
		while (1) {
			int delta = dinic_dfs(src, oo);
			if (delta == 0)
				break;
			result += delta;
		}
	}
	return result;
}


int n, m;
vp P;
vi doSwap;

int getFlow(int k){
	init(n + m + 2, 0, n + m + 1);
	for(int i = 1; i <= n; i++)
		addedge(0, i, k, 0);
	for(int i = 1; i <= m; i++)
		addedge(i + n, n + m + 1, 1, 0);
	doSwap.clear();
	loop(j, m){
		auto [a, b] = P[j];
		int i = j + n + 1;
		addedge(a, i, 1, 0);
		doSwap.push_back(addedge(b, i, 1, 0));
	}
	int f = dinic_flow();
	for(int & e : doSwap) e = flow[e] < capa[e];
	return f;
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d", &n, &m);
	P.resize(m);
	for(auto & [a, b] : P) scanf("%d %d", &a, &b);
	int s = 0, e = min(n, m);
	while(s < e){
		int mid = (s + e) >> 1;
		if(getFlow(mid) == m) e = mid;
		else s = mid + 1;
	}
	getFlow(s);
	printf("%d\n", s);
	loop(i, m){
		auto [a, b] = P[i];
		if(doSwap[i]) swap(a, b);
		printf("%d %d\n", a, b);
	}
	return 0;
}
