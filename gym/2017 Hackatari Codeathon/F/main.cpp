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

const int MAXN = 1010;
const int MAX = MAXN*MAXN + 10,MAXLG = 21;
int A[MAXN][MAXN],m,n,N;
int dx[] = {0,1,0,-1},dy[] = {1,0,-1,0};
vi G[MAX];
int depth[MAX],cnt[MAX],siz[MAX],indeg[MAX],vis[MAX];

int dfs(int u,int d){
	depth[u] = d;
	siz[u] = 1;
	vis[u] = 1;
	int ret = d;
	for(int v : G[u])
		if(vis[v]) ret = min(ret,depth[v]);
		else{
			int t = dfs(v,d + 1);
			if(t >= d) cnt[u] += siz[v];
			ret = min(ret,t);
			siz[u] += siz[v];
		}
	return ret;
}

int main(){
	scanf("%d %d",&m,&n);
	
	range(i,1,m) range(j,1,n) {
		scanf("%d",&A[i][j]);
		N = max(N,A[i][j]);
	}	
	range(i,1,m) range(j,1,n) {
		int x = A[i][j];
		loop(k,4){
			int y = A[i + dx[k]][j + dy[k]];
			if(x == y) continue;
			G[x].pb(y);
			G[y].pb(x);
		}
	}
	range(u,0,N){
		sort(all(G[u]));
		G[u].resize(unique(all(G[u])) - G[u].begin());
//		for(int v : G[u]) cerr << u << " " << v << endl;
	}

	dfs(0,0);
	range(i,1,N) printf("%d%c",cnt[i]," \n"[i==N]);
//	prArr(cnt+1,N,int);
	return 0;
}
