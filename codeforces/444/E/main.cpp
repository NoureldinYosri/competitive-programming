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

const int MAXN = 3000*2 + 2 + 5;
int node_cnt,src,snk;
int capa[MAXN][MAXN],parent[MAXN];
vi adj[MAXN];

void init(int _cnt,int _src,int _snk){
	node_cnt = _cnt;
	src = _src;
	snk = _snk;
	memset(capa,0,sizeof capa);
	loop(i,node_cnt) adj[i].clear();
}

void addedge(int fr,int to,int c1,int c2){
	capa[fr][to] += c1;
	capa[to][fr] += c2;
	adj[fr].pb(to);
	adj[to].pb(fr);
}


bool bfs(){
	queue<int> q;
	q.push(src);
	memset(parent,-1,sizeof parent);
	parent[src] = -2;
	while(!q.empty()){
		int u = q.front(); q.pop();
		if(u == snk) return 1;
		for(int v : adj[u]) if(capa[u][v]) if(parent[v] == -1){
			parent[v] = u;
			q.push(v);
		}
	}
	return 0;
}

void augment(){
	static vi path;
	path.clear();
	int cur = snk;
	while(cur != -2) {
		path.pb(cur);
		cur = parent[cur];
	}
	reverse(all(path));
	for(int i = 0;i + 1 < sz(path);i++){
		int u = path[i],v = path[i + 1];
		capa[u][v] --;
		capa[v][u] ++;
	}
}

int maxflow(){
	int f = 0;
	while(bfs()) {
		f++;
		augment();
	}
	return f;
}

int tree_dist[3001][3001];
int tree_n;
vp G[3001];
int lim[3001];

void dfs(int u,int p,int src){
	for(auto e : G[u]) if(e.xx != p) {
		tree_dist[src][e.xx] = max(tree_dist[src][u] , e.yy);
		dfs(e.xx,u,src);
	}
}

void build_graph(int Th){
	int src = 0,snk = 2*tree_n + 1;
	init(2*tree_n+2,src,snk);
	range(i,1,tree_n) addedge(src,i,lim[i],0);
	range(i,1,tree_n) range(j,1,tree_n) if(tree_dist[i][j] >= Th) addedge(i,j+tree_n,1,0);
	range(i,1,tree_n) addedge(i+tree_n,snk,1,0);
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d",&tree_n);
	loop(i,tree_n-1){
		int a,b,c; scanf("%d %d %d",&a,&b,&c);
		G[a].pb(mp(b,c));
		G[b].pb(mp(a,c));
	}
	range(i,1,tree_n) scanf("%d",lim + i);
	range(i,1,tree_n) dfs(i,0,i);
	int s = 0,e = 10000;
	while(s < e) {
		int m = s + (e - s + 1)/2;
		build_graph(m);
		if(maxflow() == tree_n) s = m;
		else e = m - 1;
	}
	cout << s << endl;
	return 0;
}
