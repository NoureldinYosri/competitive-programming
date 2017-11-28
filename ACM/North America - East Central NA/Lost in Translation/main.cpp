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

const int MAX = 111,MAXE = 4500;
vi E[MAX];
string name[MAX],a,b;
map<string,int> M;
int n,m;
int fr[MAXE],to[MAXE],cost[MAXE];
int usable[MAXE],dist[MAXE];
int level[MAX];



int dijkstra(){
	PQ<pi,vector<pi>,greater<pi> > pq;
	pq.push(mp(0,0));
	fill(dist,dist + n + 1,1 << 29);
	memset(level,-1,sizeof level);
	dist[0] = 0;
	level[0] = 0;
	int ret = 0;
	while(!pq.empty()){
		int u = pq.top().yy;
		int d = pq.top().xx;
		pq.pop();
		if(d != dist[u]) continue;
		ret += dist[u];
		for(int e : E[u]){
			int v = fr[e] + to[e] - u;
			if(level[v] == -1 || level[v] == level[u] + 1){
				if(cost[e] < dist[v]) {
					dist[v] = cost[e];
					pq.push(mp(dist[v],v));
				}
				level[v] = dist[u] + 1;
			}
		}
	}
	for(int i = 1;i <= n;i++) if(dist[i] >= (1 << 29)) ret = -1;
	return ret;
}


int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	while(cin >> n >> m){
		M.clear();
		name[0] = "English";
		M[name[0]] = 0;
		E[0].clear();
		range(i,1,n) {
			cin >> name[i];
			M[name[i]] = i;
			E[i].clear();
		}
		loop(e,m){
			cin >> a >> b >> cost[e];
			fr[e] = M[a];
			to[e] = M[b];
			E[fr[e]].pb(e);
			E[to[e]].pb(e);
		}
		int ret = dijkstra();
		if(ret == -1) puts("Impossible");
		else printf("%d\n",ret);

	}
	return 0;
}
