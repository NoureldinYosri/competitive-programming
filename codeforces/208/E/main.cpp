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

const int MAX = 1e5 + 1e2;
vi G[MAX];
int depth[MAX],in[MAX],out[MAX],dfs_time,n;
vi L[MAX];
int P[MAX][20];

void dfs(int u,int p,int d){
	depth[u] = d;
	in[u] = dfs_time++;	
	L[d].pb(in[u]);
	P[u][0] = p;
	loop(i,19) P[u][i + 1] = P[P[u][i]][i];
	for(int v : G[u]) if(v != p) dfs(v,u,d+1);
	out[u] = dfs_time-1;
}

int getParent(int u,int d){
	int k = 0;
	while(d){
		int t = LSOne(d);
		while(t != (1 << k)) k++;
		u = P[u][k];
		d ^= t;
	}
	return u;
}

int main(){
	scanf("%d",&n);
	range(i,1,n) {
		int p; scanf("%d",&p);
		G[p].pb(i);
	}	
	dfs(0,0,0);
	int m,u,d; scanf("%d",&m);
	loop(i,m){
		scanf("%d %d",&u,&d);
		int ans = 0;
		if(d < depth[u]){
			int p = getParent(u,d);
			d = depth[u];
			auto t = upper_bound(all(L[d]),out[p]);
			auto v = lower_bound(all(L[d]),in[p]);
			ans = t - v - 1;	
		}
		printf("%d%c",ans," \n"[i==m-1]);
	}
	return 0;
}
