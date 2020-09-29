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

const int MAXN = 2 << 10, MAXM = 100*1000 + 10;

int A, B, n, m;
set<int> S[MAXN];
vi adj[MAXN];
int fr[MAXM], to[MAXM], color[MAXM];
int vis[MAXN];
int End[MAXN];

void dfs(int u){
	vis[u] = 1;
	int & cur = End[u];
	cur = 0;
	while(S[u].count(cur)) cur++; 
	for(int e : adj[u]) if(color[e] == -1){
		int v = fr[e] + to[e] - u;
		if(vis[v] == 0){
			color[e] = cur;
		} else {
			assert(vis[v] == 1);
			int cand = max(cur, End[v]);
			while(S[v].count(cand) || S[u].count(cand)) cand++;
			color[e] = cand;
		} 
		S[u].insert(color[e]);
		S[v].insert(color[e]);
		while(S[u].count(cur)) cur++; 
		while(S[v].count(End[v])) End[v]++;
		if(!vis[v]) dfs(v);
		while(S[u].count(cur)) cur++; 
	}
	vis[u] = 2;
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d %d", &A, &B, &m); 
	loop(e, m){
		int a, b; scanf("%d %d", &a, &b);
		a--;
		b = A + b - 1;
		fr[e] = a, to[e] = b;
		adj[a].pb(e);
		adj[b].pb(e);
	}
	n = A + B;
	memset(color, -1, sizeof color);
	
	loop(i, n) if(!vis[i]) dfs(i);
//	prArr(End, n, int);
//	prArr(color, m, int);
	
	printf("%d\n", *max_element(color, color + m) + 1);
	loop(e, m) printf("%d%c", color[e]+1, " \n"[e==m-1]);
	
	return 0;
}
