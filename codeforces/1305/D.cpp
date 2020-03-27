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

const int MAX = 1 << 10;
vi G[MAX];
int n, N;
bool dead[MAX];

int ask(int u, int v){
	printf("? %d %d\n", u, v);
	fflush(stdout);
	int w; scanf("%d", &w);
	return w;
}

int get_any(){
	for(int u = 1; u <= n; u++)
		if(!dead[u])
			return u;
	assert(0);
	return 0;
}

pi dfs(int u, int p, int d){
	pi ret(d, u);
	for(int v : G[u]) if(v != p && !dead[v]) ret = max(ret, dfs(v, u, d+1));
	return ret;
}

pi get_diameter(int root){
	pi A = dfs(root, 0, 0);
	int u = A.second;
	pi B = dfs(u, 0, 0);
	int v = B.second;
	return pi(u, v);
}

void mark(int u, int p){
	dead[u] = 1;
	N--;
	for(int v : G[u]) if(v != p && !dead[v]) mark(v, u);	
}

bool do_kill(int w, int p, int u, int v, bool is_root){
	bool ret = w == u || w == v;
	for(int t : G[w]) if(t != p && !dead[t]) {
		bool f = do_kill(t, w, u, v, 0);
		ret = ret || f;
		if(f && is_root) mark(t, w);
	}
	return ret;
}

int main(){
	scanf("%d", &n);
	loop(e, n-1){
		int a, b; scanf("%d %d", &a, &b);
		G[a].pb(b);
		G[b].pb(a);
	}
	N = n;
	while(N > 1){
		int k = get_any();
		pi p = get_diameter(k);
		int w = ask(p.first, p.second);
		do_kill(w, 0, p.first, p.second, 1);
	}
	cout << "! " << get_any() << endl;
	return 0;
}
