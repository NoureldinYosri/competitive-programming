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
 
const int MAX = 50000, B = MAX/3;
bitset<MAX> adj[B + 1];
int n, m;
bool vis[MAX];
vi G[MAX];
int k;
bitset<MAX> aux;



void dfs(int u){
	if(aux.test(u)) return;
	aux.set(u);
	for(int v : G[u]) dfs(v);
	
}

void floodfill(int u){
	if(aux.test(u)) return;
	if(u < k) {
		aux |= adj[u];
		return;
	}
	aux.set(u);
	for(int v : G[u]) dfs(v);	
}

 
int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d", &n, &m);
	k = n / 3;
	k = min(k, B);
	while(m--){
		int a, b; scanf("%d %d", &a, &b);
		a--, b--;
		swap(a, b);
		if(a < k)
			adj[a].set(b);
		G[a].pb(b);
	}
	loop(i, k) {
		dfs(i);
		adj[i] = aux;
		aux.reset();
	}
	ll ans = 0;
	loop(i, n){
		floodfill(i);
		ll r = aux.count();
		ans += r*r;
		aux.reset();
	}
	cout << ans << endl;
	return 0;
}
