#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define popcnt(x) __builtin_popcountll(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
using namespace std;

const int MAX = 100*1000 + 10;
int n;
int B[MAX],A[MAX];
vp G[MAX];
__int128 supply[MAX];


__int128 dfs(int u,int p){
	supply[u] = B[u] - A[u];
	for(auto e : G[u]) {
		int v = e.xx;
		int k = e.yy;
		__int128 tmp = dfs(v,u);
		if(tmp == 0) continue;
		if(tmp > 0) supply[u] += tmp;
		else supply[u] += tmp*k;
	}
	return supply[u];
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d",&n);
	range(i,1,n) scanf("%d",B + i);
	range(i,1,n) scanf("%d",A + i);
	range(i,2,n){
		int p,k; scanf("%d %d",&p,&k);
		G[p].pb(mp(i,k));
	}
	if(dfs(1,0) < 0) puts("NO");
	else puts("YES");

	return 0;
}
