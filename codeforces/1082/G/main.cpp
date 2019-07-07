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

const int MAXN = 1024*10,MAXE = 1024*10;
const ll oo = 1LL << 45;
int fr[MAXN],to[MAXN];
ll cap[MAXN];
int head[MAXN],nxt[MAXE];
int edge_cnt,n,m,src,snk;
int cost[MAXN];
int i_edge[MAXN];

void add_edge(int a,int b,ll c) {
	fr[edge_cnt] = a;
	to[edge_cnt] = b;
	cap[edge_cnt] = c;

	nxt[edge_cnt] = head[a];
	head[a] = edge_cnt;
	edge_cnt++;
}

void add_edge(int a,int b,ll c1,ll c2) {
	add_edge(a,b,c1);
	add_edge(b,a,c2);
}


bool bfs(){
	static queue<int> q;
	memset(i_edge,-1,sizeof i_edge);
	i_edge[src] = 0;
	q.push(src);
	for(;!q.empty();q.pop()) {
		int u = q.front();
		for(int e = head[u];~e;e = nxt[e]) if(cap[e] > 0){
			int v = to[e];
			if(i_edge[v] == -1) {
				i_edge[v] = e;
				q.push(v);
			}
		}
	}
	return i_edge[snk] != -1;
}

ll augment(){
	ll f = oo;
	int u = snk;
	while(u != src) {
		int e = i_edge[u];
		f = min(f,cap[e]);
		u = fr[i_edge[u]];
	}
	u = snk;
	while(u != src) {
		int e = i_edge[u];
		cap[e] -= f;
		cap[e^1] += f;
		u = fr[i_edge[u]];
	}
	return f;
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	memset(head,-1,sizeof head);
	scanf("%d %d",&n,&m);
	src = 0;
	snk = n + m + 1;
	range(i,1,n) {
		int w; scanf("%d",&w);
		add_edge(i,snk,w,0);
		cost[i] = -w;
	}
	for(int e = n+1;e <= n+m;e++) {
		int a,b,w;
		scanf("%d %d %d",&a,&b,&w);
		add_edge(src,e,w,0);
		add_edge(e,a,oo,0);
		add_edge(e,b,oo,0);
		cost[e] = w;
	}
	ll f = 0;
	while(bfs()) f += augment();

	ll ans = 0;

	memset(i_edge,-1,sizeof i_edge);
	queue<int> q;
	q.push(src);
	i_edge[src] = 0;
	for(;!q.empty();q.pop()) {
		int u = q.front();
//		if(u <= n) cerr  << cost[u] << " from " << u << endl;
//		else cerr << "+" << cost[u] << " from " << u - n << endl;
		ans += cost[u];
		for(int e = head[u];~e;e = nxt[e]) if(cap[e]){
			int v = to[e];
			if(i_edge[v] == -1) {
				i_edge[v] = e;
				q.push(v);
			}
		}
	}
	ll tot = 0;
	for(int e = n+1;e <= n+m;e++) tot += cost[e];
	cerr << ans << " " << tot - f << endl;
	cout << ans << endl;
	return 0;
}
