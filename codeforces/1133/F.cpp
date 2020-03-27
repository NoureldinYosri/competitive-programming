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
int deg[MAXN], P[MAXN];
vi G[MAXN];
bool vis[MAXN];
int n, m;

void dfs(int u, int p){
	P[u] = p;
	deg[p]++;
	vis[u] = 1;
	for(int v : G[u]) if(!vis[v]) dfs(v, u);
}




int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int D; scanf("%d %d %d", &n, &m, &D);
	loop(e, m){
		int a, b; scanf("%d %d", &a, &b);
		G[a].pb(b);
		G[b].pb(a);
	}
	if(sz(G[1]) < D){
		puts("NO");
		return 0;
	}
	dfs(1, 0);
	if(deg[1] > D){
		puts("NO");
		return 0;		
	}
	int r = D - deg[1];
	for(int v : G[1]){
		if(!r) break;
		if(P[v] == 1) continue;
		P[v] = 1;
		r--;
	}
	if(r){
		puts("NO");
		return 0;				
	}
	puts("YES");
	for(int i = 2; i <= n;i++)
		printf("%d %d\n", i, P[i]);
	return 0;
}
