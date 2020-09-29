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

vi fr, to, capacity, cost, nxt;
vi head;
int N, src, snk;
 

void init(){
	head.resize(N);
	fill(all(head), -1);
	fr.clear();
	to.clear();
	capacity.clear();
	cost.clear();
	nxt.clear();
} 

void add_edge(int a, int b, int cap, int w){
	int e = sz(fr);
	fr.pb(a);
	to.pb(b);
	capacity.pb(cap);
	cost.pb(w);
	nxt.pb(head[a]);
	head[a] = e;
}
 
void add_bi_edge(int a, int b, int cap, int c){
	add_edge(a , b, cap, c);
	add_edge(b, a, 0, -c);
}
 
vi dist, inEdge;
 
bool bellman(){
	dist.clear();
	inEdge.clear();
	dist.resize(N, 1 << 29);
	inEdge.resize(N, -1);
	
	dist[src] = 0;
	loop(i, N-1){
		bool done = 1;
		loop(e, sz(fr)) if(capacity[e]){
			int a = fr[e], b = to[e];
			if(dist[a] + cost[e] < dist[b]){
				dist[b] = dist[a] + cost[e];
				inEdge[b] = e;
			}
		}
		if(!done) break;
	}
	return inEdge[snk] != -1;
}
 
void augment(pi & ret){
	ret.first++;
	ret.second += dist[snk];
	for(int u = snk; u != src;){
		int e = inEdge[u];
		capacity[e] --;
		capacity[e^1] ++;
		u = fr[e];
	}
}
 
pair<int, int> MCMF(){
	pi ret;
	while(bellman())
		augment(ret);
	return ret;
}

int n, m;
int A[2000];

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	vi L1, L2;
	while(T--){
		scanf("%d %d", &n, &m);
		loop(i, n) scanf("%d", A + i);
		N = 2 + n + n + 1;
		src = 0;
		snk = N-1;
		init();
		add_bi_edge(src, 1, m, 0);
		L1.clear();
		L2.clear();
		int q = 1;
		loop(i, n) L1.pb(++q);
		loop(i, n) L2.pb(++q);
		
		loop(i, n) add_bi_edge(1, L1[i], 1, 0);
//		loop(i, n) add_bi_edge(L1[i], L2[i], 1, 0);
		loop(i, n) for(int j = i+1; j < n; j++) add_bi_edge(L2[i], L1[j], 1, abs(A[i] - A[j]));
		loop(i, n) add_bi_edge(L2[i], snk, 1, 0);
		cout << MCMF() << endl;	
	}
	return 0;
}
