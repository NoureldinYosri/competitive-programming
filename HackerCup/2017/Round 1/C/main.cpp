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

const int MAX = 5100;
ll oo = 1LL << 60;
ll dist[MAX][MAX],dp[MAX][MAX];
int n,m,K;
int from[MAX],to[MAX];

ll add(ll a,ll b){
	return min(a+b,oo);
}

ll solve(int u,int k){
	if(k == K) return  0;
	if(dp[u][k] != -1) return dp[u][k];
	ll & ret = dp[u][k]; ret = oo;
	ret = add(solve(to[k],k+1),add(dist[u][from[k]] ,dist[from[k]][to[k]]));
	if(k != K - 1) {
		ll tmp = add(dist[u][from[k]] ,dist[from[k]][from[k+1]]); 
		tmp = add(tmp,dist[from[k+1]][to[k]]);
		tmp = add(tmp,dist[to[k]][to[k+1]]);
		tmp = add(tmp,solve(to[k + 1],k+2));
		ret = min(ret,tmp);
	}
	return ret;
}

int main(){
	int T; scanf("%d",&T);
	range(t,1,T){
		scanf("%d %d %d",&n,&m,&K);
		loop(i,n) loop(j,n) dist[i][j] = (i != j) * oo;
		loop(i,m){
			int a,b,c; scanf("%d %d %d",&a,&b,&c); a--,b--;
			dist[a][b] = dist[b][a] = min(dist[a][b],c+0LL);
		}
		loop(k,n) loop(i,n) loop(j,n) dist[i][j] = min(dist[i][j],dist[i][k] + dist[k][j]);
		loop(i,K) scanf("%d %d",from + i,to + i),from[i]--,to[i]--;
		memset(dp,-1,sizeof dp);		
		ll ans = solve(0,0);
		if(ans >= oo) ans = -1;
		printf("Case #%d: %lld\n",t,ans);
	}	
	
	return 0;
}
