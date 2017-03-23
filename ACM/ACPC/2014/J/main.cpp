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

const int MAXN = 1001;
const int MAXK = 101;
vp E[MAXN];
ll dp[MAXN][MAXK];
int n,K; 

void dfs(int u){
	ll aux [MAXK];
	for(int ik = 0;ik <= K;ik++) dp[u][ik] = -(ik > 1) * (1LL << 61);
	
	for(auto e : E[u]){
		int v = e.xx; ll w = e.yy;
		dfs(v);
		for(int ik = 0;ik <= K;ik++) aux[ik] = -(1LL << 61);
		for(int ik = 0;ik <= K;ik++)
			for(int k = 0;k <= ik;k++){
				ll t = dp[u][ik - k] + dp[v][k] + 2*min(K - k + 1,k)*w;
				aux[ik] = max(aux[ik],t);
			}
		for(int ik = 0;ik <= K;ik++) dp[u][ik] = aux[ik];
	}
}

int main(){
	int T; scanf("%d",&T);
	range(t,1,T){
		scanf("%d %d",&n,&K);
		range(u,1,n) E[u].clear();
		range(u,2,n){
			int p,w; scanf("%d %d",&p,&w);
			E[p].pb(mp(u,w));
		}
		dfs(1);		
		printf("Case %d: %lld\n",t,dp[1][K]);
	}
	
	
	return 0;
}
