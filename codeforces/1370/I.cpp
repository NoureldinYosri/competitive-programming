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

int n, a, b;
vector<vi> G;
vi F;
ifstream is;

void dfs(int u, int p, int d) {
	F[u] += d;
	for(int v : G[u]) if(v != p) dfs(v, u, d + 1);
}

void work(){
	// cerr << "new case " << endl;
	is >> n >> a >> b;

	cout << n << endl;
	
	G.clear();
	F.clear();

	G.resize(n+1);
	loop(e, n-1){
		int u, v; is >> u >> v;
		G[u].pb(v);
		G[v].pb(u);
		cout <<  u << " " << v << endl;
	}
	F.resize(n+1, 0);
	dfs(a, 0, 0);
	dfs(b, 0, 0);
	// print(F, int);
	
	while(1){
		char c; scanf(" %c", &c);

		if(c == '?') {
			int m; scanf("%d", &m);
			int best = -1, c = -1;
			loop(i, m) {
				int u; scanf("%d", &u);
				if(c == -1) c = u, best = F[u];
				else if(F[u] < best) c = u, best = F[u];
			}
			cout << c << " " << best << endl;
		} else if(c == '!') {
			int x, y; scanf("%d %d", &x, &y);
			if(x > y) swap(x, y);
			if(a > b) swap(a, b);
			// cerr << pi(a, b) << " vs " << pi(x, y) << endl;
			assert(a == x && y == b);
			break;
		} else {
			assert(0);
		}
	}
}

int main(){
	is = ifstream("in.in");
	int T; is >> T;
	cout << T << endl;
	while(T--) work();

	is.close();
}