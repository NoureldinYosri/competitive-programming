#pragma GCC optimize ("O3")
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

const int MAXV = 100,MAXCUR = 1 << 7,MAXLST = 100,MAXE = 150;
int vis[MAXV + 1][MAXCUR + 1][MAXLST + 1];
vi E[MAXV + 1];
int n,m;
int fr[MAXE],to[MAXE],C[MAXE];


int dfs(int u,int cur,int lst) {
	vis[u][cur][lst] = 1;
	int ret = cur;
	for(int e : E[u]) {
		int v = fr[e] + to[e] - u;
		int new_cur = cur ^ (lst & C[e]);
		int new_lst = C[e];
		if(vis[v][new_cur][new_lst]) continue;
		ret = max(ret,dfs(v,new_cur,new_lst));
	}
	return ret;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d",&n,&m);
	loop(e,m) {
		scanf("%d %d %d",fr + e,to + e,C + e);
		E[fr[e]].pb(e);
		E[to[e]].pb(e);
	}
	int ans = 0;
	range(i,1,n) if(!vis[i][0][0]) ans = max(ans,dfs(i,0,0));
	cout << ans << endl;
	return 0;
}
