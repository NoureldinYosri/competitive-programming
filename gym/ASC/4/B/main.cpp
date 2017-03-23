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

const int MAX = 100'010;
vi E[MAX];
int fr[MAX],to[MAX],n,m;
int dfs_num[MAX],dfs_low[MAX],dfs_time;
int dont[MAX];
vi ans;

void dfs(int u,int p) {
	dfs_low[u] = dfs_num[u] = dfs_time++;
	map<int,int> M;
	for(int e : E[u]){
		int v = fr[e] + to[e] - u;
		if(M.find(v) != M.end()) dont[e] = dont[M[v]] = 1;
		else M[v] = e; 
	}	
	for(int e : E[u]){
		int v = fr[e] + to[e] - u;
		if (dfs_num[v] == -1) { 
			dfs(v,u);
			if (dfs_low[v] > dfs_num[u] && !dont[e])
				ans.pb(e);
			dfs_low[u] = min(dfs_low[u], dfs_low[v]);
		} 
		else if (v != p)
			dfs_low[u] = min(dfs_low[u], dfs_num[v]);
		
	}
}

int main(){
	freopen("bridges.in","r",stdin);
	freopen("bridges.out","w",stdout);
	scanf("%d %d",&n,&m);
	range(e,1,m){
		scanf("%d %d",fr + e,to + e);
		E[fr[e]].pb(e);
		E[to[e]].pb(e);
	}
	memset(dfs_num,-1,sizeof dfs_num);
	dfs(1,0);
	printf("%d\n",sz(ans));
	sort(all(ans));
	for(int e : ans) printf("%d ",e);
	puts("");
//	print(ans,int);	
	
	
	return 0;
}
