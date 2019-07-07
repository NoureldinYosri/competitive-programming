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

const int MAXM = 50*1000 + 10;
int n,m;
int fr[MAXM],to[MAXM];
vi G[MAXM];
int dfs_low[MAXM],dfs_num[MAXM],dfs_time;
bool articulation_vertex[MAXM];

void dfsBi(int u,int p,int dfs_root) {
	dfs_low[u] = dfs_num[u] = dfs_time++;
	int t = 0;
	for(int v : G[u]){
		if (dfs_num[v] == -1) {
			if (u == dfs_root) t++;
			dfsBi(v,u,dfs_root);
			if (u != dfs_root && dfs_low[v] >= dfs_num[u])
				articulation_vertex[u] = 1;
//			if (dfs_low[v] > dfs_num[u])
//				printf(" Edge (%d, %d) is a bridge\n", u, v);
			dfs_low[u] = min(dfs_low[u], dfs_low[v]);
		}
		else if (v != p)
			dfs_low[u] = min(dfs_low[u], dfs_num[v]);
	}
	if(u == dfs_root && t > 1) articulation_vertex[u] = 1;
}

void init(){
	memset(dfs_num,-1,sizeof dfs_num);
	memset(articulation_vertex,0,sizeof articulation_vertex);
	dfs_time = 0;
}

int vis[MAXM];
int siz[MAXM],id[MAXM];
int dfs(int u,int idx) {
	vis[u] = 1;
	id[u] = idx;
	siz[idx]++;
	int ret = 1;
	for(int v : G[u])
		if(!vis[v] && !articulation_vertex[v])
			ret += dfs(v,idx);
	return ret;
}


pair<int,ll> ans;

set<int> S[MAXM];

void work(){
	int q = 0;
	for(int u = 1;u <= n;u++)
		if(articulation_vertex[u]) {
			id[u] = q++;
		}
//	cerr << "#art = " << q << endl;
	if(q == 0) {
		ans = mp(2,n*(n-1LL)/2);
		return;
	}
	int qq = q;
	fill(vis,vis + n + 1,0);
	fill(siz,siz + n + 1,0);
	for(int u = 1;u <= n;u++)
		if(!vis[u] && !articulation_vertex[u])
			dfs(u,q++);
	loop(i,q) S[i].clear();
	range(u,1,n) if(articulation_vertex[u]){
		for(int v : G[u])
			S[id[v]].insert(id[u]);
	}
	int ctr = 0; ll cnt = 1;
	for(int i = qq;i < q;i++) {
		if(sz(S[i]) == 1){
			ctr ++;
			cnt *= siz[i];
		}
	}
	ans = mp(ctr,cnt);
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	for(int t = 1;scanf("%d",&m) == 1 && m;t++) {
		n = 1;
		loop(e,m) {
			scanf("%d %d",fr + e,to + e);
			n = max(n,max(fr[e],to[e]));
		}
		for(int i = 1;i <= n;i++)
			G[i].clear();
		loop(e,m) {
			int a = fr[e],b = to[e];
			G[a].pb(b);
			G[b].pb(a);
		}
		init();
		dfsBi(1,0,1);
		work();
		printf("Case %d: %d %lld\n",t,ans.xx,ans.yy);
	}
	return 0;
}
