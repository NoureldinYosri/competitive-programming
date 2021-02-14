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

const int MAXN = 2e5 + 10;
vi G[MAXN];
vi children[MAXN], childrenTime[MAXN];
int A[MAXN], parent[MAXN];
int dfs_in[MAXN], dfs_out[MAXN], dfs_time;
bool vis[MAXN];

bool inSubtree(int u, int v){
	return dfs_in[u] <= dfs_in[v] && dfs_in[v] <= dfs_out[u];
}


void dfs(int u, int p){
	parent[u] = p;
	dfs_in[u] = dfs_time++;
	for(int v : G[u]) if(v != p) {
		dfs(v, u);
		children[u].push_back(v);
		childrenTime[u].push_back(dfs_out[v]);
	}
	dfs_out[u] = dfs_time - 1;
}

int getNext(int u, int v){
	if(inSubtree(u, v)){
		int i = lower_bound(all(childrenTime[u]), dfs_in[v]) - childrenTime[u].begin();
		assert(i < sz(children[u]));
		return children[u][i];
	} else if(inSubtree(v, u)){
		return parent[u];
	} else {
		return parent[u];
	}
}



set<pi> bad;

void cut(int u, int v){
	int p = getNext(u, v);
	bad.emplace(p, u);
}

int cnt[MAXN];

int floodFill(int u, int p){
	for(int v : G[u]) if(v != p) {
		cnt[u] += bad.count(pi(v, u));
		cnt[u] += floodFill(v, u);
	}
	return cnt[u];
}

void dfs(int u, int p, int fp){
	int tot = fp + cnt[u];
	if(tot) vis[u] = true;
	for(int v : G[u]) if(v != p) {
		int tmp = tot;
		tmp -= bad.count(pi(v, u));
		tmp -= cnt[v];
		tmp += bad.count(pi(u, v));
		dfs(v, u, tmp);
	}
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int n; scanf("%d", &n);
	for(int u = 1; u <= n; u++) scanf("%d", A + u);
	loop(e, n -1){
		int a, b; scanf("%d %d", &a, &b);
		G[a].push_back(b);
		G[b].push_back(a);
	}
	dfs(1, 0);
	map<int, vi> M;
	for(int u = 1; u <= n; u++) M[A[u]].push_back(u);
	for(auto & [_, V] : M){
		if(sz(V) <= 1) continue;
		sort(all(V), [](const int & a, const int & b){
			return dfs_in[a] < dfs_in[b];
		});
		int m = sz(V);
		loop(i, m) {
			int j = (i + 1)%m;
			int u = V[i];
			int v = V[j];
			cut(u, v);
			cut(v, u);
		}
	}
	
	floodFill(1, 0);
	dfs(1, 0, 0);
	
	
	int ans = 0;
	for(int u = 1; u <= n; u++) ans += !vis[u];
	cout << ans << endl;
	return 0;
}
