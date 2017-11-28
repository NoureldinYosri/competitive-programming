#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define popcnt(x) __builtin_popcountll(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
using namespace std;

const int MAX = 1024;
const ll oo = 1LL << 60;
vi E[MAX];
int fr[MAX],to[MAX],cost[MAX];
ll dist[MAX][MAX];
int n,m,s,e;
typedef pair<ll,int> tip;
int T[MAX],C[MAX];

void dijkstra(int src){
	fill(dist[src],dist[src] + n + 1,oo);
	PQ<tip,vector<tip>,greater<tip> > pq;
	pq.push(mp(0,src));
	dist[src][src] = 0;
	while(!pq.empty()){
		int u = pq.top().yy;
		ll d = pq.top().xx;
		pq.pop();
		if(d != dist[src][u]) continue;
		for(int e : E[u]) {
			int v = fr[e] + to[e] - u;
			if(d + cost[e] < dist[src][v]){
				dist[src][v] = d + cost[e];
				pq.push(mp(dist[src][v],v));
			}
		}
	}
}

ll ans[MAX];
int vis[MAX];

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d",&n,&m);
	scanf("%d %d",&s,&e);
	loop(ed,m){
		scanf("%d %d %d",fr + ed,to + ed,cost + ed);
		E[fr[ed]].pb(ed);
		E[to[ed]].pb(ed);
	}
	range(i,1,n) scanf("%d %d",T + i,C + i);
	range(i,1,n) dijkstra(i);
	fill(ans,ans + MAX,oo);
	ans[s] = 0;
	for(int done = 0;done < n;done++) {
		int u = 1; ll d = oo;
		for(int i = 1;i <= n;i++)
			if(!vis[i] && ans[i] < d){
				d = ans[i];
				u = i;
			}
		vis[u] = 1;
		for(int v = 1;v <= n;v++)
			if(dist[u][v] <= T[u] && ans[u] + C[u] < ans[v])
				ans[v] = ans[u] + C[u];
	}
	if(ans[e] >= oo) ans[e] = -1;
	cout << ans[e] << endl;
	return 0;
}
