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

const int MAX = 500*1000 + 10;
const int MAXLG = 20;
vi G[MAX];
int depth[MAX], P[MAX][MAXLG], dfs_in[MAX], dfs_out[MAX], dfs_time;
int n;

void floodfill(int u, int p){
	depth[u] = depth[p]+1;
	P[u][0] = p;
	loop(k, MAXLG-1) P[u][k+1] = P[P[u][k]][k];
	dfs_in[u] = dfs_time++;
	for(int v : G[u]) if(v != p) floodfill(v, u);
	dfs_out[u] = dfs_time-1;
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


int M, K;
int virus_city[MAX], virus_speed[MAX], id[MAX];
int visID[MAX], visNum;
int important_city[MAX];
vi V;
vi T[MAX];

ll get_estimate(int i, int u){
	if(i == -1) return (1LL << 60);
	int v = virus_city[i];
	int d = get_dist(u, v);
	ll steps = (d + virus_speed[i] - 1)/virus_speed[i];
	return i + K*max(steps - 1, 0LL);
}

int dfs(int u, int p){
	if(id[u] != -1) return id[u];
	visID[u] = visNum;
	id[u] = -1;
	for(int v : T[u]) if(v != p){
		int k = dfs(v, u);
		if(k == -1) continue;
		if(get_estimate(k, u) < get_estimate(id[u], u))
			id[u] = k;
	}
	return id[u];
}

void dfs(int u, int p, int fp){
	if(id[u] != -1 && virus_city[id[u]] == u) return;
	if(get_estimate(fp, u) < get_estimate(id[u], u))
		id[u] = fp;
	for(int v : T[u]) if(v != p) dfs(v, u, id[u]);
}

vi ST, aux;
vp E;

void build_tree(){
	visNum++;
	V.clear();
	loop(i, K)  V.pb(virus_city[i]);
	loop(i, M) V.pb(important_city[i]);
	
	sort(all(V), [](const int & a, const int & b){
		return dfs_in[a] < dfs_in[b];
	});
	V.resize(unique(all(V)) - V.begin());
//	print(V, int);

	ST.clear();
	E.clear();
	
	for(int v : V){
		if(ST.empty()){
			ST.pb(v);
			continue;
		}
		while(!ST.empty() && !inSubTree(v, ST.back())){
			int p = (sz(ST) > 1) ? ST[sz(ST)-2] : lca(v, ST.back());
			int u = ST.back();
			ST.pop_back();
			if(inSubTree(v, p)){
				int q = lca(v, u);
				E.emplace_back(u, q);
//				cerr << u << " " << p << endl;
				if(ST.empty() || ST.back() != q) ST.pb(q);				
			}
			else {
				E.emplace_back(u, p);
//				cerr << "\t**" << u << " " << p << endl;
			}
		}
		ST.pb(v);
	}
	while(sz(ST) > 1){
		int p = ST[sz(ST)-2];
		int u = ST.back();
		ST.pop_back();
		assert(u != p);
//		cerr << "\t***" << u << " " << p << endl;
		E.emplace_back(u, p);
	}
	for(auto e : E) T[e.first].clear(), T[e.second].clear();
	for(auto e : E){
		id[e.first] = id[e.second] = -1;
		T[e.first].pb(e.second);
		T[e.second].pb(e.first);
	}
	
}

void solve(){
	build_tree();
	visNum++;
	loop(i, K) id[virus_city[i]] = i;
	
	loop(i, M) if(visID[important_city[i]] != visNum) {
		int v = important_city[i];
//		cerr << "get answer for the component that contains " << v << endl;
		dfs(v, 0);
		dfs(v, 0, -1);
	} 
//	loop(i, K){
//		cerr << "\t" << virus_city[i] << " " << virus_speed[i] <<  endl;
//	}
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d", &n);
	loop(e, n-1){
		int a, b; scanf("%d %d", &a, &b);
		G[a].pb(b);
		G[b].pb(a);
	}
	floodfill(1, 0);
	dfs_out[0] = n;
	
	int q; scanf("%d", &q);
	while(q--){
		scanf("%d %d", &K, &M);
		loop(i, K) scanf("%d %d", virus_city + i, virus_speed + i);
		loop(i, M) scanf("%d", important_city + i);
		solve();
		loop(i, M) printf("%d%c", id[important_city[i]]+1, " \n"[i==M-1]);
	}
	
	return 0;
}
