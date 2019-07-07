#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
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
using namespace std;

const int MAXV = 2*1000 + 10,MAXE = 4*10000;
int n,m;
vi E[MAXV];
int fr[MAXE],to[MAXE],C[MAXE],W[MAXE],F[MAXE],e;
int src,snk;
int iE[MAXV],dist[MAXV];

void add_edge(int a,int b,int c,int w) {
	fr[e] = a;
	to[e] = b;
	C[e] = c;
	W[e] = w;
	F[e] = 0;
	E[a].push_back(e);
	e++;
}

void add_flow_edge(int a,int b,int w) {
	add_edge(2*a + 1,2*b,1,w);
	add_edge(2*b + 1,2*a,0,-w);
}

void init(){
	e = 0;
	src = 0;
	snk = 2*n-2;
	loop(i,2*n)
		E[i].clear();
}

bool bellman(){
	int oo = 1 << 29;
	fill(dist,dist + 2*n,oo);
	dist[src] = 0;
	loop(i,2*n-1) {
		bool done = 1;
		loop(j,e) if(C[j]){
			int a = fr[j],b = to[j],w = W[j];
			if(dist[a] + w < dist[b]) {
				dist[b] = dist[a] + w;
				iE[b] = j;
				done = 0;
			}
		}
		if(done) break;
	}
	loop(j,e) if(C[j]){
		int a = fr[j],b = to[j],w = W[j];
		if(dist[a] + w < dist[b]) {
//			fprintf(stderr,"dist[%d] + %d = %d + %d = %d < dist[%d] = %d\n",a,w,dist[a],w,dist[a] + w,b,dist[b]);
			cout << "found -ve cycle" << endl;
			assert(0);
		}
	}
	return dist[snk] != oo;
}

int augment(){
	int cur = snk,ret = 0;
	while(cur != src) {
		int j = iE[cur];
		assert(j != -1);
		assert(to[j] == cur);
		C[j] -- ;
		C[j^1] ++;
		F[j]++;
		F[j^1]--;
		ret += W[j];
		cur = fr[j];
	}
	return ret;
}

void johnson(){
	bellman();
	loop(j,e) {
		int u = fr[j],v = to[j],w = W[j];
		W[j] = w - dist[u] + dist[v];
	}
}

PQ<pi,vp,greater<pi> > pq;

bool dijkstra(){
	int oo = 1 << 29;
	while(!pq.empty()) pq.pop();
	fill(dist,dist + 2*n,oo);
	fill(iE,iE + 2*n,-1);
	dist[src] = 0;
	pq.push(mp(0,0));
	while(!pq.empty()) {
		pi cur = pq.top(); pq.pop();
		int d = cur.first,u = cur.second;
		if(dist[u] < d) continue;
		if(u == snk) return 1;
		for(int j : E[u]) if(C[j]) {
			assert(C[j] > 0);
			int v = to[j];
			if(dist[u] + W[j] < dist[v]) {
				dist[v] = dist[u] + W[j];
				iE[v] = j;
				pq.push(mp(dist[v],v));
			}
		}
	}
	return 0;
}

int solve(){
	int ans = 0,f = 0;
	johnson();
	while(dijkstra()){
		f++;
		ans += augment();
	}
	assert(f == 2);
	return ans;
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	while(scanf("%d %d",&n,&m) == 2) {
		init();
		loop(i,m) {
			int a,b,c; scanf("%d %d %d",&a,&b,&c);
			a--,b--;
			add_edge(2*a+1,2*b,1,c);
			add_edge(2*b,2*a+1,0,-c);
		}
		loop(i,n) {
			add_edge(2*i,2*i+1,1 + (i==0),0);
			add_edge(2*i+1,2*i,0,0);
		}
		printf("%d\n",solve());
	}
	return 0;
}
