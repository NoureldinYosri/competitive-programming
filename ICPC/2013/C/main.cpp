#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define popcnt(x) __builtin_popcountll(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
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
void addedge(int u, int v, int c1, int c2) {
	point[nedge] = v, capa[nedge] = c1, flow[nedge] = 0,
	nxt[nedge] = head[u], head[u] =(nedge++);
	point[nedge] = u, capa[nedge] = c2, flow[nedge] = 0,
	nxt[nedge] = head[v], head[v] =(nedge++);
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



const int MAX = 2*25000 + 10,INF = 1 << 29;
vi E[MAX],IN[MAX],OUT[MAX];
int indeg[MAX];
int n,m,c;
int fr[MAX],to[MAX],W[MAX];
int mydist[MAX];
int cnt[MAX];

void read(){
	scanf("%d %d %d",&n,&m,&c);
	loop(i,m) {
		scanf("%d %d %d",fr + i,to + i,W + i);
		E[fr[i]].pb(i);
		E[to[i]].pb(i);
	}
	loop(i,c) {
		int u ; scanf("%d",&u);
		cnt[u]++;
	}
}

void dijkstra(){
	PQ<pi> pq;
	fill(mydist,mydist + n+1,INF);
	pq.push(mp(0,1));
	mydist[1] = 0;
	while(!pq.empty()){
		int u = pq.top().yy,d = -pq.top().xx;
		pq.pop();
		if(d != mydist[u]) continue;
		for(int e : E[u]) {
			int v = fr[e] + to[e] - u;
			if(mydist[u] + W[e] < mydist[v]) {
				mydist[v] = mydist[u] + W[e];
				pq.push(mp(-mydist[v],v));
			}
		}
	}
}

void buildShortestPathDAG() {
	dijkstra();
	range(u,1,n) {
		for(int e : E[u]) {
			int v = fr[e] + to[e] - u;
			if(mydist[v] == mydist[u] + W[e]) {
				fr[e] = u;
				to[e] = v;
				OUT[u].pb(e);
				IN[v].pb(e);
				indeg[v]++;
			}
		}
	}
}

int myvis[MAX];

void dfs(int u) {
	myvis[u] = 1;
	for(int e : IN[u]) {
		addedge(u,fr[e],1,0);
		if(!myvis[fr[e]])
			dfs(fr[e]);
	}
}

void buildGraph(vi V) {
	init(n+1,0,1);
	for(int x : V)
		addedge(0,x,cnt[x],0);
	memset(myvis,0,sizeof myvis);
	for(int x : V)
		if(!myvis[x])
			dfs(x);
}


int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	read();
	buildShortestPathDAG();
	PQ<pi,vp,greater<pi> > pq;
	map<int,vi> M;
	range(u,1,n) if(mydist[u] < INF) {
		if(!cnt[u]) continue;
		M[mydist[u]].pb(u);
	}
	int ans = 0;
	for(auto p : M) {
		buildGraph(p.yy);
		int t = dinic_flow();
		ans += t;
	}
	cout << ans << endl;
	return 0;
}
