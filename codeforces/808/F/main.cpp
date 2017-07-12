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

int n,target;
int power[100],magic[100],L[100];
map<int,int> memo;
bool isPrime(int v){
	if(v <= 1) return 0;
	if(v <= 3) return 1;
	if(v%2 == 0 || v%3 == 0) return 0;
	if(memo.find(v) != memo.end()) return memo[v];
	for(int i = 2;i*i <= v;i++)
		if(v%i == 0)
			return memo[v] = 0;
	return memo[v] = (v > 1);
}

int solve(int lev){
	vi even,odd;
	int c = -1;
	int ret = 0;
	loop(i,n)
		if(L[i] <= lev){
			if(magic[i] == 1) {
				if(c == -1 || power[i] > power[c]) c = i;
				continue;
			}
			if(magic[i] & 1) odd.pb(i);
			else even.pb(i);
			ret += power[i];
		}
	if(c != -1) odd.pb(c),ret += power[c];

	int src = 0,snk = n + 1;
	init(n + 2,src,snk);
	for(int x : even) addedge(src,x + 1,power[x],0);
	for(int x : even)
		for(int y : odd)
			if(isPrime(magic[x] + magic[y]))
				addedge(x+1,y+1,oo,0);
	for(int x : odd) addedge(x+1,snk,power[x],0);
	return ret - dinic_flow();
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d",&n,&target);
	loop(i,n) scanf("%d %d %d",power + i,magic + i,L + i);
	int s = 1,e = 1;
	loop(i,n) e = max(e,L[i]);

	while(s < e){
		int m = (s + e) >> 1;
		if(solve(m) >= target) e = m;
		else s = m + 1;
	}
	if(solve(s) < target) s = -1;
	cout << s << endl;
	return 0;
}
