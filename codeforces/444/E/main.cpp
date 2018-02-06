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


const int maxnode = 3000*2 + 5;
const int maxedge = (3000*3000 + 2*3000 + 10)*2;
const int oo = 1000000000;
int node, src, dest, nedge;
short point[maxedge], flow[maxedge], capa[maxedge];
int head[maxnode],nxt[maxedge];
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





const int MAXN = 3000,MAXV = 2*MAXN + 2;
short W[MAXN],n,N;
int F[MAXN],T[MAXN],C[MAXN],ord[MAXN];
int id[MAXN],dsuW[MAXN];
list<int> cont[MAXN];

void init(){
	loop(i,n) addedge(0,i+1,1,0);
	loop(i,n) addedge(i+n+1,N-1,W[i],0);
}

int find(int a){
	return id[a] = (a == id[a]) ? a : find(id[a]);
}

void join(int a,int b) {
	a = find(a),b = find(b);
	if(a == b) return;
	if(dsuW[a] < dsuW[b]) swap(a,b);
	for(int x : cont[a])
		for(int y : cont[b]){
			addedge(x+1,y+n+1,1,0);
			addedge(y+1,x+n+1,1,0);
			cerr << x+1 << " " << y+n+1 << endl;
			cerr << y+1 << " " << x+n+1 << endl;
		}


	cont[a].splice(cont[a].end(),cont[b]);
	assert(cont[b].size() == 0);
	dsuW[a] += dsuW[b];
	id[b] = a;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%hd",&n);
	N = 2*n + 2;
	loop(e,n-1) {
		int a,b,c; scanf("%d %d %d",&a,&b,&c);
		--a,--b;
		F[e] = a;
		T[e] = b;
		C[e] = c;
		ord[e] = e;
	}
	loop(i,n) scanf("%hd",W + i);


	sort(ord,ord + n - 1,[](const int & a,const int & b) {
		return C[a] < C[b];
	});
	reverse(ord,ord + n - 1);

	loop(i,n) dsuW[i] = 1,id[i] = i,cont[i].push_back(i);


	init(N,0,N-1);
	init();
	int f = 0,ans = -1;
	for(int i = 0;i + 1 < n;) {
		int j = i;
		cerr << "W: " << C[ord[i]] << endl;
		while(j + 1 < n && C[ord[i]] == C[ord[j]]) {
			join(F[ord[j]],T[ord[j]]);
			j++;
		}
		f += dinic_flow();
		if(f == n) {
			ans = C[ord[i]];
			break;
		}
		i = j;
	}
	cout << ans << endl;
	return 0;
}
