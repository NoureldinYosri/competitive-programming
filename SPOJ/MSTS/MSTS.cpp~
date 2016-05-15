#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define vi vector<int>
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
#define pre() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

const int MAX = 1000*2;
int n,m;
int idx[MAX],E[MAX][3],P[MAX],W[MAX];
int mod1 = 3,mod2 = 10337;
vi G[MAX];

bool cmp(const int & a,const int & b)  { return E[a][2] < E[a][2];}
int get(int a){ return P[a] = (P[a] == a) ? a : get(P[a]); }
inline bool connected(int a,int b) {return get(a) == get(b);}
void join(int a,int b){ a = get(a),b = get(b); if(W[a] < W[b]) swap(a,b); W[a] += W[b]; P[b] = a;}
void bfs(int ,vi & ,vi & ,vi & );



void f(int s,int e,int & x,int & y){
	x = y = 1;
	for(int i = s;i <= e;i++){
		int a = get(E[idx[i]][0]),b = get(E[idx[i]][1]); ++i;		
		if(a == b) continue;	
		G[a].clear(); G[b].clear();
	}
	vi vertex,vis,subgraph;
	for(int i = s;i <= e;i++){
		int a = get(E[idx[i]][0]),b = get(E[idx[i]][1]); ++i;		
		if(a == b) continue;	
		G[a].pb(b);   G[b].pb(a);
		vertex.pb(a); vertex.pb(b);
	}
	sort(all(vertex)); vertex.resize(unique(all(vertex)) - vertex.begin());
	vis.resize(sz(vertex),0);
	for(int i = 0;i < sz(vertex);i++)
		if(vis[i] == 0){
			subgraph.clear();
			bfs(vertex[i],vertex,vis,subgraph);	
			
		}
}

int main(){
	scanf("%d %d",&n,&m);
	loop(i,n + 1) P[i] = i,W[i] = 1;
	loop(i,m) loop(j,3) scanf("%d",&E[i][j]),idx[i] = i;
	sort(idx,idx + m,&cmp);
	int ans1 = 1,ans2 = 1,x,y;	
	loop(i,m){
		int j = i;
		while(j < m && E[idx[i]][2] == E[idx[j]][2]) j++;
		f(i,j,x,y);		
		ans1 = (ans1 * x)%3;
		ans2 = (ans2 * y)%10337;
	}
	int ans = (ans1 * 2 + ans2 * 3446)%(3*10337);
	printf("%d\n",ans);
	cerr << ans << endl;
	return 0;
}


void bfs(int s,vi & vertex,vi & vis,vi & subgraph){
	queue<int> q; q.push(s); 
	vis[lower_bound(all(vertex),s) - vertex.begin()] = 1;
	subgraph.pb(s);
	while(!q.empty()){
		s = q.front(); q.pop(); 
		for(int v : G[s]){
			int u = lower_bound(all(vertex),v) - vertex.begin();
			if(!vis[u]){
				q.push(v); subgraph.pb(v);
				vis[u] = 1;
			}
		}
	}
}
