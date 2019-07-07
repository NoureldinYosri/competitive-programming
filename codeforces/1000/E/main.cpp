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

const int MAXV = 300*1000 + 10,MAXE = MAXV;
int dfs_low[MAXV],dfs_num[MAXV],dfs_time;
vi G[MAXV],nG[MAXV];
int n,m;
int ID[MAXV],id_count;

vi ST;

void extract(int u) {
	int v = 0;
	++id_count;
	while(v != u) {
		v = ST.back();
		ST.pop_back();
		ID[v] = id_count;
	}
}

void dfsBi(int u,int p,int dfs_root) {
	dfs_low[u] = dfs_num[u] = dfs_time++;
	int t = 0;
	ST.push_back(u);
	for(int v : G[u]){
		if (dfs_num[v] == -1) {
			if (u == dfs_root) t++;
			dfsBi(v,u,dfs_root);
//			if (u != dfs_root && dfs_low[v] >= dfs_num[u])
//				articulation_vertex[u] = 1;
			if (dfs_low[v] > dfs_num[u]){
				extract(v);
			}
			dfs_low[u] = min(dfs_low[u], dfs_low[v]);
		}
		else if (v != p)
			dfs_low[u] = min(dfs_low[u], dfs_num[v]);
	}
//	if(u == dfs_root && t > 1) articulation_vertex[u] = 1;
	if(u == dfs_root) extract(u);
}

void init(){
	memset(dfs_num,-1,sizeof dfs_num);
	dfs_time = 0;
}

int getDiameter(int u,int & d) {
	dfs_num[u] = 1;
	int mx = 0,mx2 = 0;
	for(int v : nG[u]) {
		if(dfs_num[v]) continue;
		int len = getDiameter(v,d) + 1;
		mx2 = max(mx2,len);
		if(mx2 > mx) swap(mx,mx2);
	}
	d = max(d,mx + mx2);
	return mx;
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	scanf("%d %d",&n,&m);
	loop(e,m) {
		int a,b; scanf("%d %d",&a,&b);
		G[a].push_back(b);
		G[b].push_back(a);
	}
	init();
	for(int u = 1;u <= n;u++)
		if(dfs_num[u] == -1)
			dfsBi(u,0,u);
	for(int u = 1;u <= n;u++) {
		for(int v : G[u])
			if(ID[v] != ID[u])
				nG[ID[u]].push_back(ID[v]);
	}
	for(int u = 1;u <= id_count;u++) {
		sort(all(nG[u]));
		nG[u].resize(unique(all(nG[u])) - nG[u].begin());
	}
	memset(dfs_num,0,sizeof dfs_num);
	int ans = 0;
	for(int u = 1;u <= id_count;u++)
		if(dfs_num[u] == 0){
			int res = 0;
			getDiameter(u,res);
			ans = max(ans,res);
		}
	cout << ans << endl;
	return 0;
}
