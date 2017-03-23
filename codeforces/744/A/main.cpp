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

const int MAX = 1024;
vi G[MAX];
int vis[MAX],n,m,k;
int C[MAX],siz[MAX];
vi aux;

int dfs(int u){
	int ret = 1;
	vis[u] = 1;
	for(int v : G[u]) if(!vis[v]) ret += dfs(v);
	return ret;
}

int main(){
	scanf("%d %d %d",&n,&m,&k);
	loop(i,k) scanf("%d",C + i);
	loop(i,m) {
		int a,b; scanf("%d %d",&a,&b);
		G[a].pb(b);
		G[b].pb(a);		
	}
	loop(i,k) {
		assert(!vis[C[i]]);
		siz[i] = dfs(C[i]);
	}
	range(i,1,n) if(!vis[i]) aux.pb(dfs(i));
	ll ans = -m; int S = 0;
	loop(i,k) S += siz[i],ans += siz[i]*(siz[i] - 1)/2;
	for(int s : aux) ans += s*(s-1)/2;
	int c = 0;
	loop(i,k) if(siz[i] > siz[c]) c = i;
	for(int s : aux){
		ans += siz[c]*s;
		siz[c] += s;
	}
	cerr << ans << endl;
	cout << ans << endl; 
		
	return 0;
}
