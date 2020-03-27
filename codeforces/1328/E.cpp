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

const int MAX = 200*1000 + 10;
vi G[MAX];
int dfs_in[MAX], dfs_out[MAX], dfs_time;
int P[MAX];

void dfs(int u, int p){
	P[u] = p;
	dfs_in[u] = dfs_time++;
	for(int v : G[u]) if(v != p) dfs(v, u);
	dfs_out[u] = dfs_time;
}


vi Q;


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int n, m; scanf("%d %d", &n, &m);
	loop(e, n-1){
		int a, b; scanf("%d %d", &a, &b);
		G[a].pb(b);
		G[b].pb(a);
	}
	dfs(1, 0);
	while(m--){
		Q.clear();
		int k; scanf("%d", &k);
		while(k--){
			int x; scanf("%d", &x);
			Q.pb((x == 1) ? 1 : P[x]);
		}
		sort(all(Q), [](const int & a, const int & b){
			return dfs_in[a] < dfs_in[b];
		});
		bool y = 1;
		for(int i = 1; i < sz(Q) && y;i++){
			int p = Q[i-1], u = Q[i];
			y = dfs_in[p] <= dfs_in[u] && dfs_in[u] < dfs_out[p];
		}
		puts(y ? "YES" : "NO");
	}
	return 0;
}
