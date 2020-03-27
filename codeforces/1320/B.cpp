#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
typedef std::vector<int> vi;
typedef std::pair<int,int> pi;
typedef std::vector<pi> vp;
typedef long long ll;
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
template<class A,class B>
std::ostream& operator << (std::ostream& st,const std::pair<A,B> p) {
	st << "(" << p.first << ", " << p.second << ")";
	return st;
}
using namespace std;

const int MAX = 1 << 20;
vi G[MAX], rG[MAX];
int dist[2][MAX];
vi path;
int n, m;

queue<int> q;
void bfs(int root, int *D, vi *adj){
	fill(D,D + n + 1, -1);
	D[root] = 0;
	q.push(root);
	for(;!q.empty(); q.pop()){
		int u = q.front();
		for(int v : adj[u]) if(D[v] == -1){
			D[v] = D[u] + 1;
			q.push(v);
		}
	}
}

int src, snk;

int get_min(){
	int ret = 0;
	for(int i = 0;i+1 < sz(path); i++){
		int u = path[i];
		int v = path[i+1];
		if(dist[1][u] == dist[1][v] + 1) continue;
		ret ++;
	}
	return ret;
}

int get_max(){
	int ret = 0;
	for(int i = 0;i+1 < sz(path); i++){
		int u = path[i];
		int v = path[i+1];
		if(dist[1][u] != dist[1][v] + 1) 
			ret ++;
		else {
			bool f = 0;
			for(int t : G[u]) if(t != v && dist[1][u] == dist[1][t] + 1){
				f = 1;
				break;
			}
			ret += f;
		}
	}
	return ret;	
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d", &n, &m);
	loop(e, m){
		int a, b; scanf("%d %d", &a, &b);
		G[a].pb(b);
		rG[b].pb(a);
	}
	int k; scanf("%d", &k);
	loop(i, k){
		int x; scanf("%d", &x);
		path.pb(x);
	}
	src = path[0], snk = path.back();
	bfs(src, dist[0], G);
	bfs(snk, dist[1], rG);
	int mn = get_min();
	int mx = get_max();
	printf("%d %d\n", mn, mx);
	return 0;
}
