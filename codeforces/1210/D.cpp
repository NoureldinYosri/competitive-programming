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


const int MAXN = 100*1000 + 10;
int n, m;
int deg[MAXN];
vi big[MAXN];

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d", &n, &m);
	loop(e, m){
		int a, b; scanf("%d %d", &a, &b);
		if(a > b) swap(a, b);
		deg[a]++, deg[b]++;
		
		big[a].push_back(b);
	}
	
	ll ans = 0;
	for(int u = 1; u <= n; u++){
		ans += big[u].size() * (deg[u] + 0LL - big[u].size());
	}
	printf("%lld\n", ans);
	scanf("%d", &m);
	loop(q, m){
		int u; scanf("%d", &u);
		ans -= big[u].size()*(deg[u] + 0LL - big[u].size());
		for(int v : big[u]) {
			ans -= big[v].size();
			big[v].push_back(u);
			ans += deg[v] + 0LL - big[v].size();
		}
		big[u].clear();
		printf("%lld\n", ans);
	}
	return 0;
}
