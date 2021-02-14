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
vector<vi> G;
vector<ll> A;
vi deg;
vector<bool> done;
vp V;

int get_cost(int u){
	for(int v : G[u])
		if(!done[v])
			return A[v];
	assert(0);
	return -1;
}

void tc(){
	scanf("%d", &n);
	G.clear();
	A.clear();
	deg.clear();
	done.clear();
	G.resize(n);
	A.resize(n);
	deg.resize(n, 0);
	done.resize(n, false);
	for(ll & a : A) scanf("%lld", &a);
	loop(e, n - 1){
		int a, b; scanf("%d %d", &a, &b);
		a--, b--;
		G[a].push_back(b);
		G[b].push_back(a);
		deg[a]++;
		deg[b]++;		
	}

	
	V.clear();
	loop(i, n) {
		V.emplace_back(A[i], i);
	}
	sort(all(V));

	ll ans = accumulate(all(A), 0LL);
	printf("%lld", ans);
	int best = 0, cnt = 0;
	for(int k = 2; k < n; k++){
		while(cnt <= 1){
			best = V.back().second;
			V.pop_back();
			cnt = 0;
			for(int v : G[best])
				cnt += !done[v];
		}
//		cerr << "use " << best << " " << A[best] << " cnt = " << cnt << endl;
		ans += A[best];
		printf(" %lld", ans);
		cnt--;
	}
	puts("");
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--) tc();	
	
	return 0;
}
