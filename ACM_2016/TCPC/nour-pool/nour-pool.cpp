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

vi adj[1024];
int N,M,G,C,S;
int dist[1024];
int vis[1024],when[1024];
int gather[1024],cnt[1024];
vector<pi > V;
vi buses;
vector<vi> who;

void bfs(){
	fill(vis,vis + N + 1,0);
	vis[S] = 1;
	dist[S] = 0;
	queue<int> q; q.push(S);
	while(!q.empty()){
		int u = q.front(); q.pop();
		for(int v : adj[u]){
			if(vis[v]) continue;
			vis[v] = 1;
			dist[v] = dist[u] + 1;
			q.push(v);
		}
	}
}


int main(){
	int T,a,b;
	scanf("%d",&T);
	while(T--){
		scanf("%d %d %d %d %d",&N,&M,&G,&C,&S);
		loop(i,N) adj[i + 1].clear(),when[i] = -2;
		V.clear(); buses.clear(); who.clear();
		loop(i,M){
			scanf("%d %d",&a,&b);
			adj[a].pb(b);
			adj[b].pb(a);
		}	
		bfs();
		loop(i,G) scanf("%d",gather + i);
		loop(i,G) scanf("%d",cnt + i);	
		loop(i,G) {
			int d = vis[gather[i]] ? dist[gather[i]] : -1;		
			V.pb(mp(d,i));
		}
		sort(all(V));
		for(auto v : V){
			if(!vis[gather[v.yy]] || cnt[v.yy] > C){
				when[v.yy] = -1;
				continue;
			}
			bool c = 1;			
			loop(i,sz(buses)) {
				if(buses[i] + cnt[v.yy] <= C){
					buses[i] += cnt[v.yy];
					who[i].pb(v.yy);
					c = 0;
					if(buses[i] == C){
						for(auto u : who[i])
							when[u] = v.xx;	
					}
				} 
			}
			if(c){
				int i = sz(buses);
				buses.pb(0); who.pb(vi());
				buses[i] += cnt[v.yy];
				who[i].pb(v.yy);
				c = 0;
				if(buses[i] == C){
					for(auto u : who[i])
						when[u] = v.xx;	
				}
			}
		}
		loop(i,sz(buses)){
			if(buses[i] == C) continue;
			for(int q : who[i]){
				when[q] = vis[gather[V.back().yy]] ? V.back().xx : -1;
			}
		}
		loop(i,G) printf("%d%s",when[i],(i == G - 1) ? "\n" : " ");
	}
	return 0;
}
