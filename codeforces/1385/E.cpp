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


int n, m;
vp undirected;
vector<vi> G;
vector<bool> vis;
vi ord, Id;

void dfs(int u){
	if(vis[u]) return ;
	vis[u] = true;
	for(int v : G[u]) dfs(v);
	ord.push_back(u);
}

void tc(){
	scanf("%d %d", &n, &m);
	G.clear();
	G.resize(n + 1);
	undirected.clear();
	loop(e, m){
		int t, a, b; scanf("%d %d %d", &t, &a, &b);
		if(t == 0){
			undirected.emplace_back(a, b);
		} else {
			G[a].push_back(b);
		} 
	}
	vis.resize(n + 1);
	ord.clear();
	fill(all(vis), false);
	for(int u = 1; u <= n; u++) dfs(u);
	Id.resize(n + 1);
	assert(sz(ord) == n);
	reverse(all(ord));
	loop(i, n) Id[ord[i]] = i;
	for(int u = 1; u <= n; u++) {
		for(int v : G[u])
			if(Id[v] < Id[u]){
				puts("NO");
				return;
			}
	}
	puts("YES");
	for(int u = 1; u <= n; u++) {
		for(int v : G[u])
			printf("%d %d\n", u, v);
	}
	for(auto [a, b] : undirected){
		if(Id[a] < Id[b]){
			printf("%d %d\n", a, b);
		} else {
			printf("%d %d\n", b, a);
		}
	}
	
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--) tc();
	return 0;
}
