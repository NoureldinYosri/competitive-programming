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


vi L, R;
vector<bool> vis;
vector<vi> G;
int n;
int box[500][3];

void init(){
	L.resize(n);
	R.resize(n);
	vis.resize(n);
	fill(all(L), -1);
	fill(all(R), -1);
	G.clear();
	G.resize(n);
}

bool dfs(int u){
	if(vis[u]) return 0;
	vis[u] = 1;
	for(int v : G[u]) if(R[v] == -1 || dfs(R[v])){
		L[u] = v;
		R[v] = u;
		return 1;
	}
	return 0;
}

int kuhn(){
	int m = 0;
	loop(i, n) {
		if(L[i] == -1){
			fill(all(vis), 0);
			m += dfs(i);
		}
		else m++;
	}
	
	return m;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	while(scanf("%d", &n) == 1 && n){
		init();
		loop(i, n) loop(j, 3) scanf("%d", &box[i][j]);
		loop(i, n) loop(j, n) {
			bool can = 1;
			loop(k, 3) can &= box[i][k] < box[j][k];
			if(can) G[i].pb(j);
		}
		printf("%d\n", n - kuhn());
	}
	return 0;
}
