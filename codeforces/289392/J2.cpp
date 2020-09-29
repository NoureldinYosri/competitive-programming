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

const int MAXN = 300*1000 + 10;
vi adj[MAXN];
int fr[MAXN], to[MAXN];
int color[MAXN], n, m;

bool dfs(int u, int c, int lim){
	if(color[u] != -1) return color[u] != c;
	color[u] = c;
	for(int e : adj[u]) if(e <= lim) {
		int v = fr[e] + to[e] - u;
		if(dfs(v, c ^ 1, lim)) return true;
	}
	return false;
}

bool isBi(int lim){
	for(int u = 1; u <= n; u++) color[u] = -1;
	for(int u = 1; u <= n; u++) if(color[u] == -1 && dfs(u, 0, lim)) {
		return false;
	}
	return true;
}



int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d", &n, &m);
	loop(e, m){
		scanf("%d %d", fr + e, to + e);
		adj[fr[e]].pb(e);
		adj[to[e]].pb(e);
	}
	if(isBi(m-1)) {
		puts("-1");
	} else {
		int s = 0, e = m-1;
		while(s < e){
			int mid = (s + e) >> 1;
			if(!isBi(mid)) e = mid;
			else s = mid + 1;
		}
		cout << s + 1 << endl;
	}
	return 0;
}
