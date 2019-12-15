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

const int MAXN = 1 << 10,MAXM = 2 << 10;
int n,Q;
vi G[MAXN]
vi colors;
int ctr[MAXN][MAXM],distinct[MAXN];
ll ans[MAXN];
int P[MAXN],color[MAXN],siz[MAXN];
int dfs_in[MAXN],dfs_out[MAXN],euler[MAXN],dfs_time;


void dfs(int u,int p){
	dfs_in[u] = dfs_time;
	euler[dfs_time] = u;
	dfs_time++;
	P[u] = p;
	siz[u] = 1;
	for(int v : G[u]) if(v != p) {
		dfs(v,u);
		siz[u] += siz[v];
	}
	dfs_out[u] = dfs_time;
}

vector<pi> queries;

void update(int u,int c){
	ll delta = siz[u] - ans[u];
	for(int i = dfs_in[u];i < dfs_out[u];i++){
		int t = euler[u];
		color[t] = c;
		ans[t] = siz[t];
	}
	for(int p = P[u]; p; p = P[p]){
		ll old = ans[p];
		ans[p] += delta;
		delta += ans[p] - old;
		
		
	}
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d",&n,&Q);
	loop(e,n-1){
		int a,b; scanf("%d %d",&a,&b);
		G[a].push_back(b);
		G[b].push_back(a);
	}
	loop(q,Q){
		int t,u; scanf("%d %d",&t,&u);
		if(t == 1){
			int c; scanf("%d",&c);
			colors.push_back(c);
			queries.emplace_back(u,c);
		}
		else {
			queries.emplace_back(u,-1);
		}
	}
	
	dfs(1,0);
	sort(all(colors));
	colors.resize(unique(all(colors)) - colors.begin());
	
	for(auto q : queries){
		int u = q.first,c = q.second;
		if(c == -1) printf("%lld\n",ans[u]);
		else {
			c = lower_bound(all(colors),c) - colors.begin();
			update(u,c);
		}
	}
	
	return 0;
}
