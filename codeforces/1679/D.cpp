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

int n, m;
ll K;
int A[1 << 20];
vi adj[1 << 20];
int vis[1 << 20];
ll dp[1 << 20];


ll dfs(int u, int Th) {
	if(vis[u] == 1) return 1LL << 60;
	if(vis[u] == 2) return dp[u];
	vis[u] = 1;
	dp[u] = 1;
	for(int v : adj[u]) if(A[v] <= Th) {
		dp[u] = max(dp[u], 1 + dfs(v, Th));
	}
	vis[u] = 2;
	dp[u] = min(dp[u], 1LL << 60);
	return dp[u];
}

bool check(int Th) {
	fill(vis, vis + n, 0);
	loop(i, n) if(A[i] <= Th && !vis[i] && dfs(i, Th) >= K) return true;
	return false;
}

void tc() {
	scanf("%d %d %lld", &n, &m, &K);
	loop(i, n) scanf("%d", A + i);
	loop(e, m) {
		int a, b; scanf("%d %d", &a, &b);
		a--, b--;
		adj[a].push_back(b);
	}
	vi B{A, A + n};
	sort(all(B));
	B.resize(unique(all(B)) - B.begin());
	if(!check(B.back())) {
		puts("-1");
		return;
	}
	int s = 0, e = sz(B) - 1;
	while(s < e) {
		int mid = (s + e) >> 1;
		if(check(B[mid])) e = mid;
		else s = mid + 1;
	}
	printf("%d\n", B[s]);
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	tc();
	return 0;
}
