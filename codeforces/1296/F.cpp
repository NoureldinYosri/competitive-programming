
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

const int MAX = 5 << 10;
int fr[MAX], to[MAX], f[MAX];
int A[MAX], B[MAX], W[MAX];
vi ord;
vi E[MAX];
int n, m;

bool dfs(int u, int p, int t, int w){
	if(u == t) return 1;
	for(int e : E[u]){
		int v = fr[e] + to[e] - u;
		if(v == p) continue;
		if(dfs(v, u, t, w)){
			f[e] = w;
			return 1;
		}
	}
	return 0;
}

pair<int, bool> getMin(int u, int p, int t){
	if(u == t) return pi(INT_MAX, 1);
	int ret = INT_MAX;
	for(int e : E[u]){
		int v = fr[e] + to[e] - u;
		if(v == p) continue;
		auto tmp = getMin(v, u, t);
		if(tmp.second){
			tmp.first = min(tmp.first, f[e]);
			return tmp;
		}
	}
	return mp(ret, 0);
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d", &n);
	loop(e, n-1){
		scanf("%d %d", fr + e, to + e);
		f[e] = 1;
		E[fr[e]].pb(e);
		E[to[e]].pb(e);
	}
	scanf("%d", &m);
	loop(i, m){
		scanf("%d %d %d", A + i, B + i, W + i);
		ord.pb(i);
	}
	sort(all(ord), [](const int & a,const int & b){
		return W[a] < W[b];
	});
	for(int i : ord) dfs(A[i], 0, B[i], W[i]);
	for(int i : ord) if(getMin(A[i], 0, B[i]) != pair<int,bool>(W[i], 1)){
		puts("-1");
		return 0;
	}
	loop(e, n-1) printf("%d ", f[e]);
	puts("");
	return 0;
}
