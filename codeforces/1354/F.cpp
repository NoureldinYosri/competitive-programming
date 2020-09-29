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

const int MAX = 300;
int dist[MAX], N, src, snk, in_edge[MAX];
vector<list<int>> E;
vi fr, to, capacity, cost;
int A[MAX], B[MAX], n;
vi potential;

void init(){
	E.clear();
	fr.clear();
	to.clear();
	capacity.clear();
	cost.clear();
	potential.clear();
	
	E.resize(N);
	potential.resize(N, 0);
}



void add_edge(int a, int b, int cap, int weight){
	int e = sz(fr);
	fr.pb(a);
	to.pb(b);
	capacity.pb(cap);
	cost.pb(weight);
	E[a].pb(e);
} 

void add_bi_edge(int a, int b, int c1, int c2, int w){
	add_edge(a, b, c1, w);
	add_edge(b, a, c2, -w);
}


void augment(int & flow, int & cost){
	int f = INT_MAX;
	for(int u = snk; u != src; ){
		int e = in_edge[u];
		f = min(f, capacity[e]);
		u = fr[e];
	}
	for(int u = snk; u != src; ){
		int e = in_edge[u];
		capacity[e] -= f;
		capacity[e^1] += f;
		u = fr[e];
	}
	flow += f;
	cost += f*(dist[snk] - potential[src] + potential[snk]);
}


void build_network(int k){
	N = n+k+1+2 + 1;
	src = 0;
	snk = N-1;
	init();
	for(int i = 1; i <= n; i++){
		add_bi_edge(src, i, 1, 0, 0);
		for(int j = 1; j <= k+1; j++){
			int coef = j-1;
			if(coef == k) coef = k-1;
			int value = coef*B[i];
			if(j <= k) value += A[i];
			add_bi_edge(i, j + n, 1, 0, -value);
		}
	}
	for(int j = 1; j <= k+1; j++)
		add_bi_edge(j+n, snk, (j <= k) ? 1 : (n - k), 0, 0);	
}

void bellman(){
	fill(all(potential), 0);
	loop(i, N-1) add_bi_edge(i, N-1, 0, 0, 0);
	loop(t, N){
		bool change = 0;
		int m = sz(fr);
		loop(e, m){
			int a = fr[e], b = to[e], c = cost[e];
			if(potential[a] + c < potential[b]){
				potential[b] = potential[a] + c;
				change = 1;
			}
		}
		if(!change) break;
		if(change && t == N-1){
			cerr << "negative cycle" << endl;
		}
	}
	print(potential, int);
	int m = sz(fr);
	loop(e, m){
		int a = fr[e], b = to[e], c = cost[e];
		cerr << a << " " << b << " " << c + potential[a] - potential[b] << endl;
	}
}

bool dijkstra(){
	static priority_queue<pi, vector<pi>, greater<pi>> pq;
	while(!pq.empty()) pq.pop();
	fill(dist, dist + N, 1 << 29);
	pq.emplace(0, src);
	dist[src] = 0;
//	cerr << "Dijkstra" << endl;
	while(!pq.empty()){
		auto [d, u] = pq.top(); pq.pop();
		if(dist[u] != d) continue;
//		cerr << u << " " << d << endl;
		if(u == snk) return 1;
		for(int e : E[u]) if(capacity[e]){
			int v = to[e];
			int w = cost[e] + potential[u] - potential[v];
			if(dist[u]+w < dist[v]){
				dist[v] = dist[u] + w;
				in_edge[v] = e;
				pq.emplace(dist[v], v);
			}
		}
	}
	return 0;
}

void mcmf(){
	int f = 0, c = 0;
	bellman();
	while(dijkstra()) augment(f, c);	
//	cerr << f << " " << c << endl;
}

void build_answer(int k){
	vi B;
	vi A(k, INT_MAX);
	for(int i = 1; i <= n; i++)
		for(int e : E[i])
			if(capacity[e] == 0 && e%2 == 0){
				int pos = to[e] - n - 1;
				if(pos == k) B.pb(i);
				else A[pos] = i;
			}
	printf("%d\n", k + 2*(n - k));
	loop(i, k-1) printf("%d ", A[i]);
	for(int x : B) printf("%d %d ", x, -x); 	
	printf("%d\n", A.back());
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--){
		int k; scanf("%d %d", &n, &k);
		for(int i = 1; i <= n; i++)
			scanf("%d %d", A + i, B + i);
		build_network(k);
		mcmf();
		build_answer(k);
	}
		
	return 0;
}
