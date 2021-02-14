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

int n;
int A[1 << 20];
int B[1 << 20];
vi G[1 << 20];
vi T[1 << 20];

vi ord;

bool vis[1 << 20];

void dfsOrd(int u){
	if(vis[u]) return;
	vis[u] = true;
	for(int v : T[u]) dfsOrd(v);
	ord.push_back(u);
}


pair<ll, ll> dfs(int u){
	ll s = A[u];
	ll ret = 0;
	vi aux;
	for(int v : G[u]){
		auto [t, tot] = dfs(v);
		s += max(t, 0LL);
		ret += tot;
		if(t >= 0) {
			T[v].push_back(u);
		} else {
			T[u].push_back(v);
		}
	}
	ret += s;
	return mp(s, ret);
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", A + i);
	for(int i = 1; i <= n; i++) {
		scanf("%d", B + i);
		if(B[i] != -1) G[B[i]].push_back(i);
	}
	ll ans = 0;
	for(int i = 1; i <= n; i++) if(B[i] == -1){
		auto [_, v] = dfs(i);
		ans += v;
	}
	for(int u = 1; u <= n; u++) dfsOrd(u);
	reverse(all(ord));
	printf("%lld\n", ans);
	for(int u : ord) printf("%d ", u);
	puts("");
	return 0;
}
