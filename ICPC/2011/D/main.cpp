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

const int MAXN = 2*40 + 10,MAXE = MAXN*MAXN;
const int oo = 1 << 29;
int fr[MAXE],to[MAXE],cap[MAXE],cost[MAXE],edge_cnt,N;
int src,snk;
int iE[MAXN];
int bridges[MAXN];

int add_edge(int a,int b,int ca,int co) {
	int e = edge_cnt++;
	fr[e] = a;
	to[e] = b;
	cap[e] = ca;
	cost[e] = co;
	return e;
}
int add_flow_edge(int a,int b,int ca,int co) {
	add_edge(b,a,0,-co);
	return add_edge(a,b,ca,co);
}


int dist[MAXN],oo = 1 << 25;

int bellman(){
	loop(i,N) dist[i] = oo;
	dist[src] = 0;
	loop(i,N-1) {
		loop(e,edge_cnt) if(cap[e]){
			int a = fr[e],b = to[e],w = cost[e];
			if(dist[a] + w < dist[b]) {
				dist[b] = dist[a] + w;
				iE[b] = e;
			}
		}
	}
	bool found = 0;
	loop(e,edge_cnt) if(cap[e]){
		int a = fr[e],b = to[e],w = cost[e];
		if(dist[a] + w < dist[b]) {
			found = 1;
		}
	}
	return found;
}

int augment(int & F){
	static set<int> vis;
	int u = snk;
	loop(e,edge_cnt) if(cap[e]){
		int a = fr[e],b = to[e],w = cost[e];
		if(dist[a] + w < dist[b]) {
			u = b;
			break;
		}
	}

	F++;
	vis.clear();

	int ret = 0;
	while(!vis.count(u)) {
		vis.insert(u);
		int e = iE[u];
		ret += 2*(e&1) - 1;
		cap[e] --;
		cap[e^1]++;
		u = fr[e];
	}
	return ret;
}

int n,A,B;
char grid[MAXN][MAXN];

bool read(){
	scanf("%d %d %d",&n,&A,&B);
	if(n == 0 && A == 0 && B == 0) return 0;
	loop(i,n)
		scanf("%s",grid[i]);
	return 1;
}

void build(){
	src = 0;
	snk = 2*n + 1;
	N = snk + 1;

	loop(i,n) {
		int u = 2*i + 1,v = u + 1;
		add_flow_edge(src,u,oo,0);
		bridges[i] = add_edge(u,v,0,0);
		add_flow_edge(v,snk,oo,0);
	}

	loop(i,n) {
		int u = 2*i + 2;
		loop(j,n) {
			if(grid[i][j] == '/') continue;
			int v = 2*j + 1;
			if(grid[i][j] == '.')
				add_flow_edge(u,v,1,-1);
			else
				add_flow_edge(u,v,1,-oo);
		}
	}
}

int solve(){
	int ans = -1,f = 0,found = 0;
	int tmp = 0;
	int old = 0;
	int m = 0;
	while((m*A)/B == 0) m++;
	for(;m <= n;m++) {
		if(old != (A*m)/B){
			assert((A*m)/B == old + 1);
			loop(i,n) cap[bridges[i]]++;
			old ++;
		}
		while(bellman())
			tmp += augment(f);
		if(f == m)
			ans = tmp,found = 1;
	}
	cerr << f << " " << tmp << " " << ans << endl;
	if(!found) return oo;
	return ans;
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	for(int cn = 1;read();cn++) {
		build();
		int ans = solve();
		printf("Case %d: ",cn);
		if(ans >= oo) puts("impossible");
		else printf("%d\n",ans);
		edge_cnt = 0;
	}
	return 0;
}
