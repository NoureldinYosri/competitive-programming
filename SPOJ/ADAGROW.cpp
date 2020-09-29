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

const int MAXN = 2 << 10, MAXK = 22;
int A[MAXN], N;
vi fr, to, capacity, cost, nxt;
vi head;
vi dist, in_queue, in_edge;
queue<int> q;

void init(){
	fr.clear();
	to.clear();
	capacity.clear();
	cost.clear();
	nxt.clear();
	head.clear();
	dist.clear();
	in_queue.clear();
	in_edge.clear();

	head.resize(N, -1);
	dist.resize(N);
	in_queue.resize(N);
	in_edge.resize(N);
}

void add_edge(int a, int b, int c, int w){
	int e = fr.size();
	nxt.pb(head[a]);
	head[a] = e;
	
	fr.pb(a);
	to.pb(b);
	capacity.pb(c);
	cost.pb(w);
}

void add_edge(int a, int b, int c1, int c2, int w){
	cerr << a << " " << b << " " << c1 << "," << w << endl;
	add_edge(a, b, c1, w);
	add_edge(b, a, c2, -w);
}

bool spfa(){
	while(!q.empty()) q.pop();
	fill(all(in_queue), 0);
	fill(all(dist), 1 << 29);
	dist[0] = 0;
	in_queue[0] = 1;
	q.push(0);
	while(!q.empty()){
		int u = q.front(); 
		q.pop(); in_queue[u] = 0;
//		cerr << u << " " << N-1 << endl;
		if(u == N-1) return 1;
		for(int e = head[u]; ~e; e = nxt[e]) if(capacity[e]){
			int d = dist[u] + cost[e];
			int v = to[e];
			if(d < dist[v]){
				dist[v] = d;
				in_edge[v] = e;
				if(!in_queue[v]){
					q.push(v);
					in_queue[v] = 1;
				}
			}
		}
	}
	return 0;
}

void augment(int & f, int & c){
	c += dist.back();
	f ++;
	for(int u = N-1; u; u = fr[in_edge[u]]){
		int e = in_edge[u];
		capacity[e]--;
		capacity[e^1]++;
	}
}

pi MCMF(){
	int f = 0, c = 0;
	while(spfa()) augment(f, c);
	return pi(f, c);
}

void build_graph(int n, int k){
	N = 2*n + 3;
	init();
	add_edge(0, 1, k, 0, 0);
	for(int i = 2; i <= n+1; i++){
		add_edge(0, i + n, 1, 0, 1 << 29);		
		add_edge(1, i, 1, 0, 0);
	}

	loop(i, n){
		int a = i + 2;
		for(int j = i; j < n; j++){
			int b = j + 2 + n;
			add_edge(a, b, 1, 0, abs(A[i] - A[j]));
		}
	}
	loop(j, n) for(int i = j+1; i < n; i++) add_edge(j+2+n, i+2, 1, 0, abs(A[i] - A[j]));
	for(int i = n+2; i + 1 < N; i++)
		add_edge(i, N-1, 1, 0, 0);
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--){
		int n, k; scanf("%d %d", &n, &k);
		loop(i, n) scanf("%d", A + i);
		build_graph(n, k);
		cerr << MCMF() << endl;
//		printf("%d\n", dp[n-1][k]);
	}
	return 0;
}
