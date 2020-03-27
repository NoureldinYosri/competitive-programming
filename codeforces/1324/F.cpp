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

const int MAXN = 200*1000 + 10;
vi G[MAXN];
int A[MAXN], n;
int ans[MAXN];

int dfs(int u, int p){
	for(int v : G[u]) if(v != p){
		ans[u] += max(0, dfs(v, u));
	}
	ans[u] += A[u] ? 1 : -1;
	return ans[u];
}


void dfs(int u, int p, int fp){
	fp = max(fp, 0);
	ans[u] += fp;
	for(int v : G[u]) if(v != p) {
		int tmp = ans[u];
		if(ans[v] > 0) tmp -= ans[v];
		dfs(v, u, tmp);
	}
}



int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d", &n);
	for(int i = 1;i <= n;i++) scanf("%d", A + i);
	loop(e, n-1){
		int a, b; scanf("%d %d", &a, &b);
		G[a].pb(b);
		G[b].pb(a);
	}
	dfs(1, 0);
	dfs(1, 0, 0);
	for(int i = 1;i <= n;i++) printf("%d%c", ans[i], " \n"[i==n]);	
	return 0;
}
