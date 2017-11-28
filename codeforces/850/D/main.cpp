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
	int e = nedge;
	point[nedge] = v, capa[nedge] = c1, flow[nedge] = 0,
	nxt[nedge] = head[u], head[u] =(nedge++);
	point[nedge] = u, capa[nedge] = c2, flow[nedge] = 0,
	nxt[nedge] = head[v], head[v] =(nedge++);
	return e;
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




int INF = 1 << 29;
int A[31],n;
int dp [31][70][70*70][2];
int mynxt[31][70][70*70][2];
vi D;
int E[70][70];

void get_deg(){
	int cur = 0,k = 0,r = 0,inSet = 0;
	while(cur != n){
//		cerr << cur << " " << k << " " << r << " " << inSet << endl;
		int v = mynxt[cur][k][r][inSet];
		assert(v);
		if(v == 1){
			cur++;
			inSet = 0;
		}
		else {
			r = r + A[cur] - k;
			D.pb(A[cur]);
			inSet = 1;
			k++;
		}
	}
}

int solve(int cur,int k,int r,int inSet){
	if(cur == n) return (r == 0) ? k : INF;
	int & ret = dp[cur][k][r][inSet];
	if(ret != -1) return ret;
	ret = INF;
	if(inSet) ret = solve(cur+1,k,r,0),mynxt[cur][k][r][inSet] = 1;
	if(A[cur] + r >= k) {
		int tmp = solve(cur,k+1,A[cur] + r - k,1);
		if(tmp < ret){
			ret = tmp;
			mynxt[cur][k][r][inSet] = 2;
		}
	}
	return ret;
}

int name[70][70],oname[70][70],lstname[70];
int IDX[70][70];

void build_graph(){
	int N = sz(D);
	int M = 2*N*(N-1) + 2*N + 2;
	int src = 0,snk = M - 1;
	init(M,src,snk);
	for(int i = 0;i < N;i++) addedge(src,i+1,D[i],0);
	int idx = N;
	for(int i = 0;i < N;i++)
		for(int j = i+1;j < N;j++){
			name[i][j] = ++idx;
			oname[i][j] = ++idx;
		}
	for(int i = 0;i < N;i++)
		lstname[i] = ++idx;

	for(int i = 0;i < N;i++)
		for(int j = 0;j < N;j++)
			if(i != j) {
				int x = min(i,j);
				int y = max(i,j);
				IDX[i][j] = addedge(i+1,name[x][y],1,0);
			}
	for(int i = 0;i < N;i++)
		for(int j = i+1;j < N;j++)
			addedge(name[i][j],oname[i][j],1,0);

	for(int i = 0;i < N;i++)
		for(int j = 0;j < N;j++)
			if(i != j) {
				int x = min(i,j);
				int y = max(i,j);
				addedge(oname[x][y],lstname[j],1,0);
			}

	for(int i = 0;i < N;i++)
		addedge(lstname[i],snk,N-1-D[i],0);
}

char G[70][70];

void output(){
	int N = sz(D);
	for(int i = 0;i < N;i++){
		for(int j = 0;j < N;j++){
			if(i == j) G[i][j] = '0';
			else {
				int e = IDX[i][j];
				if(flow[e]) G[i][j] = '1';
				else G[i][j] = '0';
			}
		}
		puts(G[i]);
	}
	for(int i = 0;i < N;i++)
		for(int j = 0;j < N;j++)
			if(i != j)
				assert((G[i][j] == '1') ^ (G[j][i] == '1'));
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif

	cin >> n;
	loop(i,n) cin >> A[i];
	sort(A,A + n);
	memset(dp,-1,sizeof dp);
	int ans = solve(0,0,0,0);
	if(ans >= INF) {
		cout << "=" << endl;
		return 0;
	}
	printf("%d\n",ans);
	get_deg();
//	print(D,int);
	build_graph();
	int N = sz(D);
	assert(dinic_flow() == N*(N - 1)/2);
	output();
	return 0;
}
