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

const int oo = 1 << 29;
int N, src, snk;
vi fr, to, cost, capacity, nxt;
vi head, InEdge;
vector<bool> inQueue;
queue<int> q;
vector<ll> dist, potential;

void init(){
	src = 0;
	snk = N-1;
	head.resize(N, -1);
	InEdge.resize(N);
	inQueue.resize(N);
	dist.resize(N);
	potential.resize(N);
}

int addEdge(int a, int b, int cap, int w){
	int e = sz(fr);
	nxt.push_back(head[a]);
	head[a] = e;
	fr.push_back(a);
	to.push_back(b);
	capacity.push_back(cap);
	cost.push_back(w);
	return e;
}

int addBiEdge(int a, int b, int w, int c1, int c2){
	addEdge(a, b, c1, w);
	return addEdge(b, a, c2, -w);
//	cerr << a << " " << b << " " << pi(c1, w) << endl;
}


vi tasks;

void buildGraph(){
	int n, m; scanf("%d %d", &n, &m);
	vi fr, to, profit;
	vi T;
	loop(i, n) {
		int s, e, c; scanf("%d %d %d", &s, &e, &c);
		e += s;
		fr.push_back(s);
		to.push_back(e);
		profit.push_back(c);
		T.push_back(s);
		T.push_back(e);
	}
	sort(all(T));
	T.resize(unique(all(T)) - T.begin());
	N = m + sz(T) + 2;
	init();
	for(int i = 1; i <= m; i++) {
		addBiEdge(src, i, 0, 1, 0);
		for(int t = 0; t < sz(T); t++) {
			addBiEdge(i, t + m + 1, 0, 1, 0);
		}
	}
	for(int t = 0; t < sz(T); t++){
		addBiEdge(t + m + 1, snk, 0, oo, 0);
		if(t + 1 < sz(T))
			addBiEdge(t + m + 1, t + m + 2, 0, oo, 0);
	}
	loop(i, n){
		fr[i] = lower_bound(all(T), fr[i]) - T.begin();
		to[i] = lower_bound(all(T), to[i]) - T.begin();
		tasks.push_back(addBiEdge(fr[i] + m + 1, to[i] + m + 1, -profit[i], 1, 0));
	}
}


bool SPFA(){
	while(!q.empty()) q.pop();
	fill(all(dist), 1LL << 60);
	dist[0] = 0;
	q.push(0);
	inQueue[0] = true;
	bool visited = false;
	while(!q.empty()){
		int u = q.front(); q.pop();
		inQueue[u] = false;
		visited |= u == snk;
		for(int e = head[u]; ~e; e = nxt[e]) if(capacity[e]){
			int v = to[e];
			if(dist[u] + cost[e] < dist[v]){
				dist[v] = dist[u] + cost[e];
				InEdge[v] = e;
				if(!inQueue[v]) {
					q.push(v);
					inQueue[v] = true;
				}
			}
		}
	}
	return visited;
}

void augment(int & flow, ll & cost){
	int f = INT_MAX;
	for(int u = snk; u != src; ){
		int e = InEdge[u];
		f = min(f, capacity[e]);
		u = fr[e];
	}
	for(int u = snk; u != src; ){
		int e = InEdge[u];
		capacity[e] -= f;
		capacity[e^1] += f;
		u = fr[e];
	}
	flow += f;
	cost += f*(dist[snk] - potential[src] + potential[snk]);
}

void update(){
	loop(i, N) {
		potential[i] += dist[i];
		potential[i] = min(potential[i], 1LL << 60);
	}
}

priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;

bool dijkstra(){
	fill(all(dist), 1LL << 60);
	while(!pq.empty()) pq.pop();
	dist[src] = 0;
	pq.emplace(dist[src], src);
	while(!pq.empty()){
		auto [d, u] = pq.top(); pq.pop();
		if(u == snk) return true;
		assert(d >= dist[u]);
		if(d != dist[u]) continue;
		for(int e = head[u]; ~e; e = nxt[e]) if(capacity[e]) {
			int v = to[e];
			ll w = cost[e] - (potential[v] - potential[u]);
			if(dist[u] + w < dist[v]){
				InEdge[v] = e;
				dist[v] = dist[u] + w;
				pq.emplace(dist[v], v);
			}
		}
	}
	
	return false;
}

ll MCMF(){
	int f = 0;
	ll cost = 0;
	ll ans = 0;
	SPFA();
	update();
//	print(potential, ll);
	while(dijkstra()) {
		augment(f, cost);
		ans = max(ans, -cost);
		update();
	}
	return ans;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	buildGraph();
	cerr << MCMF() << endl;
	for(int t : tasks)
		printf("%d ", capacity[t]);
	puts("");
	return 0;
}
