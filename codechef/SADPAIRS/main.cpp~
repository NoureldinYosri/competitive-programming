#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0,_ = (n);i < _;i++)
#define range(i,a,b) for(int i = (a),_ = (b);i <= _;i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b),_ = (a);i >= _;i--)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define vi vector<int>
#define vl vector<long>
#define vd vector<double>
#define ll long long
#define pi pair<int,int>
#define point pair<double,double>
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

const int MAX = 1 << 20;
const int UNVISITED = 0;
int dfsNumberCounter = 0,N,M,rootChildren,dfsRoot; 
int dfs_num[MAX],dfs_low[MAX],G[MAX];
int dfs_parent[MAX], articulation_vertex[MAX];
vi Adj[MAX],connected_component[MAX];
int which_connected_component[MAX],vis[MAX],CTR[MAX],Level[MAX];
int flat[MAX << 1];
ll ans = 0;

void articulationPointAndBridge(int u) {
	dfs_low[u] = dfs_num[u] = dfsNumberCounter++;
	for (auto v : Adj[u]) {
		if (dfs_num[v] == UNVISITED) {
			dfs_parent[v] = u;
			if (u == dfsRoot) rootChildren++;
			articulationPointAndBridge(v);
			if (dfs_low[v] >= dfs_num[u]) articulation_vertex[u] = 1;
			//if (dfs_low[v] > dfs_num[u]) printf(" Edge (%d, %d) is a bridge\n", u, v);
			dfs_low[u] = min(dfs_low[u], dfs_low[v]);
		}
		else if (v != dfs_parent[u]) dfs_low[u] = min(dfs_low[u], dfs_num[v]); // update dfs_low[u]
	}
}


void getArticulationPoints(){
	dfsNumberCounter = 0; 
	fill(dfs_num,dfs_num + N,0); 
	fill(dfs_low,dfs_low + N,0);
	fill(dfs_parent,dfs_parent + N,0); 
	fill(articulation_vertex,articulation_vertex + N,0);
	for (int i = 0; i < N; i++)
		if (dfs_num[i] == UNVISITED) {
			dfsRoot = i; 
			rootChildren = 0; 
			articulationPointAndBridge(i);
			articulation_vertex[dfsRoot] = (rootChildren > 1); 
		}
}

void process(vi & V){	
	sort(all(V));
	loop(i,sz(V)){
		int j = i;
		while(j < sz(V) && V[i] == V[j]) j++;
		ll tmp = j - i;
		ans += tmp*(CTR[V[i]] - tmp);
		i = j - 1;
	}
}

void bfs(int s,int conn_comp){
	queue<int> q;
	q.push(s); vis[s] = 1;
	while(!q.empty()){
		s = q.front(); q.pop();
		which_connected_component[s] = conn_comp;
		connected_component[conn_comp].pb(G[s]);
		for(int v : Adj[s]){
			if(vis[v]) continue;
			vis[v] = 1;
			q.push(v);
		}
	}
	process(connected_component[conn_comp]);
}

void get_raw(){
	int j = 0;
	loop(i,N) if(!vis[i]) bfs(i,j++);
	ans >>= 1;
}

void dfs(int u,int & idx){
	vis[u] = 1;
	if(articulation_vertex[u]){
		flat[idx++] = u;
		for(int v : Adj[u]) {
			if(vis[v]) continue;
			dfs(v);
			flat[idx++] = u;
		}	
	}
	else{
		flat[idx++] = u;
		for(int v : Adj[u]) if(!vis[v]) dfs(v);
	}
}

void buildAPT(){
	fill(vis,vis + N,0);
	int idx;
	loop(i,N){
		if(vis[i] || !articulation_vertex[i])  continue;
		idx = 0;
		dfs(i,idx);
	}
}

int main(){
	scanf("%d %d",&N,&M);
	loop(i,N) scanf("%d",G + i),CTR[G[i]]++;
	loop(i,M){
		int a,b;
		scanf("%d %d",&a,&b); --a,--b;
		Adj[a].pb(b);
		Adj[b].pb(a);
	}
	getArticulationPoints();
	get_raw();
	cerr << ans << endl;
	return 0;
}
