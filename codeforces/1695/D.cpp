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


vector<vi> adj;
int n;
int dp[1 << 20][2][2];
int root;

int dfs(int u, int p, bool mustHave, bool parentProvides) {
	int & ret = dp[u][mustHave][parentProvides];
	if(ret != -1) return ret;
	int cnt = 0;
	for(int v : adj[u]) if(v != p) cnt++;
	ret = 0;
	if(cnt == 0) {
		ret = mustHave;
	} else if(cnt == 1) {
		for(int v : adj[u]) if(v != p) ret += dfs(v, u, mustHave, parentProvides);
		ret;
	} else {
		int s = 0;
		for(int v : adj[u]) if(v != p) s += dfs(v, u, true, true);
		ret = s;

		if(parentProvides || u == root){
			for(int v : adj[u]) if(v != p) {
				int tmp = s - dfs(v, u, true, true) + dfs(v, u, false, true);
				ret = min(ret, tmp);
			}
		}
	}
//	cerr << u << " " << mustHave << " " << parentProvides << ": " << ret << endl;
	return ret;
}


void tc() {
	scanf("%d", &n);
	adj.clear();
	adj.resize(n + 1);
	loop(e,n-1) {
		int a, b; scanf("%d %d", &a, &b);
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	if(n <= 2) {
		printf("%d\n", n - 1);
		return;
	}
	root = 1;
	while(root <=n && sz(adj[root]) == 1) root++;
	assert(root <= n);
//	cerr << "root = " << root << endl;
	loop(i, n + 1) loop(j, 2) loop(k, 2) dp[i][j][k] = -1;
	printf("%d\n", dfs(root, 0, false, false));
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	test_cases();
	return 0;
}
