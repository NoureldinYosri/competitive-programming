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

const int MAX = 202;
vi G[MAX],rG[MAX];
int color[MAX],id[MAX];
int n,m;
vp Q[500];
int vis[MAX],ord[MAX],dfs_time;
vi say[MAX][2];

void clear(){
	loop(i,MAX) G[i].clear(),rG[i].clear(),say[i][0].clear(),say[i][1].clear();
	memset(color,-1,sizeof color);
}

int NOT(int x){
	if(x > n) return x - n;
	else return x + n;
}

void add_edge(int a,int b){
	G[a].pb(b);
	rG[b].pb(a);
}

void add_sat_edge(int x,int y){
	add_edge(NOT(x),y);
	add_edge(NOT(y),x);
}

void buildGraph(){
	loop(i,m){
		int k = Q[i].size();
		if(k <= 2) {
			for(auto p : Q[i]){
				int x = p.xx,v = p.yy;
				if(v) add_sat_edge(x,x);
				else add_sat_edge(NOT(x),NOT(x));
			}
		}
		else{
			loop(a,k) loop(b,a){
				int x = Q[i][a].xx,vx = Q[i][a].yy;
				int y = Q[i][b].xx,vy = Q[i][b].yy;
				if(!vx) x = NOT(x);
				if(!vy) y = NOT(y);
				add_sat_edge(x,y);
			}
		}
	}
}

void dfs(int u){
	vis[u] = 1;
	for(int v : G[u]) if(!vis[v]) dfs(v);
	ord[dfs_time++] = u;
}

void dfs(int u,int ID){
	id[u] = ID;
	vis[u] = 1;
	for(int v : G[u]) if(!vis[v]) dfs(v,ID);
}

bool sat(){
	dfs_time = 0;
	memset(vis,0,sizeof vis);
	range(i,1,2*n) if(!vis[i]) dfs(i);
	reverse(ord,ord + 2*n);
	memset(vis,0,sizeof vis);
	int ctr = 0;
	loop(i,2*n) if(!vis[ord[i]]) dfs(i,ctr++); 
	range(i,1,n) if(id[i] == id[i + n]) return 0;
	return 1;
}

void dfsTC(int x){
	vis[x] = 1;
	for(int per : say[x][!color[x]]){
		if(sz(Q[per]) <= 2) continue;
		for(auto p : Q[per]){
			if(p.xx == x) continue;
			int y = p.xx,v = p.yy;
			if(color[y] == -1){
				color[y] = v;
				dfsTC(y);
			}
			else assert(y == v);
		}
	}
}


int main(){
	for(int t = 1;scanf("%d %d",&n,&m) == 2 && !(n == 0 && m == 0);t++){
		cerr << "processing " << t << endl;
		clear();
		bool cond = 1;
		loop(i,m){
			int k; scanf("%d",&k);
			vp V;
			loop(j,k) {
				int x; char c; scanf("%d %c",&x,&c);
				V.pb(mp(x,c == 'y'));
				if(k > 2) say[x][c == 'y'].pb(i);
			}
			if(k <= 2){
				loop(j,k){
					int x = V[j].xx,v = V[j].yy;
					if(color[x] != -1 && color[x] != v) cond = 0;
					color[x] = v;
				}
			}
			Q[i] = V;	
		}
		printf("Case %d: ",t);
		if(!cond) puts("impossible");
		else {
			buildGraph();
			if(!sat()) puts("impossible");
			else {
				memset(vis,0,sizeof vis);
				range(i,1,n) if(!vis[i] && color[i] != -1) dfsTC(i); 				
				range(i,1,n) 
					if(color[i] == -1) putchar('?');
					else printf("%d\n",color[i]);
				puts("");
				cerr << t << " is valid" << endl;
			}
		}
	}	
	return 0;
}
