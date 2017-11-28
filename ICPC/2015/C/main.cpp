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

const ll oo = 1LL << 60;
const int MAX = 111;
int C[MAX][MAX];
int cost[MAX][MAX];
int n,K;
int src,snk;
int parent[MAX];
ll dist[MAX];

void addedge(int f,int t,int c,int co) {
	cost[f][t] = co;
	C[f][t] = c;
}

void addedge(int f,int t,int c1,int c2,int cost) {
	addedge(f,t,c1,cost);
	addedge(t,f,c2,-cost);
}

bool bellman(){
	fill(dist,dist + MAX,oo);
	dist[src] = 0;
	int N = snk + 1;
	for(int ctr = 0,done = 0;ctr < n && !done;ctr++){
		done = 1;
		loop(u,N) loop(v,N) if(C[u][v] && dist[u] + cost[u][v] < dist[v]) {
			dist[v] = dist[u] + cost[u][v];
			parent[v] = u;
			done = 0;
		}
	}
	return dist[snk] < oo;
}

ll augment(){
	int u = snk;
	ll ret = 0;
	while(u){
		int p = parent[u];
		C[p][u] ^= 1; C[u][p] ^= 1;
		ret += cost[p][u];
		u = p;
	}
	return ret;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d",&n,&K);
	src = 0;
	snk = (n+1);

	addedge(0,1,1,0,0);

	range(i,1,n){
		range(j,i+1,n+1) {
			int x; scanf("%d",&x);
//			cerr << i << " " << j << " -> " << x << endl;
			addedge(i,j,1,0,x);
		}
	}

	ll ans = 0;
	while(bellman())
		ans += augment();
	cout << ans << endl;
	return 0;
}
