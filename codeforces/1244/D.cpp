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

const int MAX = 100*1000 + 10;

int C[MAX][3],n;
vi G[MAX];



int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d",&n);
	loop(j,3)
		for(int u = 1;u <= n;u++)
			scanf("%d",&C[u][j]);
	loop(e,n-1) {
		int a,b; scanf("%d %d",&a,&b);
		G[a].push_back(b);
		G[b].push_back(a);
	}
	for(int u = 1;u <= n;u++)
		if(sz(G[u]) > 2) {
			puts("-1");
			return 0;
		}

	int root = 1;
	while(sz(G[root]) != 1) root++;

	ll best = LLONG_MAX;
	vi bestColors;
	int color[3] = {0,1,2};

	do{
		ll tmp = 0;
		for(int u = root,p = 0,i = 0;i < n;i++) {
			tmp += C[u][color[i%3]];
			int s = 0;
			for(int v : G[u]) s += v;
			s -= p;
			p = u;
			u = s;
		}
		if(tmp < best) {
			best = tmp;
			bestColors = vi{color,color+3};
		}
	}while(next_permutation(color,color + 3));
	printf("%lld\n",best);
	int ans[MAX];
	for(int u = root,p = 0,i = 0;i < n;i++) {
		ans[u] = bestColors[i%3] + 1;
		int s = 0;
		for(int v : G[u]) s += v;
		s -= p;
		p = u;
		u = s;
	}
	for(int u = 1;u <= n;u++)
		printf("%d%c",ans[u]," \n"[u==n]);
	return 0;
}
#endif
