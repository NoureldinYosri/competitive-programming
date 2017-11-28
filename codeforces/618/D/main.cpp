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

const int MAX = 200*1000 + 10;
int n,x,y;
vi G[MAX];
int f[MAX][2];

void dfs(int u,int p) {
	int sum = 0;
	vp vals;
	for(int v : G[u]) if(v != p) {
		dfs(v,u);
		sum += f[v][0];
		vals.pb(mp(f[v][0] - f[v][1],f[v][0]));
	}
	sort(all(vals));
	reverse(all(vals));
	if(sz(vals) == 0) {
		f[u][0] = 1;
		f[u][1] = 0;
	}
	else if(sz(vals) == 1) {
		f[u][0] = sum - vals.back().xx + 1 ;
		f[u][1] = vals.back().yy - vals.back().xx;
	}
	else {
		f[u][0] = sum - vals[0].xx - vals[1].xx + 1;
		f[u][1] = sum - vals[0].xx ;
	}
//	cerr << u << " " << f[u][0] << " " << f[u][1] << endl;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d %d",&n,&x,&y);
	loop(i,n-1) {
		int a,b;
		scanf("%d %d",&a,&b);
		G[a].pb(b);
		G[b].pb(a);
	}
	if(y <= x) {
		int blocked = 0;
		range(i,1,n) if(sz(G[i]) == n-1) blocked++;
		if(blocked == n) cout << (blocked-1LL)*x << endl;
		else cout << (blocked+0LL)*x + (n-blocked - 1LL)*y << endl;
	}
	else {
		int root = 1;
		range(i,1,n) if(sz(G[i]) == 1) root = i;
	//	cerr << "root is " << root << endl;
		dfs(root,0);
		ll cnt = f[root][0];
	//	cerr << cnt << endl;
		cout << (n - cnt)*x + (cnt - 1)*y << endl;
	}
	return 0;
}
