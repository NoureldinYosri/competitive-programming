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

const int MAX = 2010;
vi G[MAX*MAX];
char grid[MAX][MAX];
int m,n,deg[MAX*MAX],vis[MAX*MAX];

void add_edge(int a,int b){
	G[a].pb(b); deg[a]++;
	G[b].pb(a); deg[b]++;
}

void build(){
	loop(i,m) loop(j,n){
		if(grid[i][j] == '*') continue;
		if(i != m - 1 && grid[i+1][j] != '*') add_edge(i*n+j,i*n+j+n);
		if(j != n - 1 && grid[i][j + 1]!= '*') add_edge(i*n+j,i*n+j+1); 
	}
}

void assign(int u,int v){
	if(u > v) swap(u,v);
	vis[u] = vis[v] = 1;
	if(u/n == v/n) grid[u/n][u%n] = '<' ,grid[v/n][v%n] = '>';
	else grid[u/n][u%n] = '^' ,grid[v/n][v%n] = 'v';
}

int solve(){
	queue<int> q;
	loop(i,m) loop(j,n){
		if(grid[i][j] == '*') continue;
		if(!deg[i*n + j]) return 0;
		if(deg[i*n + j] == 1) q.push(i*n + j);
	}
	while(!q.empty()){
		int u = q.front(),v = -1; q.pop();
		if(vis[u]) continue;
		for(int t : G[u]) if(!vis[t]) v = t;
		assert(v != -1);
		assign(u,v);
		for(int t : G[v]) if(!vis[t]) {
			deg[t]--;
			if(deg[t] == 0) return 0;
			if(deg[t] == 1) q.push(t);
		}
	}
	loop(i,m) loop(j,n){
		if(grid[i][j] == '*') continue;
		if(!vis[i*n + j]) return 0;
	}
	return 1;	
}

int main(){
	scanf("%d %d",&m,&n);
	loop(i,m) scanf("%s",grid[i]);
	build();
	if(!solve()) puts("Not unique");
	else{
		loop(i,m) puts(grid[i]);//,cerr << grid[i] << endl;
	}		
	
	
	return 0;
}
