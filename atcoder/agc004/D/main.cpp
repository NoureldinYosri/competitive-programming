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

const int MAX = 1 << 20;
int f[MAX],dist[MAX],n,k;
vi G[MAX];
int ans;

int dfs(int u,int p) {
	if(G[u].empty()) return 0;
	int mx = 0;
	for(int v : G[u]) {
		int h = dfs(v,u);
		if(u != 1 && h + 1 == k) {
			ans++;
			h = -1;
//			cerr << "cur " << u << " " << v << endl;
		}
		mx = max(mx,h + 1);
	}
	if(u != 1 && mx == k) {
		ans ++;
		mx = 0;
//		cerr << "cut " << p << " " << u << endl;
	}
//	cerr << u << " " << mx << endl;
	return mx;
}


int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d",&n,&k);
	range(i,1,n) scanf("%d",f + i);
	if(f[1] != 1) f[1] = 1,ans ++;
	range(i,2,n) G[f[i]].pb(i);
	dfs(1,0);

	cout << ans << endl;
	return 0;
}
