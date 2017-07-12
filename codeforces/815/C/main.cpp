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
#define pl pair<ll,ll>
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

const int MAX = 5000 + 10;
int price[MAX],discount[MAX],parent[MAX];
vi G[MAX];
ll dp[2][MAX][MAX];
int n,palance;
const ll oo = 1LL << 60;
int siz[MAX];
ll aux[MAX];
void dfs(int u){
	siz[u] = 1;
	for(int v : G[u]) dfs(v);
	range(i,0,n) dp[0][u][i] = dp[1][u][i] = oo;
	dp[0][u][0] = 0;
	dp[0][u][1] = price[u];
	dp[1][u][1] = price[u] - discount[u];
	for(int v : G[u]){
		fill(aux,aux + n+1,oo);
		for(int k0 = 0;k0 <= siz[u];k0++) {
			for(int k1 = 0;k1 <= siz[v];k1++)
				aux[k0 + k1] = min(aux[k0 + k1],dp[0][u][k0] + dp[0][v][k1]);
		}
		copy(aux,aux + n+1,dp[0][u]);
		siz[u] += siz[v];
	}
	siz[u] = 1;
	for(int v : G[u]){
		fill(aux,aux + n+1,oo);
		for(int k0 = 0;k0 <= siz[u];k0++) {
			for(int k1 = 0;k1 <= siz[v];k1++){
				ll tmp = dp[1][u][k0];
				tmp += min(dp[0][v][k1],dp[1][v][k1]);
				aux[k0 + k1] = min(aux[k0 + k1], tmp);
			}
		}
		copy(aux,aux + n+1,dp[1][u]);
		siz[u] += siz[v];
	}
//	cerr << u << " : " << endl;
//	prArr(dp[0][u],n+1,ll);
//	prArr(dp[1][u],n+1,ll);
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d",&n,&palance);
	range(i,1,n) {
		scanf("%d %d",price + i,discount + i);
		if(i != 1) {
			scanf("%d",parent + i);
			G[parent[i]].pb(i);
		}
	}
	dfs(1);
	int ans = 0;
	for(int i = 1;i <= n;i++)
		if(dp[0][1][i] <= palance || dp[1][1][i] <= palance)
			ans = i;
	cout << ans << endl;
	return 0;
}
