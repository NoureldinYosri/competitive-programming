#ifdef ACTIVE
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
#define tc() int T; scanf("%d",&T); for(int t = 1;t <= T;t++)
using namespace std;

const int MAXN = 100*1000 + 10;
int A[MAXN],n;
vi E[MAXN];
int fr[MAXN],to[MAXN],W[MAXN];
int deg[MAXN],S[MAXN];


void dfs(int u,int p,int e) {
	int ctr = 0;
	for(int e : E[u]) {
		int v = fr[e] + to[e] - u;
		if(v == p) continue;
		dfs(v,u,e);
		ctr++;
		S[u] += W[e];
	}
	if(!ctr) W[e] = A[u];
	else W[e] = 2*A[u] - S[u];
//	if(p) cerr << p << " " << u << " " << W[e] << endl;
}
bool check(){
	for(int u = 1;u <= n;u++) {
		ll s = 0;
		int w = 0;
		for(int e : E[u]) {
			if(W[e] < 0) return 0;
			s += W[e];
			w = max(w,W[e]);
		}
		if(sz(E[u]) == 1) {
			if(w != A[u]) return 0;
			continue;
		}
//		cerr << u << " " << A[u] << " " << s << " " << w << endl;
		if(s != 2*A[u]) return 0;
		if(w > A[u]) return 0;
	}
	return 1;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d",&n);
	for(int u = 1;u <= n;u++) scanf("%d",A + u);
	loop(e,n-1) {
		scanf("%d %d",fr + e,to + e);
		E[fr[e]].push_back(e);
		E[to[e]].push_back(e);
	}
	dfs(1,0,n);
	puts(check() ? "YES" : "NO");
	return 0;
}
#endif
