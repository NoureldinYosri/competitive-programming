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

const int MAX = 400010,MAXLG = 20;
vi E[MAX],ver[MAX],G[MAX];
int fr[MAX],to[MAX];
int dfs_low[MAX],dfs_num[MAX],dfs_time;
vi V;
int id[MAX],m;
int S[MAX],T[MAX];
int ito[MAX],edge_cnt,eP[MAX];
int dfs_in[MAX],dfs_out[MAX],P[MAX][20],depth[MAX];

int ID[MAX],id_count;

vi ST;

void extract(int u) {
	int v = 0;
	++id_count;
	while(v != u) {
		v = ST.back();
		ST.pop_back();
		ID[v] = id_count;
	}
}

void dfsBi(int u,int p,int pe,int component) {
	dfs_low[u] = dfs_num[u] = dfs_time++;
	id[u] = component;
	ST.push_back(u);
	for(int e : E[u]){
		int v = fr[e] + to[e] - u;
		if (dfs_num[v] == -1) {
			dfsBi(v,u,e,component);
//			if (u != dfs_root && dfs_low[v] >= dfs_num[u])
//				articulation_vertex[u] = 1;
			if (dfs_low[v] > dfs_num[u]){
				extract(v);
			}
			dfs_low[u] = min(dfs_low[u], dfs_low[v]);
		}
		else if (v != p)
			dfs_low[u] = min(dfs_low[u], dfs_num[v]);
		else if(e != pe)
			dfs_low[u] = min(dfs_low[u], dfs_num[v]);
	}
//	if(u == dfs_root && t > 1) articulation_vertex[u] = 1;
	if(pe == -1) extract(u);
}

void init(){
	memset(dfs_num,-1,sizeof dfs_num);
	dfs_time = 0;
}

void dfs(int u,int p){
	dfs_in[u] = dfs_time++;
	P[u][0] = p;
	depth[u] = p ? (depth[p] + 1) : 0;
	loop(i,19) P[u][i + 1] = P[P[u][i]][i];
	for(int v : G[u]) if(v != p) dfs(v,u);
	dfs_out[u] = dfs_time - 1;
}

bool inSubTree(int a,int b){
	return dfs_in[b] <= dfs_in[a] && dfs_in[a] <= dfs_out[b];
}

int lca(int a,int b){
	if(depth[a] > depth[b]) swap(a,b);
	if(inSubTree(b,a)) return a;
	int k = MAXLG - 1;
	while(a != b){
		if(depth[a] > depth[b]) swap(a,b);		
		while(k && inSubTree(a,P[b][k])) k--;
		b = P[b][k];
	}
	return a;
}

int up[MAX],down[MAX];
int term[MAX];
bool cond = 0;
bool vis[MAX];

pi dfs_count(int u,int p) {
	int up = ::up[u],down = ::down[u];
	vis[u] = 1;
	for(int v : G[u]) {
		if(v == p) continue;
		pi tmp = dfs_count(v,u);
		up += tmp.xx;
		down += tmp.yy;
	}
	up -= term[u];
	down -= term[u];
	assert(up >= 0);
	assert(down >= 0);
	if(up && down) {
		if(p != 0) cond = 1;
	}
	if(p == 0) assert(up == 0 && down == 0);
	return mp(up,down);
}

char out[2][10] = {"No","Yes"};

int main(){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	int n,m,q; scanf("%d %d %d",&n,&m,&q);
	loop(i,m){
		int a,b; scanf("%d %d",&a,&b);
		E[a].pb(i);
		E[b].pb(i);
		fr[i] = a,to[i] = b;
	}
	loop(i,q){
		scanf("%d %d",S + i,T + i);
	}
	init();
	for(int u = 1;u <= n;u++)
		if(dfs_num[u] == -1)
			dfsBi(u,0,-1,++m);
	loop(i,q) {
		int a = S[i],b = T[i];
		if(id[a] != id[b]){
			puts(out[0]);
			return 0;
		}
	}
	m = id_count;
	for(int u = 1;u <= n;u++) {
		for(int e : E[u]) {
			int v = fr[e] + to[e] - u;
			if(ID[u] == ID[v]) continue;
			G[ID[u]].push_back(ID[v]);
		}
	}
	range(i,1,m) {
		sort(all(G[i]));
		G[i].resize(unique(all(G[i])) - G[i].begin());
	}
	dfs_time = 0;
	memset(dfs_in,-1,sizeof dfs_in);
	for(int u = 1;u <= m;u++)
		if(dfs_in[u] == -1)
			dfs(u,0);
	dfs_out[0] = m-1;
	// it remains to find a way to efficiently propagate info about edges
	loop(i,q) {
		int a = S[i],b = T[i];
		a = ID[a],b = ID[b];
		if(a == b) continue;
		up[a]++;
		down[b]++;
		term[lca(a,b)] ++;
	}
	for(int u = 1;u <= m;u++)
		if(!vis[u])
			dfs_count(u,0);
	puts(cond ? out[0] : out[1]);
	return 0;
}
