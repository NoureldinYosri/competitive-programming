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

const int MAX = 200'000 + 10,MAXK = 5;
vi G[MAX];
ll sum[MAX][MAXK],cnt[MAX][MAXK];
ll ans = 0;
int n,K;

void dfs(int u,int p){
	cnt[u][0]++;
	ll tmp = 0;
	for(int v : G[u]) if(v != p){
		dfs(v,u);
		for(int k = 0;k < K;k++)
			for(int k2 = 0;k2 < K;k2++){
				ll tmp2 = 0;
				int t = k2 + 1; t = (t == K) ? 0 : t;
				tmp2 += (sum[u][k] - cnt[u][k]*k)/K * cnt[v][k2];
				tmp2 += (sum[v][k2] + cnt[v][k2] - cnt[v][k2]*t)/K * cnt[u][k];
				tmp2 += ((k + t + K - 1)/K) * cnt[u][k]*cnt[v][k2];
				tmp += tmp2;
			}
		for(int k = 0;k < K;k++){
			sum[u][(k + 1)%K] += sum[v][k] + cnt[v][k];
			cnt[u][(k + 1)%K] += cnt[v][k];
		}
	}
	ans += tmp;
}

int main(){
	scanf("%d %d",&n,&K);
	loop(i,n-1){
		int a,b; scanf("%d %d",&a,&b);
		G[a].pb(b);
		G[b].pb(a);
	}	
	dfs(1,0);	
	cerr << ans << endl;
	cout << ans << endl;
	return 0;
}
