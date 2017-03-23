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

const int MAX = 5 << 10,oo = 1 << 29;
const ll INF = 1LL << 60;
int to[MAX],from[MAX],n,b,s,r;
vp G[MAX],rG[MAX];
ll cost[MAX],dp[MAX][MAX];
ll sum[MAX];

void dijkstra(int src,int *dist,vp *G){
	fill(dist + 1,dist + n + 1,oo);
	PQ<pi,vp,greater<pi> > pq;
	pq.push(mp(0,src)); dist[src] = 0;
	while(!pq.empty()){
		int u = pq.top().yy,d = pq.top().xx; pq.pop();
		if(d > dist[u]) continue;
		for(auto e : G[u]){
			e.xx += d;
			if(e.xx < dist[e.yy]){
				pq.push(e);
				dist[e.yy] = e.xx;
			}
		}
	}
}

ll solve(int pos,int s){
	if(pos == 0) return (s == 0) ? 0 : INF;
	if(s == 0) return INF;
	if(dp[pos][s] != -1) return dp[pos][s];
	ll & ret = dp[pos][s]; ret = INF;
	for(int k = 1;k <= pos/s;k++){
		ret = min(ret,solve(pos - k,s - 1) + (sum[pos] - sum[pos - k])*(k - 1));
	}
	return ret;
}

int main(){
	scanf("%d %d %d %d",&n,&b,&s,&r);
	loop(i,r){
		int a,b,c; scanf("%d %d %d",&a,&b,&c);
		G[a].pb(mp(c,b));
		rG[b].pb(mp(c,a));
	}
	dijkstra(b+1,from,G);
	dijkstra(b+1,to,rG);
	loop(i,b) cost[i + 1] = from[i + 1] + to[i + 1];	
	sort(cost + 1,cost + b + 1);
	range(i,1,b) sum[i] = cost[i] + sum[i - 1];	
	memset(dp,-1,sizeof dp);	
	cerr << solve(b,s) << endl;
	cout << solve(b,s) << endl;
	return 0;
}
