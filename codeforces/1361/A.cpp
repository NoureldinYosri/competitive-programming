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

const int MAX = 500*1000 + 10;
int n, m;
vi G[MAX];
int deg[MAX];
int color[MAX];

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d", &n, &m);
	loop(e, m){
		int a, b; scanf("%d %d", &a, &b);
		G[a].pb(b);
		G[b].pb(a);
		deg[a]++;
		deg[b]++;
	}
	for(int u = 1; u <= n; u++) scanf("%d", color + u);
	vi V;
	for(int u = 1; u <= n; u++){
		V.pb(u);
	}
	for(int u = 1; u <= n; u++){
		set<int> S;
		for(int v : G[u]){
			if(color[v] < color[u]) S.insert(color[v]);
			if(color[u] == color[v]){
				puts("-1");
				return 0;
			}
		}
		if(sz(S) != color[u]-1){
			puts("-1");
			return 0;
		}
	}
	sort(all(V), [](const int & a, const int &b){
		return color[a] < color[b];
	});
	
	if(sz(V) < n) puts("-1");
	else {
		for(int v : V) printf("%d ", v);
		puts("");
	}
	return 0;
}
