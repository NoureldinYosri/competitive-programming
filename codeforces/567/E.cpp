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

using edge = pair<ll,int>;
const ll oo = 1LL << 60;
const int MAX = 100*1000 + 10;
int fr[MAX],to[MAX],W[MAX],n,m;
ll dist[2][MAX];
vi IG[MAX],revIG[MAX],E[MAX];


void dijkstra(int src,ll *dist,vi *G) {
	static priority_queue<edge,vector<edge>,greater<edge> > pq;
	fill(dist+1,dist + n + 1,oo);
	pq.push(mp(0,src));
	dist[src] = 0;
	while(!pq.empty()){
		ll d = pq.top().first;
		int u = pq.top().second;
		pq.pop();
		if(d != dist[u]) continue;
		for(int e : G[u]) {
			int v = fr[e] + to[e] - u;
			if(dist[u] + W[e] < dist[v]) {
				dist[v] = dist[u] + W[e];
				pq.push(mp(dist[v],v));
			}
		}
	}
}


int dfs_low[MAX],dfs_num[MAX],dfs_time;
bool isBridge[MAX];

void dfsBi(int u,int ie,int dfs_root) {
	dfs_low[u] = dfs_num[u] = dfs_time++;
	int t = 0;
	for(int e : E[u]){
		int v = fr[e] + to[e] - u;
		if (dfs_num[v] == -1) {
			if (u == dfs_root) t++;
			dfsBi(v,e,dfs_root);
			if (dfs_low[v] > dfs_num[u])
				isBridge[e] = 1;
			dfs_low[u] = min(dfs_low[u], dfs_low[v]);
		}
		else if (e != ie)
			dfs_low[u] = min(dfs_low[u], dfs_num[v]);
	}
}

void init(){
	memset(dfs_num,-1,sizeof dfs_num);
	dfs_time = 0;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int s,t; scanf("%d %d %d %d",&n,&m,&s,&t);
	loop(e,m) {
		scanf("%d %d %d",fr + e,to + e,W + e);
		IG[fr[e]].push_back(e);
		revIG[to[e]].push_back(e);
	}
	dijkstra(s,dist[0],IG);
	dijkstra(t,dist[1],revIG);
	ll D = dist[0][t];
	loop(e,m){
		int a = fr[e],b = to[e];
		if(dist[0][a] + W[e] + dist[1][b] == D){
			E[a].push_back(e);
			E[b].push_back(e);
		}
	}
	init();
	dfsBi(s,-1,s);
	loop(e,m){
		ll a = dist[0][fr[e]],b = dist[1][to[e]];
		if(isBridge[e]) puts("YES");
		else {
			ll w = D - 1 - a - b;
			if(w > 0) printf("CAN %lld\n",W[e] - w);
			else puts("NO");
		}
	}

	return 0;
}
