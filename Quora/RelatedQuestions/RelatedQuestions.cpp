#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define print(A,t) cout << #A << ": "; copy(all(A),ostream_iterator<t>(cout," " )); cout << endl
#define pi pair<int,int>
#define point pi
#define vi vector<int>
#define ll long long
#define pl pair<ll,ll>
#define pre() cin.tie(0),cout.tie(0),ios_base::sync_with_stdio(0)
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define prp(p) cout << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cout << #A << ": "; copy(A,A + n,ostream_iterator<t>(cout," " )); cout << endl
using namespace std;


int T[1 << 20],N;
vi G[1 << 20];
double dp[1 << 20];
vector<double> V[1 << 20];

double dfs1(int u,int p){
	int ctr = 0;
	for(int v : G[u]) ctr += v != p;
	dp[u] = T[u];
	loop(i,sz(G[u])){
		int v = G[u][i]; 
		if(v != p) {
			double t = dfs1(v,u);
			V[u][i] = t;		
			dp[u] += t/ctr;
		}
	}
	return dp[u];
}

void dfs2(int u,int p,double value){
	int ctr = max((int)sz(G[u]) - 1,1);
	double tmp = dp[u] = T[u];
	loop(i,sz(G[u]))
		if(G[u][i] == p) V[u][i] = value;
	loop(i,sz(G[u])) {
		dp[u] += V[u][i] / sz(G[u]);
		tmp += V[u][i]/ctr;
	}
	loop(i,sz(G[u]))
		if(G[u][i] != p){
			int v = G[u][i];			
			dfs2(v,u,tmp - V[u][i]/ctr);
		}
}

int main(){
	int a,b;	
	scanf("%d",&N);
	range(i,1,N) scanf("%d",T + i);
	loop(i,N - 1){
		scanf("%d %d",&a,&b);
		G[a].pb(b);
		G[b].pb(a);
		V[a].pb(b);
		V[b].pb(a);
	}
	int s = 1; 
	dfs1(1,0);
	dfs2(1,0,0);
	double t = dp[1];	
	range(i,1,N){
		cerr << i << " " << dp[i] << endl;
		double ti = dp[i];
		if(ti < t) {
			t = ti;
			s = i;
		}
	}
	printf("%d\n",s);
	return 0;
}
