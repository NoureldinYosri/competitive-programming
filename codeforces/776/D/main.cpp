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

const int MAX = 200'010;
int n,m;
int color[MAX];
vi key[MAX];
vi G[MAX];
int vis[MAX];

bool dfs(int u,int d){
	if(vis[u] != -1) return d == vis[u];
	vis[u] = d;
	for (int v : G[u]) if(!dfs(v,d^1)) return 0;
	return 1; 
}

void add_edge(int a,int b){
	G[a].pb(b);
	G[b].pb(a);
}

int main(){
	scanf("%d %d",&n,&m);
	memset(color,-1,sizeof color);
	loop(i,n) scanf("%d",color + i);
	loop(j,m){
		int i = j + n;
		int q; scanf("%d",&q);
		while(q--){
			int x; scanf("%d",&x); x--;
			key[x].pb(j);
		}
	}

	loop(i,n) {
		int x = key[i][0],y = key[i][1];
		if(color[i]) add_edge(x,y+m),add_edge(x+m,y);//,cerr << x << " like " << y << endl;
		else add_edge(x,y),add_edge(x+m,y+m);//,cerr << x << " dislike " << y << endl;
	}
	loop(i,m) add_edge(i,i+m);
	//loop(u,2*m) for(int v : G[u]) cerr << u << " " << v << endl; 	
	memset(vis,-1,sizeof vis);
	loop(i,2*m) if(vis[i] == -1 && !dfs(i,0)){
		puts("NO");
		return 0;
	}
	puts("YES");
	return 0;
}
