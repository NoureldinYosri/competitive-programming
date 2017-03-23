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

const int MAX = 100000 + 1e2;
vi G[MAX];
int dp[MAX][8];
int val[MAX];

bool isGood(int x){
	x %= 8;
	return (x == 3) || (x == 7);
}

void dfs(int u,ll & ans,int par[8]){
	fill(dp[u],dp[u] + 8,0);
	int aux[8] = {0}; par[0]++;
	loop(i,8) aux[(i + val[u])%8] = par[i];
	loop(i,8) par[i] = aux[i];
	for(int v : G[u]){
		ll tmp = 0;
		dfs(v,tmp);
		loop(i,8) loop(j,8) loop(k,8) {
			if(u && isGood(i + k) && isGood(j + k) && isGood(i + j + val[u])) ans += dp[u][i]*1LL*dp[v][k];
			if(u && !isGood(i) && !isGood(j) && !isGood(i + k)) ans += dp[u][i]*1LL*dp[v][k];
		}
		loop(i,8) dp[u][(i + val[u])%8] += dp[v][i];
		ans += tmp;
	}
	dp[u][val[u]%8] ++;
//	cerr << u << " : " ; prArr(dp[u],8,int);
//	cerr << u << " " << ans << endl;
}

void dfs(int u,ll & ans,int *aux){
	//cerr << u << " : " ; prArr(aux,8,int);
	dp[u][val[u]%8]--;
	loop(i,8) loop(k,8) {
		int j = (k + val[u])%8;
	//	if(u && isGood(i) && isGood(j) && isGood(i + k)) ans += dp[u][i]*1LL*aux[k];
		if(u && !isGood(i) && !isGood(j) && !isGood(i + k)) ans += dp[u][i]*1LL*aux[k];
	}
	if(u) aux[0]++;
	for(int v : G[u]){
		ll tmp = 0;
		int aux2[8] = {0};
		loop(i,8) aux2[(i + val[u])%8] += aux[i];
		loop(i,8) aux2[i] += dp[u][i];
		loop(i,8) aux2[(i + val[u])%8] -= dp[v][i];
		dfs(v,tmp,aux2);
		ans += tmp;
	}
//	cerr << u << " " << ans << endl;
}

int main(){
	int T; scanf("%d",&T);
	while(T--){
		int n; scanf("%d",&n);
		loop(i,n+1) G[i].clear();
		loop(i,n){
			int p; scanf("%d %d",&p,val + i + 1);
			G[p].pb(i + 1);
		}
		ll ans = 0,ans2 = 0;
		dfs(0,ans);
		int aux [8] = {0};
		dfs(0,ans2,aux);
		printf("%lld\n",ans + ans2);
		cerr << ans << " + " << ans2 << endl;
	}	
	
	
	return 0;
}
