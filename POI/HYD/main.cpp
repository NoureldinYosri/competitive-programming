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

const int MAX = 200*1000 + 10;
enum vcolor{white=0,grey=1,black=2};
vi G[MAX];
int n,m;
vcolor color[MAX];
vi ST;
vi connectedCycles[MAX];
vector<vi> cycles;

int extractCycle(int pivot) {
	int u;
	vi cycle;
	do{
		u = ST.back();
		if(u != pivot) ST.pop_back();
		cycle.push_back(u);
	}while(u != pivot);
	int c = cycles.size();
	cycles.push_back(cycle);
//	print(cycle,int);
	return c;
}


int dfs(int u,int p = -1) {
	if(color[u] == grey) return u;
	if(color[u] == black) return -1;
	assert(color[u] != black);
	color[u] = grey;
	ST.push_back(u);
	int res = -1;
	for(int v : G[u]) {
		if(v == p) continue;
		int r = dfs(v,u);
		if(r == -1) continue;
		if(r == u) {
			int c = extractCycle(r);
			connectedCycles[u].push_back(c);
		}
		else {
			assert(res == -1);
			res = r;
		}
	}
	color[u] = black;
	assert(res != -1 || (res==-1 && p==-1));
	return res;
}

void dfs(int c,int enteryPoint) {
	for(int u : cycles[c]) {
		if(u == enteryPoint) continue;
		for(int t : connectedCycles[])
	}
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d",&n,&m);
	loop(e,m) {
		int a,b; scanf("%d %d",&a,&b);
		G[a].push_back(b);
		G[b].push_back(a);
	}
	dfs(1);
//	print(ST,int);

	return 0;
}
