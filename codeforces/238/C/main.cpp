#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define popcnt(x) __builtin_popcountll(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
using namespace std;

vi G[3 << 10];
int n;
int vis[3 << 10];
int f [3 << 10];

int flood_fill(int u) {
	vis[u] = 1;
	int ret = 1;
	for(int v : G[u])
		if(!vis[v])
			ret += flood_fill(v);
	return ret;
}

int dfs(int u){
	if(f[u] != -1) return f[u];
	f[u] = 1;
	for(int v : G[u]) if(!vis[v]) {
		int tmp = dfs(v);
		f[u] += tmp;
	}
	return f[u];
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d",&n);
	range(i,1,n-1) {
		int a,b; scanf("%d %d",&a,&b);
		G[a].pb(b);
	}
	int ans = n-1;
	range(i,1,n) {
		memset(vis,0,sizeof vis);
		memset(f,-1,sizeof f);
		int n1 = flood_fill(i),n2 = 0;
		if(n1 == n) puts("0");
		int deg0 = 0,u = 0;
		range(j,1,n) if(!vis[j]) deg0++
		ans = min(ans,n-n1-n2);
	}
	cout << ans << endl;
	return 0;
}
