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


const int MAXN = 1 << 10;
vi G[2][MAXN];
int M[2];
int N[2];

bool vis[2][MAXN][MAXN];

void dfs(int u,int d,int i) {
	if(vis[i][u][d]) return;
	vis[i][u][d] = 1;
	for(int v : G[i][u])
		dfs(v,d+1,i);
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	loop(i,2) scanf("%d",N + i);
	loop(i,2) scanf("%d",M + i);
	loop(i,2) {
		int m = M[i];
		loop(e,m){
			int a,b; scanf("%d %d",&a,&b);
			G[i][a].push_back(b);
		}
	}
	loop(i,2) dfs(1,0,i);
	int Q; scanf("%d",&Q);
	while(Q--) {
		int q; scanf("%d",&q);
		bool y = 0;
		for(int a = 0;a <= q && !y;a++)
			y = vis[0][N[0]][a] && vis[1][N[1]][q-a];
		puts(y ? "Yes" : "No");
	}
	return 0;
}
#endif
