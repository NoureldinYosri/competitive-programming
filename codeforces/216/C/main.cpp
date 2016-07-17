#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define point pair<double,double>
#define pl pair<ll,ll>
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

const int MAX = 1e5 + 1e2;
vp G[MAX];
int n;
int color[MAX];

int dfs(int u,int p = 0,int cnt = 0){
	int ret = 0;
	for(pi e : G[u]) if(e.xx != p) ret += dfs(e.xx,u,e.yy);
	color[u] = !ret && cnt;
	ret += (!ret && cnt);
	return ret;
}

int main(){
	int a,b,c;
	scanf("%d",&n);
	loop(i,n - 1){
		scanf("%d %d %d",&a,&b,&c); c--;
		G[a].pb(mp(b,c));
		G[b].pb(mp(a,c));
	}
	int ans = dfs(1),q = 0;
	cout << ans << endl;
	range(i,1,n) if(color[i]) printf("%d%c",i," \n"[++q == ans]);
	cerr << ans << endl;
	return 0;
}
