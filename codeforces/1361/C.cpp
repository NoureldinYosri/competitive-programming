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

const int MAXA = 1 << 20, MAXN = 500*1000 + 10;
int n;
int A[MAXN], B[MAXN];
int deg[MAXA], where[MAXA];
vi in[MAXA], out[MAXA];
bool used[MAXA], vis[MAXA];

int dfs(int u){
	if(vis[u]) return 0;
	int ret = 1;
	vis[u] = 1;
	for(int x : out[u]){
		int id = (x + 1) >> 1;
		int y = 4*id - 1 - x;
		ret += dfs(where[y]);
	}
	return ret;
}

bool check(int d){
	int msk = (1 << d) - 1;
	loop(i, MAXA){
		in[i].clear();
		out[i].clear();
		deg[i] = 0;
	}
	int root = 0;
	int active = 0;
	loop(i, n) {
		int a = A[i] & msk;
		int b = B[i] & msk;
		if(a == b) {
			active += in[a].empty() && out[a].empty();
			in[a].pb(i + 1);
		} else {
			active += in[a].empty() && out[a].empty();
			active += in[b].empty() && out[b].empty();
			out[a].pb(2*i + 1);
			out[b].pb(2*i + 2);
		}
		
		where[2*i+1] = a;
		where[2*i+2] = b;

		deg[a]++;
		deg[b]++;		
		vis[a] = vis[b] = 0;
		root = a;
	}
	loop(i, MAXA) if(deg[i] & 1) return 0;
	return dfs(root) == active;
}

void euler(int u, int a, int b){
	while(!out[u].empty()){
		int x = out[u].back(); 
		out[u].pop_back();
		int id = (x + 1) >> 1;
		if(used[id]) continue;
		used[id] = 1;
		int y = 4*id-1-x;
		euler(where[y], x, y);
	}
	while(!in[u].empty()){
		int id = in[u].back(); in[u].pop_back();
		printf("%d %d ", 2*id-1, 2*id);
	}
	if(a != -1) {
		printf("%d %d ", b, a);
	}
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d", &n);
	loop(i, n) scanf("%d %d", A + i, B + i);
	int d = 20;
	for(;d > 0; d--) if(check(d)) break;
	printf("%d\n", d);
	if(d == 0){
		loop(i, n) printf("%d %d ", 2*i+1, 2*i+2);
		puts("");
		return 0;
	}
	int root = -1;
	loop(i, MAXA) if(!in[i].empty() || !out[i].empty()) root = i;
	euler(root, -1, -1);
	puts("");
	
	return 0;
}
