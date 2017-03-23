#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
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

const int MAX = 80000 + 10;
vi G[MAX];
ll ans = 0;
int siz[MAX],n;
ll Y[MAX];

ll dfs(int u,int p){
	siz[u] = 1;
	ll sxy = 0;	
	for(int v : G[u]) if(v != p) {
		Y[u] += dfs(v,u);
		siz[u] += siz[v];
		sxy += siz[v]*1LL*Y[v];
	}
	ans += (n - siz[u] + 0LL) * Y[u];
	for(int v : G[u]) if(v != p) {
		ans += (n - siz[u])*siz[v]*(Y[u] - Y[v]);
	}
	ll sx = siz[u] - 1;
	for(int v : G[u]) if(v != p) {
		sx -= siz[v];
		sxy -= siz[v] * 1LL* Y[v];
		ans += siz[v] * (sx*(Y[u] - Y[v]) - sxy);
	}
	for(int v : G[u]) if(v != p){
		ans += siz[v] * (Y[u] - Y[v]);
	}
	ll tmp = 0;
	for(int v : G[u]) if(v != p){
		tmp += Y[v] * (Y[u] - Y[v]);
	}
	ans += tmp >> 1;
	siz[u] = 1;
	for(int v : G[u]) if(v != p) {
		Y[u] += siz[u] * 1LL * siz[v];
		siz[u] += siz[v];
	}
	//cerr << u << " " << ans << " " << Y[u] << " " << siz[u] << endl;
	return Y[u];
}

int main(){
	scanf("%d",&n);
	loop(i,n-1){
		int a,b; scanf("%d %d",&a,&b);
		G[a].pb(b);
		G[b].pb(a);
	}
	dfs(1,0);
	ans <<= 1;
	cerr << ans << endl;
	cout << ans << endl;
	
	return 0;
}
