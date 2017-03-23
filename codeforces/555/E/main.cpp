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

const int MAX = 200'010,MAXLG = 20;
vi E[MAX],ver[MAX],G[MAX];
int fr[MAX],to[MAX];
int dfs_low[MAX],dfs_num[MAX],dfs_time;
vi V;
int id[MAX],m;
int S[MAX],T[MAX];
int ito[MAX],edge_cnt,eP[MAX];
int dfs_in[MAX],dfs_out[MAX],P[MAX][20],depth[MAX];

void extract(int u){
	++m;
	while(V.back() != u){
		id[V.back()] = m;
		ver[m].pb(V.back());
		V.pop_back();
	}
}

void dfs(int u,int p,int pe) {
	dfs_low[u] = dfs_num[u] = dfs_time++; 
	V.pb(u);
	for(int e : G[u]){	
		int v = fr[e] + to[e] - u;
		if (dfs_num[v] == -1) {
			dfs(v,u,e);
			if (dfs_low[v] > dfs_num[u]) extract(u);
			dfs_low[u] = min(dfs_low[u], dfs_low[v]); 
		} 
		else if (v != p)
			dfs_low[u] = min(dfs_low[u], dfs_num[v]);
		else if (e != pe)
			dfs_low[u] = min(dfs_low[u], dfs_num[v]);
	}
}

void dfs(int u,int p){
	dfs_in[u] = dfs_time++;
	P[u][0] = p;
	depth[u] = p ? (depth[p] + 1) : 0;
	loop(i,19) P[u][i + 1] = P[P[u][i]][i];
	for(int v : G[u]) if(v != p) {
		eP[v] = edge_cnt;
		to[edge_cnt] = v;
		edge_cnt++;
		dfs(v,u);
	}		
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


int main(){
	int n,m,q; scanf("%d %d %d",&n,&m,&q);
	loop(i,m){
		int a,b; scanf("%d %d",&a,&b);
		E[a].pb(i);
		E[b].pb(i);
		fr[i] = a,to[i] = b;
	}
	memset(dfs_num,-1,sizeof dfs_num);	
	int src = 1;
	loop(i,q){
		scanf("%d %d",S + i,T + i);
		src = S[i];
	}
	memset(id,-1,sizeof id);
	V.pb(0);	
	dfs(src,0,-1);
	extract(0);
	loop(i,q){
		if(dfs_num[S[i]] == -1 || dfs_num[T[i]] == -1){
			puts("NO");
			return 0;
		}
	}
	int cnt = 0;
	range(i,1,m) {
		for(int v : ver[i]) if(id[v] != -1 && id[v] != i) G[i].pb(id[v]);
		sort(all(G[i]));
		G[i].resize(unique(all(G[i])) - G[i].begin());
		cnt += G[i].size();
	}
	assert(cnt == 2*m-2);
	dfs_time = 0;
	dfs(1,0);
	// it remains to find a way to efficiently propagate info about edges
	return 0;
}
