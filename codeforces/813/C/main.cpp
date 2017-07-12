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

const int MAX = 200*1000 + 10,MAXLG = 20;
vi G[MAX];
int P[MAX][MAXLG],inTime[MAX],outTime[MAX],dfs_time,n,x;
int depth[MAX];

void dfs(int u,int p){
	inTime[u] = dfs_time++;
	depth[u] = depth[p] + 1;
	P[u][0] = p;
	loop(i,MAXLG - 1) P[u][i + 1] = P[P[u][i]][i];
	for(int v : G[u]) if(v != p) dfs(v,u);
	outTime[u] = dfs_time - 1;
}

bool in_subtree(int a,int b){
	if(!a) return 1;
	if(!b) return 0;
	return inTime[a] <= inTime[b] && inTime[b] <= outTime[a];
}

int lca(int a,int b){
	for(int k = MAXLG - 1;k >= 0;k--){
		if(depth[a] > depth[b]) swap(a,b);
		if(in_subtree(a,b)) return a;
		if(k && in_subtree(P[b][k],a)) continue;
		b = P[b][k];
		k++;
	}
	if(depth[a] > depth[b]) swap(a,b);
	assert(in_subtree(a,b));
	return (depth[a] < depth[b]) ? a : b;
}

int dist(int a,int b){
	int p = lca(a,b);
	return depth[a] + depth[b] - 2*depth[p];
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d",&n,&x);
	loop(i,n-1){
		int a,b; scanf("%d %d",&a,&b);
		G[a].pb(b);
		G[b].pb(a);
	}
	dfs(1,0);
	int ans = 0;
	range(i,1,n) {
		int cx = lca(x,i);
		int tmp = 0;
		if(depth[x] - depth[cx] < depth[cx]-1) {
			tmp = 2*depth[i] - 2;
		}
	//	cerr << i << " " << cx << " -> " << tmp ;
	//	if(x == cx) cerr << " stay put" << endl;
	//	else cerr << " " << depth[x] - depth[cx] << " " << depth[cx] << " " << endl;
		ans = max(ans,tmp);
	}
	cout << ans << endl;
	return 0;
}
