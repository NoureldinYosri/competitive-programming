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

const int MAX = 1 << 10,oo = 1e8;
vp G[MAX];
int n,m,k;
int dist[MAX][MAX];
int items[MAX];
int vis[MAX],dp[MAX];

void dijkstra(int src){
	loop(i,n) loop(j,1<<k) dist[i][j] = oo;
	typedef pair<int,pi> state;
	PQ<state,vector<state>,greater<state> > pq;
	pq.push(mp(0,mp(src,items[src]))); dist[src][items[src]] = 0;
	while(!pq.empty()){
		int u = pq.top().yy.xx,d = pq.top().xx,item = pq.top().yy.yy; pq.pop();
		if(dist[u][item] > d) continue;
		for(auto e : G[u]){
			int nd = e.xx + d,v = e.yy;
			if(nd < dist[v][item | items[v]]){
				dist[v][item | items[v]] = nd;
				pq.push(mp(nd,mp(v,item | items[v])));
			}
		}
	}
}

int solve(int msk){
	if(vis[msk]) return dp[msk];
	vis[msk] = 1;
	dp[msk] = dist[n-1][msk];
	for(int omsk = ((1 << k) - 1)^msk;omsk;omsk ^= LSOne(omsk))
		dp[msk] = min(dp[msk],solve(msk | LSOne(omsk)));
	return dp[msk];
}

int main(){
	scanf("%d %d %d",&n,&m,&k);
	loop(i,n){
		int cnt,x; scanf("%d",&cnt);
		while(cnt--){
			int x; scanf("%d",&x); x--;
			items[i] |= 1 << x;
		}
	}	
	loop(i,m){
		int a,b,c; scanf("%d %d %d",&a,&b,&c);	
		--a,--b;
		G[a].pb(mp(c,b));
		G[b].pb(mp(c,a));
	}
	dijkstra(0);
	int ans = oo;
	loop(msk,1 << k) ans = min(ans,max(solve(msk),solve(((1 << k)-1)^msk)));		
	cerr << ans << endl;
	cout << ans << endl;
	return 0;
}
