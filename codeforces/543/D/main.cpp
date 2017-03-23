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

const int MAX = 2e5 + 1e2,mod = 1e9 + 7 ;
vi G[MAX];
int f[MAX],g[MAX];

int dfs(int u){
	f[u] = 1;
	for(int v : G[u]) f[u] = (f[u] * (dfs(v) + 1LL))%mod;
	return f[u];
}

void dfs(int u,int val){
	g[u] = (f[u] * 1LL * val)%mod;
	reverse(all(G[u]));
	vi P(1,1);
	for(int v : G[u]) P.pb((P.back() * (f[v] + 1LL))%mod);
	reverse(all(G[u]));
	int p = 1;
	for(int v : G[u]){
		P.pop_back();
		int tmp = (p*1LL*val)%mod;
		tmp = (tmp * 1LL * P.back())%mod;
		tmp = (tmp + 1)%mod;
		dfs(v,tmp);
		p = (p * (f[v] + 1LL))%mod;
	}
}

int main(){
	int n; scanf("%d",&n);
	range(i,2,n){
		int p; scanf("%d",&p);
		G[p].pb(i);
	}	
	dfs(1);
	dfs(1,1);
	range(i,1,n) printf("%d%c",g[i]," \n"[i==n]);
	
	return 0;
}
