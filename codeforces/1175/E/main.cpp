#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
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
using namespace std;

const int MAX = 500*1000 + 10,MAXLG = 20;
int R[MAX];
vi G[MAX];
int ID[MAX],dfs_in[MAX],dfs_out[MAX],dfs_time;
int depth[MAX];
bool vis[MAX];
int P[MAX][MAXLG];


void dfs(int u,bool isRoot,int i) {
	if(isRoot) {
		loop(k,MAXLG) P[u][k] = -1;
	}
	vis[u] = 1;
	ID[u] = i;
	dfs_in[u] = dfs_time++;
	for(int v : G[u]){
		depth[v] = depth[u] + 1;
		P[u][0] = v;
		loop(k,MAXLG-1) {
			int t = P[u][k];
			if(t == -1) P[u][k + 1] = -1;
			else P[u][k+1] = P[t][k];
		}
		dfs(v,0,i);
	}
	dfs_out[u] = dfs_time;
}



int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	memset(R,-1,sizeof R);
	int n,m; scanf("%d %d",&n,&m);
	loop(i,n) {
		int l,r; scanf("%d %d",&l,&r);
		R[l] = max(R[l],r);
		R[r] = max(R[r],r);
	}
	for(int i = 1;i < MAX;i++)
		R[i] = max(R[i],R[i - 1]);
	for(int i = 0;i < MAX;i++) {
		if(R[i] > i)
			G[R[i]].push_back(i);
	}
	int id = 0;
	for(int i = MAX-1;i >= 0;i--)
		if(!vis[i]) {
			dfs(i,1,id++);
		}
	loop(i,m) {
		int x,y; scanf("%d %d",&x,&y);
		int ctr = 0;
		bool f = 1;
		if(x == y) {
			if(R[x] >= x) {
				ctr = 1;
				f = 1;
			}
			else {
				f = 0;
				ctr = -1;
			}
		}
		else {

		}
		if(!f) ctr = -1;
		printf("%d\n",ctr);
	}
	return 0;
}
