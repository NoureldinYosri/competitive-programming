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

const int MAX = 2e5 + 1e2;
const ll oo = 1LL << 60;
vector<pl> G[MAX];
vi nG[MAX],rnG[MAX],aux[MAX],tree[MAX];
ll dist[MAX];
int n;
int id[MAX],dfs_time,rev[MAX];
int sdom[MAX],dom[MAX];
int dsu[MAX],label[MAX],par[MAX],W[MAX];

void dijkstra(int src){
	fill(dist,dist + MAX,oo);
	PQ<pl,vector<pl>,greater<pl> > pq;
	dist[src] = 0; pq.push(mp(0,src));
	while(!pq.empty()){
		int u = pq.top().yy;
		ll d = pq.top().xx; pq.pop();
		if(d > dist[u]) continue;
		for(auto e : G[u]){
			e.xx += d;
			if(e.xx < dist[e.yy]) {
				dist[e.yy] = e.xx;			
				pq.push(e);
			}
		}
	}
	range(u,1,n) if(dist[u] < oo) {
		for(auto e : G[u]){
			if(dist[e.yy] == dist[u] + e.xx){
				nG[u].pb(e.yy);
			}
		}
	}
}

int get(int u,int x=0){
	if(u == dsu[u]) return x ? -1 : u;
	int v = get(dsu[u],x+1);
	if(v < 0) return u;
	if(sdom[label[dsu[u]]]<sdom[label[u]])
		label[u] = label[dsu[u]];
	dsu[u] = v;
	return x?v:label[u];
}

void join(int a,int b){
	dsu[b] = a;
}

void dfs(int u){
	id[u] = ++dfs_time; rev[dfs_time] = u;
	label[dfs_time] = sdom[dfs_time] = dom[dfs_time] = dfs_time;
	W[dfs_time] = 1;	
	for(int v : nG[u]) {
		if(!id[v]) {
			dfs(v);
			par[id[v]] = id[u];
		}
		rnG[id[v]].pb(id[u]);
	}
}

void build_DT(int src){
	dfs(src);
	n = dfs_time;
	for(int i = n;i;i--){
		for(int v : rnG[i])
			sdom[i] = min(sdom[i],sdom[get(v)]);
		if(i > 1) aux[sdom[i]].pb(i);
		for(int w : aux[i]){
			int v = get(w);
			if(sdom[v] == sdom[w]) dom[w] = sdom[w];
			else dom[w] = v;
		}
		if(i > 1) join(par[i],i);
	}
	for(int i = 2;i <= n;i++){
		if(dom[i] != sdom[i]) dom[i] = dom[dom[i]];
		tree[dom[i]].pb(i);
	}	
}

int dfs(int u,int & ans){
	int tmp = 1;
	for(int v : tree[u]) tmp += dfs(v,ans);
	if(u != 1) ans = max(ans,tmp);
	return tmp;
}

int main(){
	int m,src; scanf("%d %d %d",&n,&m,&src);
	loop(i,m){
		int a,b,c; scanf("%d %d %d",&a,&b,&c);
		G[a].pb(mp(c+0LL,b+0LL));
		G[b].pb(mp(c+0LL,a+0LL));
	}
	dijkstra(src);
	build_DT(src);
	int ans = 0;
	dfs(1,ans);
	cout << ans << endl;
	cerr << ans << endl;

	return 0;
}
