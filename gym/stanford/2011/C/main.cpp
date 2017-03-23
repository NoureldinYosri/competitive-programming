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

const int MAX = 100'010;
int n;
vp G[MAX];
int dfs_in[MAX],dfs_low[MAX],dfs_time;
int to[MAX],dist[3][MAX];
int in_cycle[MAX];

void dfs(int u,int p){
	dfs_in[u] = dfs_low[u] = dfs_time++;
	int mn = INT_MAX;
	for(auto e : G[u]) if(e.yy != p){
		int v = e.yy;
		if(dfs_in[v] != -1) dfs_low[u] = min(dfs_low[u],dfs_in[v]);
		else {
			dfs(v,u);
			dfs_low[u] = min(dfs_low[u],dfs_low[v]);
			if(dfs_low[v] <= dfs_in[u]) in_cycle[u] = 1;
		}
	}
	if(dfs_low[u] < dfs_in[u]) in_cycle[u] = 1;
}

void dfs(int u,int p,int *D){
	if(in_cycle[u]){
		loop(i,n) if(in_cycle[i]) {
			D[i] = D[u];
			for(auto e : G[i]){
				int v = e.yy;
				if(in_cycle[v] || v == p) continue;
				D[v] = D[u] + e.xx;
				to[v] = i;
			//	cerr << "type 0 ,set to " << v << " to " << to[v] << endl;
				dfs(v,i,D);
			}
		}
	}
	else{
		for(auto e : G[u]){
			int v = e.yy;
			if(v == p) continue;
			if(to[u] != u) {
				to[v] = to[u];
			//	cerr << "type 1 ,set to " << v << " to " << to[v] << endl;
			}
			D[v] = D[u] + e.xx;
			dfs(v,u,D);
			if(to[u] == u) {
				to[u] = to[v];
			//	cerr << "type 2 ,set to " << v << " to " << to[v] << endl;
			}
		}
	}
}

void dfs(int u,int p,int *D,int root){
	for(auto e : G[u]) if(e.yy != p && in_cycle[e.yy] && e.yy != root){
		D[e.yy] = D[u] + e.xx;
		dfs(e.yy,u,D,root);
	}
}

void preprocess(){
	loop(i,n) to[i] = i;
	dfs_time = 0;
	fill(dfs_in,dfs_in + n,-1);
	fill(in_cycle,in_cycle + n,0);
	dfs(0,-1);
	int root = -1,cycle_root = -1;
	loop(i,n) {
		if(!in_cycle[i] && sz(G[i]) == 1) root = i;
		if(in_cycle[i]) cycle_root = i;
	}
	assert(cycle_root != -1);
	loop(i,3) fill(dist[i],dist[i] + n,0);
	if(root != -1) dfs(root,-1,dist[0]);
	int ctr = 1;
	for(auto e : G[cycle_root]) if(in_cycle[e.yy]) {
		assert(ctr < 3);		
		dist[ctr][e.yy] = e.xx;
		dfs(e.yy,cycle_root,dist[ctr],cycle_root);
		ctr++;
	}
}



int main(){
	while(scanf("%d",&n) == 1 && n){
		loop(i,n) G[i].clear();
		loop(i,n){
			int a,b,c; scanf("%d %d %d",&a,&b,&c);
			G[a].pb(mp(c,b));
			G[b].pb(mp(c,a));
		}
		preprocess();
		int m; scanf("%d",&m);
		loop(i,m){
			int x,y; scanf("%d %d",&x,&y);
			int ans = 0;
			if(to[x] == to[y]) ans = abs(dist[0][x] - dist[0][y]);
			else{
				ans  = abs(dist[0][x] - dist[0][to[x]]);
				ans += abs(dist[0][y] - dist[0][to[y]]);
				x = to[x],y = to[y];
				int d1 = abs(dist[1][x] - dist[1][y]),d2 = abs(dist[2][x] - dist[2][y]);
				int d3 = dist[1][x] + dist[2][y],d4 = dist[1][y] + dist[2][x];
				ans += min(min(d1,d2),min(d3,d4));
			}
//			cerr << ans << endl;
			printf("%d\n",ans);
		}
	}	
	return 0;
}
