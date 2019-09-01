#ifdef ACTIVE
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
#define tc() int T; scanf("%d",&T); for(int t = 1;t <= T;t++)
using namespace std;

const int MAX = 1 << 20;
int src,snk;
int N;
vi E[MAX];
int fr[MAX],to[MAX],C[MAX],cost[MAX],m;

void addEdge(int a,int b,int c,int w) {
	fr[m] = a;
	to[m] = b;
	C[m] = c;
	cost[m] = w;
	E[a].push_back(m);
	m++;
}
void addBiEdge(int a,int b,int c,int w) {
	addEdge(a,b,c,w);
	addEdge(b,a,0,-w);
}

vi G[MAX];
bool vis[MAX];

void dfs(int u,int c,int w) {
	if(vis[u]) return;
	vis[u] = 1;
	for(int v : G[u]) {
		addBiEdge(u,v,c,w);
		dfs(v,1,1);
	}
}

int iE[MAX];
int dist[MAX];
queue<int> q;

bool bellman(){
	const int oo = 1 << 29;
	fill(dist,dist + N,oo);
	dist[src] = 0;
	bool change = 1;
	for(int k = 0;k < N-1 && change;k++) {
		change = 0;
		loop(e,m) if(C[e]){
			int a = fr[e],b = to[e];
			if(dist[a] + cost[e] < dist[b]) {
				dist[b] = dist[a] + cost[e];
				iE[b] = e;
				change = 1;
			}
		}
	}
	return dist[snk] != oo;
}

int augment(int & w){
	int u = snk;
	while(u != src) {
		int e = iE[u];
		C[e] --;
		C[e^1] ++;
		u = fr[e];
	}
	w += dist[snk];
	return 1;
}

int maxflow(int & w){
	int f = 0;
	while(bellman()) f += augment(w);
	return f;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int P,R,L; scanf("%d %d %d",&P,&R,&L);
	int root = R;
	src = root + 1;
	snk = src + 2;
	N = snk + 1;

	auto getName = [root](const int & x) {
		if(x >= 0) return x;
		if(x == -1) return root;
		else return snk;
	};
	loop(i,L){
		int a,b; scanf("%d %d",&a,&b);
		a = getName(a);
		b = getName(b);
		G[a].push_back(b);
		G[b].push_back(a);
	}
	G[src].push_back(root);
	dfs(src,P,0);
	int w = 0;
	int f = maxflow(w);
	if(f == P) printf("%d\n",w);
	else printf("%d people left behind\n",P - f);
	return 0;
}
#endif
