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
 



const int MAXN = 55;
int low[MAXN], high[MAXN], n;


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int q; scanf("%d %d", &n, &q);
	for(int i = 1; i <= n;i++) low[i] = 1, high[i] = n;
	while(q--){
		int t, l, r, v; scanf("%d %d %d %d", &t, &l, &r, &v);
		if(t == 1){
			for(int i = l; i <= r; i++) low[i] = max(low[i], v);
		}
		else {
			for(int i = l; i <= r; i++) high[i] = min(high[i], v);			
		}
	}
	for(int i = 1; i <= n; i++)
		if(low[i] > high[i]){
			puts("-1");
			return 0;
		}
	
	N = 1 + n + n + 1;
	head.resize(N, -1);
	
	src = 0;
	snk = N-1;
	
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			add_bi_edge(src, i, 1, 2*j - 1);
	
//	prArr(low + 1, n , int);
//	prArr(high+ 1, n , int);
	for(int i = 1; i <= n; i++)
		for(int j = low[i]; j <= high[i]; j++)
			add_bi_edge(j, i + n, 1, 0);
	
	for(int i = 1; i <= n; i++)
		add_bi_edge(i + n, snk, 1, 0);
	cout << MCMF().second << endl;
		
	return 0;
}
