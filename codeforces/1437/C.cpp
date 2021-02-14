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

vi fr, to, capacity, cost, nxt, head, dist, inEdge;
vector<bool> inQueue;
queue<int> q;

void add_edge(int a, int b, int c, int w) {
	int e = sz(fr);
	fr.push_back(a);
	to.push_back(b);
	capacity.push_back(c);
	cost.push_back(w);
	nxt.push_back(head[a]);
	head[a] = e;
}

void add_edge(int a, int b, int c1, int c2, int w){
	add_edge(a, b, c1, w);
	add_edge(b, a, c2, -w);
}

void clear(){
	fr.clear();
	to.clear();
	capacity.clear();
	cost.clear();
	nxt.clear();
	head.clear();
	dist.clear();
	inQueue.clear();
	inEdge.clear();
}

void init(int n){
	head.resize(3*n + 2, -1);
	dist.resize(3*n + 2);
	inQueue.resize(3*n + 2);
	inEdge.resize(3*n + 2);
}

bool spfa(int src, int snk){
	fill(all(dist), 1 << 29);
	fill(all(inQueue), false);
	q.push(src);
	inQueue[src] = true;
	dist[src] = 0;
	while(!q.empty()){
		int u = q.front(); 
		q.pop();
		inQueue[u] = false;
		for(int e = head[u]; ~e; e = nxt[e]) if(capacity[e]){
			int v = to[e];
			int nd = dist[u] + cost[e];
			if(nd < dist[v]){
				dist[v] = nd;
				inEdge[v] = e;
				if(!inQueue[v]){
					inQueue[v] = true;
					q.push(v);
				}
			}
		}
	}
	return dist[snk] < (1 << 29);
}

void augment(int src, int snk, int & f, int & c){
	int mn = INT_MAX;
	for(int u = snk; u != src; ){
		int e = inEdge[u];
		mn = min(mn, capacity[e]);
		u = fr[e];
	}
	f += mn;
	c += mn * dist[snk];
	for(int u = snk; u != src; ){
		int e = inEdge[u];
		capacity[e] -= mn;
		capacity[e^1] += mn;
		u = fr[e];
	}
}

pi MCMF(int src, int snk){
	int f = 0, c = 0;
	while(spfa(src, snk)) augment(src, snk, f, c);
	return pi(f, c);
}

void tc(){
	int n; scanf("%d", &n);
	clear();
	init(n);
	loop(i, n) add_edge(0, i + 1, 1, 0, 0);
	loop(i, n){
		int b; scanf("%d", &b); b--;
		loop(t, 2*n){
			add_edge(i + 1, t + n + 1, 1, 0, abs(t - b));
		}
	}
	loop(t, 2*n) add_edge(t + n + 1, 3*n + 1, 1, 0, 0);
	
	auto [f, c] = MCMF(0, 3*n + 1);
	printf("%d\n", c);
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--) tc();
	return 0;
}
