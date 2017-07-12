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

const int MAX = 100*1000 + 10;
vi G[MAX],rG[MAX],content[MAX];
int n,m;
int vis[MAX],ord[MAX],dfs_time;
int out_deg[MAX],scc_id[MAX];

void dfs(int u){
	if(vis[u]) return;
	vis[u] = 1;
	for(int v : G[u]) dfs(v);
	ord[dfs_time++] = u;
}

void extract(int u,int id){
	scc_id[u] = id;
	vis[u] = 1;
	content[id].pb(u);
	for(int v : rG[u])
		if(!vis[v])
			extract(v,id);
}

bool solve(){
	if(scanf("%d %d",&n,&m) != 2) return 0;
	range(i,1,n) G[i].clear(),rG[i].clear();
	loop(i,n+1) content[i].clear();
	memset(vis,0,sizeof vis);
	dfs_time = 0;
	while(m--){
		int a,b; scanf("%d %d",&a,&b);
		G[a].pb(b);
		rG[b].pb(a);
	}
	range(i,1,n) dfs(i);
	memset(vis,0,sizeof vis);
	int ctr = 0;
	loop(i,n) if(!vis[ord[n-1-i]]) {
		extract(ord[n-1-i],ctr);
//		print(content[ctr],int);
		++ctr;
	}

	loop(i,ctr) {
		vi tmp;
		for(int u : content[i])
			for(int v : G[u])
				if(scc_id[v] != i)
					tmp.pb(scc_id[v]);
		sort(all(tmp));
		tmp.resize(unique(all(tmp)) - tmp.begin());
		out_deg[i] = sz(tmp);
	}
	vi out;
	loop(i,ctr){
		if(out_deg[i] == 0){
			for(int u : content[i])
				out.pb(u);
		}
	}
	sort(all(out));
	loop(i,sz(out)) printf("%d%c",out[i]," \n"[i==sz(out)-1]);
	return 1;
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
		freopen("out.out", "w", stdout);
	#endif
	while(solve());
	return 0;
}
