#pragma GCC optimize ("O3")
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

const int MAXN = 1000 + 10,MAXM = 10*1000 + 10;
const ll oo = 1LL << 60;
typedef pair<ll,int> state;
vi E[MAXN];
int fr[MAXM],to[MAXM],W[MAXM],magic[MAXM];
int n,m,L,s,t;
ll dist[2][MAXN];

void dijkstra(int src,ll *dist) {
	fill(dist,dist + n,oo);
	PQ<state,vector<state>,greater<state> > pq;
	dist[src] = 0; pq.push(mp(0,src));

	while(!pq.empty()) {
		int u = pq.top().second;
		ll d = pq.top().first;
		pq.pop();
		if(d != dist[u]) continue;
		for(int e : E[u]) {
			int v = fr[e] + to[e] - u;
			if(d + W[e] < dist[v]) {
				dist[v] = d + W[e];
				pq.push(mp(d + W[e],v));
			}
		}
	}
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d",&n,&m);
	scanf("%d %d %d",&L,&s,&t);
	loop(e,m) {
		scanf("%d %d %d",fr + e,to + e,W + e);
		if(W[e] == 0) {
			magic[e] = 1;
			W[e] = 1;
		}
		E[fr[e]].pb(e);
		E[to[e]].pb(e);
	}


	dijkstra(t,dist[1]);
	ll *dist = ::dist[0],*dist2 = ::dist[1];
	fill(dist,dist + n,oo);
	PQ<state,vector<state>,greater<state> > pq;
	dist[s] = 0; pq.push(mp(0,s));
	while(!pq.empty()) {
		int u = pq.top().second;
		ll d = pq.top().first;
		pq.pop();
		if(d != dist[u]) continue;
		for(int e : E[u]) {
			int v = fr[e] + to[e] - u;
			if(magic[e]) {
				ll sum = dist[u] + dist2[v];
				if(sum < L) W[e] = L - sum;
				magic[e] = 0;
			}
			if(dist[u] + W[e] < dist[v]) {
				dist[v] = dist[u] + W[e];
				pq.push(mp(dist[v],v));
			}
		}
	}


	if(dist[t] != L) return puts("NO"),0;
	puts("YES");
	loop(e,m) printf("%d %d %d\n",fr[e],to[e],W[e]);

	return 0;
}
