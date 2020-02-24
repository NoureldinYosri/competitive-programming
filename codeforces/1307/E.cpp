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

const int MAX = 1 << 20, MAXLG = 20;
int n, K, r;
vi G[MAX];
bool is_special[MAX];

set<pi> *S[MAX];
int id[MAX], W[MAX];
int depth[MAX];
int dfs_in[MAX], dfs_out[MAX], dfs_time;
int P[MAX][MAXLG];

int find(int a){
	return id[a] = (a == id[a]) ? a : find(id[a]);
}
void join(int a, int b){
	a = find(a), b = find(b);
	if(a == b) return;
	if(W[a] < W[b]) swap(a, b);
	W[a] += W[b];
	id[b] = a;
}
bool inSubTree(int a,int b){
	return dfs_in[b] <= dfs_in[a] && dfs_in[a] <= dfs_out[b];
}
 
int lca(int a,int b){
	if(depth[a] > depth[b]) swap(a,b);
	if(inSubTree(b,a)) return a;
	int k = MAXLG - 1;
	while(a != b){
		if(depth[a] > depth[b]) swap(a,b);		
		while(k && inSubTree(a,P[b][k])) k--;
		b = P[b][k];
	}
	return a;
}

int get_dist(int a, int b){
	return depth[a] + depth[b] - 2*depth[lca(a, b)];
}


void dfs(int u, int p, int d){
	depth[u] = d;
	dfs_in[u] = dfs_time++;
	P[u][0] = p;
	loop(k, MAXLG-1) P[u][k+1] = P[P[u][k]][k];
	
	int pref_child = 0;
	for(int v : G[u]) if(v != p){
		dfs(v, u, d+1);
		if(!pref_child || S[v]->size() > S[pref_child]->size())
			pref_child = v;
	}
	if(!pref_child) S[u] = new set<pi>();
	else S[u] = S[pref_child];
	if(is_special[u]) S[u]->emplace(d, u);
	for(int v : G[u]) if(v != p && v != pref_child){
		for(pi q : (*S[v]))
			S[u]->insert(q);
	}
	
	if(!S[u]->empty()){
		int t = S[u]->begin()->second;
		int h = S[u]->begin()->first;
		auto ptr = S[u]->begin();
		for(ptr++; ptr != S[u]->end(); ptr++){
			int v = ptr->second;
			int dist = h + ptr->first - 2*d; 
			if(dist <= K){
				cerr << "join " << v << " " << t << endl;
				join(v, t);
			}
		}
	}
	
	dfs_out[u] = dfs_time-1;
}

queue<int> q;
int dist[MAX];
void bfs(){
	fill(dist, dist + n + 1, INT_MAX);
	for(int i = 1;i <= n;i++) {
		if(is_special[i]){
			q.push(i);
			dist[i] = 0;
		}
	}
	while(!q.empty()){
		int u = q.front(); q.pop();
		int d = dist[u];
//		cerr << u << " id " << id[u] << endl;
		if(d == K) continue;
		for(int v : G[u]) if(dist[u] + 1 < dist[v]){
			dist[v] = dist[u] + 1;
			id[v] = id[u];
			q.push(v);
		}
		
	}
	
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d %d", &n, &K, &r);
	loop(e, n-1){
		int a, b; scanf("%d %d", &a, &b);
		G[a].pb(b);
		G[b].pb(a);
	}
	loop(i, r){
		int x; scanf("%d", &x);
		is_special[x] = 1;
	}
	loop(i, n+1) id[i] = i, W[i] = 1;
	bfs();
	dfs_out[0] = n;
	dfs(1, 0, 0);
	
	int m; scanf("%d",&m);
	while(m--){
		int a, b; scanf("%d %d", &a, &b);
		if(get_dist(a, b) <= K){
			puts("YES");
			continue;
		}
		cerr << a << " " << b << " " << id[a] << " " << id[b] << endl;
		a = find(a);
		b = find(b);
		puts((a == b) ? "YES" : "NO");
	}
	return 0;
}
