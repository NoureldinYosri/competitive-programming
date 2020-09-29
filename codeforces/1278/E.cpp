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


vi adj[1 << 20];
vi T[1 << 20];
int n;

int L(int x){
	return 2*x - 1;
}
int R(int x){
	return 2*x;
}

void addEdge(int a, int b){
	adj[a].pb(b);
	cerr << "\t" << a << " " << b << endl;
}

void floodFill(int u, int p, int d = 0){
	addEdge(L(u), R(u));
	int prv = -1;
	for(int v : T[u]) if(v != p){
		if(true || d==0) {
			addEdge(L(u), L(v));
			addEdge(L(v), R(u));
			addEdge(R(u), R(v));
		}
		else {
			addEdge(L(v), L(u));
			addEdge(L(u), R(v));
			addEdge(R(v), R(u));
		}
		if(prv != -1) addEdge(R(prv), L(v));
		floodFill(v, u, d ^ 1);
		prv = v;
	}
}

vi ord;
bool vis[1 << 20];

void dfs(int u){
	if(vis[u]) return;
	vis[u] = true;
	for(int v : adj[u]) dfs(v);
	ord.pb(u);
}


vp ans;

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d", &n);
	loop(e, n-1){
		int a, b;
		scanf("%d %d", &a, &b);
		T[a].pb(b);
		T[b].pb(a);
	}
	floodFill(1, 0);
	for(int i = 1; i <= 2*n; i++) dfs(i);
//	print(ord, int);
	reverse(all(ord));
//	print(ord, int);
	ans.resize(n);
	for(int i = 0; i < sz(ord); i++) {
		int u = ord[i];
		int j = (u + 1) >> 1;
		if(u & 1){
			ans[j - 1].first = i+1;
		} else {
			ans[j - 1].second = i+1;
		}
	}
	for(auto [l, r] : ans)
		printf("%d %d\n", l, r);
	return 0;
}
