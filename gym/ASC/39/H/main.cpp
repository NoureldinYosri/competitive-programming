#pragma GCC optimize ("O3")
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
#define pl pair<ll,ll>
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
int addedge(int u, int v, int c1, int c2) {
	point[nedge] = v, capa[nedge] = c1, flow[nedge] = 0,
	nxt[nedge] = head[u], head[u] =(nedge++);
	point[nedge] = u, capa[nedge] = c2, flow[nedge] = 0,
	nxt[nedge] = head[v], head[v] =(nedge++);
	return nedge - 2;
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


int n,m,k;
int E[100*100][2];
int deg[111];

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d %d",&n,&m,&k);
	int src = 0,snk = n + 1;
	loop(i,m) loop(j,2) {
		scanf("%d",&E[i][j]);
		deg[E[i][j]]++;
	}

	for(int s = 2;s <= n;s++){
		int a = k*(s - 1),b = s;
		int g = __gcd(a,b);
		a /= g,b /= g;
		init(n+2,src,snk);
		range(i,1,n) addedge(src,i,b*m,0);
		loop(i,m) addedge(E[i][0],E[i][1],b,b);
		range(i,1,n) addedge(i,snk,b*m + 2*a + 2  - b*deg[i],0);

		cerr << s << " " << dinic_flow() ;
		vi V;
		for(int i = 0;i < 2*n;i += 2)
			if(capa[i] - flow[i])
				V.pb(i/2 + 1);
		cerr << " " << sz(V) << " " << a << "/" << b << endl;

		if(0 && !V.empty()) {
			cout << "found " << s << " " << a << "/" << b << endl;
			print(V,int);
			return 0;
		}
	}
	puts("OK");
	return 0;
}
