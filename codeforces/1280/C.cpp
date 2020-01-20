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
vi E[1 << 20];
int fr[1 << 20], to[1 << 20], W[1 << 20];
int siz[1 << 20];

ll dfs(int u,int p){
	ll mn = 0;
	siz[u] = 1;  
	for(int e : E[u]){
		int v = fr[e] + to[e] - u;
		if(v == p) continue;
		mn += dfs(v, u);
		siz[u] += siz[v];
		if(siz[v] & 1) mn += W[e];	
	}
	return mn;
}

ll getMax(){
	vi ord;
	loop(e,n-1) ord.push_back(e);
	sort(all(ord), [](const int & a,const int & b){
		return W[a] > W[b];
	});
	ll ans = 0;
	for(int e : ord){
		int s = min(siz[fr[e]], siz[to[e]]);
		s = min(s, n - s);
		ans += s*(ll)W[e];
	}
	return ans;
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d",&T);
	while(T--){
		int k; scanf("%d",&k);
		n = 2*k;
		for(int i = 1;i <= n;i++) E[i].clear();
		loop(e,n-1){
			scanf("%d %d %d",fr + e, to + e, W + e);
			E[fr[e]].push_back(e);
			E[to[e]].push_back(e);
		}
		auto mn = dfs(1, 0);
		printf("%lld %lld\n",mn, getMax());
	}
	return 0;
}
