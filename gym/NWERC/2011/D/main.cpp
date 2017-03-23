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

const int MAX = 500*500*4;
char G[500][501];
vi adj[MAX],radj[MAX];
int m,n,N;
int dx [] = {0,1,0,-1},dy [] = {1,0,-1,0};
int vis[MAX],ord[MAX],dfs_time;
int id[MAX];

int NOT(int a){
	if(a >= m*n*2) return a - m*n*2;
	else return a + 2*m*n;
}

int name(int x,int y){
	return x*n + y;
}

void add_edge(int a,int b){
	adj[NOT(b)].pb(a);
	adj[NOT(a)].pb(b);
}

bool build_graph(){
	loop(i,m*n*4) adj[i].clear();
	int cnt[2] = {0};
	loop(i,m) loop(j,n) {
		if(G[i][j] == '.') continue;
		cnt[G[i][j] == 'W']++;
		if(G[i][j] == 'W'){
			vi E;
			loop(k,4){
				int nx = i + dx[k],ny = j + dy[k];
				if(nx < 0 || nx >= m || ny < 0 || ny >= n) continue;
				if(G[nx][ny] == 'W') continue;
				if(G[nx][ny] == '.') continue;
				if(k < 2) E.pb(2*name(i,j) + k); 
				else E.pb(2*name(nx,ny) + k - 2);
			}
			loop(i,sz(E)) loop(j,i) {
				int x = E[i],y = E[j];
				add_edge(NOT(x),NOT(y));
			}
		}
		else{
			vi E[2];
			loop(k,4){
				int nx = i + dx[k],ny = j + dy[k];
				if(nx < 0 || nx >= m || ny < 0 || ny >= n) continue;
				if(G[nx][ny] == 'B') continue;
				if(G[nx][ny] == '.') continue;
				if(k < 2) E[k & 1].pb(2*name(i,j) + k);
				else E[k & 1].pb(2*name(nx,ny) + k - 2); 
			}
			loop(k,2) {
				if(E[k].empty()) return 0;
				if(E[k].size() == 1) {
					add_edge(E[k][0],E[k][0]);
					continue;
				}
				int x = E[k][0],y = E[k][1];
				add_edge(x,y);
				add_edge(NOT(x),NOT(y));
			}
		}
	}
//	cerr << dfs_time << " " << 4*n*m << endl;
	loop(i,m*n*4) radj[i].clear();
	loop(u,m*n*4) for(int v : adj[u]) radj[v].pb(u);
	//loop(u,m*n*4) for(int v : adj[u]) cerr << u << " " << v << endl;
	//cerr << "done" << endl;
	return 2*cnt[0] == cnt[1];
}

void dfs(int u){
	vis[u] = 1;
	for(int v : adj[u]) if(!vis[v]) dfs(v);
	ord[dfs_time++] = u;
}

bool dfs(int u,int q){
	id[u] = q;
	vis[u] = 1;
//	if(id[NOT(u)] == id[u]) cerr << u << " " << NOT(u) << " " << q << endl;
	if(id[NOT(u)] == id[u]) return 0;
	for(int v : radj[u]) if(!vis[v]) if(!dfs(v,q)) return 0;
	return 1;
}

bool solve(){
	memset(vis,0,sizeof vis);
	dfs_time = 0;
	loop(i,m*n*4) if(!vis[i]) dfs(i);

	reverse(ord,ord + dfs_time);	
	memset(id,-1,sizeof id);
	int cnt = 0;
	memset(vis,0,sizeof vis);
	loop(j,m*n*4) {
		int i = ord[j];	
		if(!vis[i]) if(!dfs(i,cnt++)) return 0;
	}
	return 1;
}

int main(){
	int T; scanf("%d",&T);
	while(T--){
		scanf("%d %d",&m,&n);
		loop(i,m) scanf("%s",G[i]);	
		if(build_graph()) puts(solve() ? "YES" : "NO"); 
		else puts("NO");
	}	
	return 0;
}
