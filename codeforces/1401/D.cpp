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

const int mod = 1e9 + 7;
const int MAXN = 100*1000 + 10;
vector<ll> S;
int siz[MAXN], n, m;
vector<ll> primes;
vector<vi> tree;

void dfs(int u, int p){
	siz[u] = 1;
	for(int v : tree[u]) if(v != p) {
		dfs(v, u);
		S.pb(siz[v]*(n - siz[v] + 0LL));
		siz[u] += siz[v];
	}
}

void tc(){
	S.clear();
	tree.clear();
	primes.clear();
	scanf("%d", &n);
	tree.resize(n);
	loop(e, n-1){
		int a, b; scanf("%d %d", &a, &b);
		a--, b--;
		tree[a].pb(b);
		tree[b].pb(a);
	}
	scanf("%d", &m);
	primes.resize(m);
	for(ll & p : primes) scanf("%lld", &p);
//	cerr << "fix primes" << endl;
//	print(primes, ll);
	sort(all(primes));
	while(sz(primes) > 1 && sz(primes) > n-1) {
		ll x = primes.back();
		primes.pop_back();
		primes.back() = (primes.back() * x)%mod;
	}
	reverse(all(primes));
	while(sz(primes) < n-1) primes.pb(1);
	reverse(all(primes));
//	print(primes, ll);
	
	dfs(0, -1);
	sort(all(S));
//	print(S, ll);
//	print(primes, ll);
	int ans = 0;
	loop(i, sz(S)) {
		ans += (S[i]%mod*primes[i])%mod;
		if(ans >= mod) ans -= mod;
	}
	printf("%d\n", ans);
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--) tc();
	return 0;
}
