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

const int MAX = 300, MAXE = MAX*MAX;
int dist[MAX], N, src, snk, in_edge[MAX], in_queue[MAX];
vector<list<int>> E;
int fr[MAXE], to[MAXE], capacity[MAXE], cost[MAXE], edge_cnt;
int A[MAX], B[MAX], n;

void add_edge(int a, int b, int cap, int weight){
	int e = edge_cnt++;
	fr[e] = a;
	to[e] = b;
	capacity[e] = cap;
	cost[e] = weight;
	E[a].pb(e);
} 

void add_bi_edge(int a, int b, int c1, int c2, int w){
	add_edge(a, b, c1, w);
	add_edge(b, a, c2, -w);
}

queue<int> q;
bool spfa(){
	fill(dist, dist + N, 1 << 29);
	fill(in_edge, in_edge + N, -1);
	fill(in_queue, in_queue + N, 0);
	while(!q.empty()) q.pop();
	q.push(src);
	dist[src] = 0;
	in_queue[src] = 1;
	while(!q.empty()){
		int u = q.front(); q.pop();
		in_queue[u] = 0;
		for(int e : E[u]) if(capacity[e]){
			int v = to[e];
			if(dist[u]+cost[e] < dist[v]){
				dist[v] = dist[u] + cost[e];
				in_edge[v] = e;
				if(!in_queue[v]) q.push(v), in_queue[v] = 1;
			}
		}
	}
	return in_edge[snk] != -1;
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
	cost += f*dist[snk];
}

void init(){
	edge_cnt = 0;
	E.clear();
	E.resize(N);
}

void build_network(int k){
	N = n+k+1+2;
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

void mcmf(){
	int f = 0, c = 0;
	while(spfa()) augment(f, c);	
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