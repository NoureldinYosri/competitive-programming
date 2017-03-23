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


const int MAX = (100000 + 10) << 1,MXLG = 20;
//nodes
vi E[MAX];
int depth[MAX],id[MAX],n,deg[MAX];
// queries
int type[MAX],X[MAX],Y[MAX],q;
// documents
int owner[MAX],inTime[MAX],m;
// sparse table
int order[MAX],ST[MAX][MXLG],lst[MAX],lg[MAX],dfs_time;
// binary raise
int P[MAX][MXLG],mxEdge[MAX][MXLG];


int argmin(int a,int b){
	return (depth[a] < depth[b]) ? a : b;
}

void buildST(){
	lg[0] = -1; loop(i,MAX-1) lg[i + 1] = lg[i] + ((i+1) == LSOne((i+1)));
	loop(i,dfs_time) ST[i][0] = order[i];
	loop(k,MXLG-1){
		loop(i,dfs_time){
			int j = i + (1 << k);
			if(j >= dfs_time) j = i;
			ST[i][k + 1] = argmin(ST[i][k],ST[j][k]);
		}
	}
}

void dfs(int u,int e,int idx,int h = 0){
	depth[u] = h; id[u] = idx;
	P[u][0] = Y[e]; mxEdge[u][0] = e;
	loop(i,MXLG-1){
		P[u][i + 1] = P[P[u][i]][i];
		mxEdge[u][i+1] = max(mxEdge[u][i],mxEdge[P[u][i]][i]);
	}
	order[dfs_time] = u; lst[u] = dfs_time; dfs_time++;
	for(int e : E[u]) {
		dfs(X[e],e,idx,h + 1);
		order[dfs_time] = u; lst[u] = dfs_time; dfs_time++;
	}
}

int lca(int a,int b){
	if(a == b) return a;
	a = lst[a],b = lst[b];
	if(a > b) swap(a,b);
	int l = lg[b - a + 1];
	return argmin(ST[a][l],ST[b - (1 << l) + 1][l]);
}

int getMax(int u,int v){
	int d = depth[v] - depth[u];
	int mx = 0,k = 0;
	while(d > 0){
		int t = LSOne(d);
		while(t != (1 << k)) k++;
		mx = max(mx,mxEdge[v][k]);
		v = P[v][k];
		d ^= t;
	}
	return mx;
}

int main(){
	scanf("%d %d",&n,&q);
	range(i,1,q){
		scanf("%d %d",type + i,X + i);
		if(type[i] != 2) scanf("%d",Y + i);
		if(type[i] == 1) E[Y[i]].pb(i),deg[X[i]]++;
	}
	int k = 0;
	range(i,1,n) if(!deg[i]) dfs(i,0,++k);
	buildST();
	m = 1;
	range(i,1,q){
		if(type[i] == 1) continue;
		else if(type[i] == 2){
			owner[m] = X[i];
			inTime[m] = i;
			m++;
		}
		else{
			int u = X[i],v = owner[Y[i]];
			if(Y[i] > m || id[u] != id[v] || lca(u,v) != u || getMax(u,v) > inTime[Y[i]]) puts("NO");
			else puts("YES");		
		}
	}
}
