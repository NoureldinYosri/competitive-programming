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


const int MAX = 100*1000 + 110,MAXLG = 20;
int dfs_low[MAX],dfs_num[MAX],dfs_time;
vi G[MAX],nG[MAX];
vi ST;
vi content[MAX];
int id[MAX],comp_cnt;
int n,m,k;
int depth[MAX],dfs_in[MAX],dfs_out[MAX];
int P[MAX][MAXLG];

void extract(int cnt){
	bool done_work = 0;
	++comp_cnt;
	while(!ST.empty() && cnt--) {
		int u = ST.back();
		ST.pop_back();
		id[u] = comp_cnt;
		content[id[u]].pb(u);
		done_work = 1;
	//	cerr << u << " is in " << id[u] << endl;
	}
//	if(done_work) cerr << endl;
	comp_cnt -= !done_work;
}

void dfsBi(int u,int p,int dfs_root) {
	ST.pb(u);
	dfs_low[u] = dfs_num[u] = dfs_time++;
	for(int v : G[u]){
		if (dfs_num[v] == -1) {
			int cur_siz = sz(ST);
			dfsBi(v,u,dfs_root);
			if (dfs_low[v] > dfs_num[u]){
				//cerr << u << " " << v << " is bridge " << endl;
				extract(sz(ST) - cur_siz);
			}
			dfs_low[u] = min(dfs_low[u], dfs_low[v]);
		}
		else if (v != p)
			dfs_low[u] = min(dfs_low[u], dfs_num[v]);
	}
	if(u == dfs_root) extract(sz(ST));
}

void init(){
	memset(dfs_num,-1,sizeof dfs_num);
	dfs_time = 0;
}

void get_tree(){
	range(i,1,comp_cnt){
		for(int u : content[i]) {
			for(int v : G[u]) if(id[v] != i) {
				nG[i].pb(id[v]);
			}
		}
	}
}

void dfs(int u,int p){
	depth[u] = depth[p] + 1;
	dfs_in[u] = dfs_time++;
	P[u][0] = p;
	loop(i,MAXLG-1) P[u][i+1] = P[P[u][i]][i];
	for(int v : nG[u]) if(v != p) dfs(v,u);
	dfs_out[u] = dfs_time - 1;
 }

bool inSubTree(int a,int b){
	return dfs_in[b] <= dfs_in[a] && dfs_in[a] <= dfs_out[b];
}

int lca(int a,int b){
	if(depth[a] > depth[b]) swap(a,b);
	if(inSubTree(b,a)) return a;
	int k = MAXLG - 1;
	while(a != b){
		if(depth[a] > depth[b]) swap(a,b);
		while(k && inSubTree(a,P[b][k])) k--;
		b = P[b][k];
	}
	return a;
}


int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	init();
	scanf("%d %d",&n,&m);
	loop(i,m){
		int a,b; scanf("%d %d",&a,&b);
		G[a].pb(b);
		G[b].pb(a);
	}
	range(i,1,n) if(dfs_num[i] == -1) {
		dfsBi(i,0,i);
		break;
	}
	get_tree();
	dfs_time = 0;
	dfs(1,0);
	dfs_out[0] = comp_cnt;
	scanf("%d",&k);
	loop(i,k){
		int a,b; scanf("%d %d",&a,&b);
		a = id[a],b = id[b];
		printf("%d\n",depth[a] + depth[b] - 2*depth[lca(a,b)]);
	}
	return 0;
}
