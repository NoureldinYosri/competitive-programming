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

vi L, R;
vector<bool> vis;
vector<vi> G;
int N, M;

void init(){
	L.resize(N);
	R.resize(M);
	vis.resize(N);
	fill(all(L), -1);
	fill(all(R), -1);
	G.clear();
	G.resize(N);
}

bool dfs(int u){
	if(vis[u]) return 0;
	vis[u] = 1;
	for(int v : G[u]) if(R[v] == -1 || dfs(R[v])){
		L[u] = v;
		R[v] = u;
		return 1;
	}
	return 0;
}

void greedy(){
	vi ord;
	loop(i, N) ord.pb(i);
	random_shuffle(all(ord));
	for(int i : ord){
		for(int j : G[i]) if(R[j] == -1){
			L[i] = j;
			R[j] = i;
			break;
		}
	}
}

int kuhn(){
	greedy();
	int m = 0;
	loop(i, N) {
		if(L[i] == -1){
			fill(all(vis), 0);
			m += dfs(i);
		}
		else m++;
	}
	
	return m;
}



const int MAX = 500, oo = 1 << 29;
int n, m, F, T;
int dist[MAX][MAX];
int city[MAX];


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int num; scanf("%d", &num);
	while(num--){
		scanf("%d %d %d %d", &n, &m, &F, &T);
		N = F;
		M = n;
		init();
		loop(i, F) {
			scanf("%d", city + i);
			city[i]--;
		}
		loop(i, n) loop(j, n) dist[i][j] = oo*(i != j);
		loop(e, m){
			int a, b, c; scanf("%d %d %d", &a, &b, &c);
			a--, b--;
			dist[a][b] = dist[b][a] = min(dist[a][b], c);
		}
		loop(k, n) loop(i, n) loop(j, n) dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
		loop(i, F) loop(j, n) if(dist[city[i]][j] <= T) G[i].pb(j);
		printf("%d\n", kuhn());
	}
	return 0;
}
