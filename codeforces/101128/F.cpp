#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define pl pair<ll,ll>
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
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


char G[50][51];
int h,w;
int d,f,b;
int dx[] = {0,-1,0,1},dy[] = {-1,0,1,0};

int name(int x,int y){
	return x*w + y + 1;
}

void build_graph(){
	init(h*w + 2,0,h*w + 1);
	loop(i,h) loop(j,w){
		if(!i || !j || i==h-1 || j==w-1) addedge(0,name(i,j),oo,0);
		else if(G[i][j] == '#') addedge(0,name(i,j),d,0);
		else addedge(name(i,j),h*w + 1,f,0);
	}
	loop(i,h) loop(j,w) {
		loop(k,2){
			int nx = i + dx[k],ny = j + dy[k];
			if(nx < 0 || nx >= h || ny < 0 || ny >= w) continue;
			addedge(name(i,j),name(nx,ny),b,b);
		}
	}

}


int main(){
	scanf("%d %d",&w,&h);
	int ans = 0;
	scanf("%d %d %d",&d,&f);
	b = 0;
	loop(i,h) scanf("%s",G[i]);
	loop(i,h) {
		ans += f*(G[i][0] != '#');
		ans += f*(G[i][w-1] != '#');
		G[i][0] = G[i][w-1] = '#';
	}
	loop(i,w){
		ans += f*(G[0][i] != '#');
		ans += f*(G[h-1][i] != '#');
		G[0][i] = G[h-1][i] = '#';
	}
	build_graph();
	ans += dinic_flow();
	printf("%d\n",ans);
//		cerr << ans << endl;


	return 0;
}
