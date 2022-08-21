#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
using vi = std::vector<int>;
using pi = std::pair<int,int>;
using vp = std::vector<pi>;
using ll = long long;
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
template<class A,class B>
std::ostream& operator << (std::ostream& st,const std::pair<A,B> p) {
	st << "(" << p.first << ", " << p.second << ")";
	return st;
}
void tc();
auto test_cases = [](){
	int T; scanf("%d", &T);
	while(T--) tc();
};
using namespace std;

const int MAX = 1 << 20, MAXLG = 20;
vector<vi> adj;
int n, m;
int dfs_in[MAX], dfs_out[MAX], depth[MAX], dfs_time;
int P[MAX][MAXLG];

void readQuery(vi & V) {
	int c; scanf("%d", &c);
	V.resize(c);
	for(int & v : V) scanf("%d", &v);
 }

void dfs(int u, int p) {
	depth[u] = depth[p] + 1;
	dfs_in[u] = dfs_time++;
	P[u][0] = p;
	loop(k, MAXLG-1) P[u][k + 1] = P[P[u][k]][k];
	for(int v : adj[u]) if(v != p) {
		dfs(v, u);
	}
	dfs_out[u] = dfs_time - 1;
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

bool onPath(int v, int p, int b) {
	return dfs_in[v] <= dfs_in[b]
				&& dfs_in[b] <= dfs_out[v]
				&& dfs_in[p] <= dfs_in[v]
				&& dfs_in[v] <= dfs_out[p];
}

void tc() {
	scanf("%d", &n);
	adj.clear();
	adj.resize(n + 1);
	loop(e, n - 1) {
		int a, b; scanf("%d %d", &a, &b);
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	dfs_time = 0;
	dfs(1, 0);
	dfs_out[0] = n-1;

	static vi V;
	scanf("%d", &m);
	loop(q, m) {
		readQuery(V);
		if(sz(V) <= 2) {
			puts("YES");
			continue;
		}
		int p = V[0];
		for(int v : V)
			p = lca(p, v);
		int left = V[0];
		for(int v : V)
		 	if(inSubTree(v, left))
				left = v;
		int right = -1;
		for(int v : V) {
			if(onPath(v, p, left)) continue;
			if(right == -1 || inSubTree(v, right)) {
				right = v;
			}
		}
		if(right == -1) right = p;
		// cerr << left << "-" << p << "-" << right << endl;
		bool good = p == lca(left, right);
		for(int v : V) if(!onPath(v, p, left) && !onPath(v, p, right)) {
			good = false;
			break;
		}
		puts(good ? "YES" : "NO");
	}
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	tc();
	return 0;
}
