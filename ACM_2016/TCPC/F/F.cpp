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
vi buses,bw;
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


void assign(int t,int idx){
	if(t < 0 || cnt[idx] > C) {
		when[idx] = -1;
		return;
	}
	loop(i,sz(buses)){
		if(buses[i] + cnt[idx] <= C){
			buses[i] += cnt[idx];
			who[i].pb(idx);
			bw[i] = t;
			return;
		}
	}
	buses.pb(cnt[idx]);
	who.pb(vi(1,idx));
	bw.pb(t);
}

void check(){
	loop(i,sz(buses)){
		int e = bw[i];
		if(buses[i] != C) e = V.back().xx; 
		for(int w : who[i]){
			when[w] = e - dist[gather[w]];
		}
	}
}

int main(){
	freopen("finding.in","r",stdin);
	int T,a,b;
	scanf("%d",&T);
	while(T--){
		scanf("%d %d %d %d %d",&N,&M,&G,&C,&S);
		loop(i,N) adj[i + 1].clear(),when[i + 1] = -2;
		V.clear(); buses.clear(); who.clear(); bw.clear();
		loop(i,M){
			scanf("%d %d",&a,&b);
			adj[a].pb(b);
			adj[b].pb(a);
		}	
		bfs();
		loop(i,G) scanf("%d",gather + i);
		loop(i,G) scanf("%d",cnt + i);	
		loop(i,G) {
			if(vis[gather[i]]) V.pb(mp(dist[gather[i]],i));
			else when[i] = -1;
		}
		sort(all(V));
		for(auto v : V) assign(v.xx,v.yy);
		check();
		loop(i,G) printf("%d%s",when[i],(i == G - 1) ? "\n" : " ");
	}
	return 0;
}