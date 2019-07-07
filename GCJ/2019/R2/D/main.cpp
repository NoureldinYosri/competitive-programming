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

int M;
int A[1 << 20],B[1 << 20];
ll G[1 << 20];
int vis[1 << 20],belongsToCycle[1 << 20];
int dfs_in[1 << 20],dfs_time;

int dfs(int u) {
	if(G[u] == 0) return -1;
	if(vis[u] == 1) {
		return u;
	}
	if(vis[u] == 2) return -1;
	vis[u] = 1;
	dfs_in[u] = dfs_time++;
	int a = dfs(A[u]),b = dfs(B[u]);
	if(a == -1) swap(a,b);
	if(b != -1 && dfs_in[b] < dfs_in[a]) a = b;
	if(a != -1) belongsToCycle[u] = 1;
	if(a == u) a = -1;
	vis[u] = 2;
	return a;
}

void flood(int u) {
	if(vis[u]) return;
	belongsToCycle[u] = 1;
	vis[u] = 1;
	flood(A[u]);
	flood(B[u]);
}

vi revAdj[1 << 20];
bool isImportant[1 << 20];
int inDeg[1 << 20];
int mod = 1000000007;

void flood2(int u) {
	if(vis[u]) return;
	vis[u] = 1;
	isImportant[u] = 1;
	for(int v : revAdj[u])
		flood2(v);
}

bool solve(ll & res){
	dfs_time = 0;
	fill(vis,vis + M,0);
	fill(belongsToCycle,belongsToCycle + M,0);
	loop(i,M) if(!vis[i]) dfs(i);
	fill(vis,vis + M,0);
	loop(i,M) if(!vis[i] && belongsToCycle[i]) flood(i);
	if(belongsToCycle[0]) return 0;

	loop(i,M) revAdj[i].clear();
	loop(i,M) revAdj[A[i]].push_back(i),revAdj[B[i]].push_back(i);
	loop(i,M) inDeg[i] = sz(revAdj[i]);
	fill(vis,vis + M,0);
	flood2(0);


	queue<int> q;
	loop(i,M) if(isImportant[i] && inDeg[i] == 0) q.push(i);
	res = 0;
	while(!q.empty()) {
		int u = q.front(); q.pop();
		if(u == 0) break;
		vi aux{A[u],B[u]};
		for(int v : aux) {
			if(!isImportant[v]) continue;
			G[v] = (G[v] + G[u])%mod;
			inDeg[v]--;
			if(inDeg[v] == 0) q.push(v);
		}
	}
	res = G[0];
	return 1;
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	int T; scanf("%d",&T);
	range(t,1,T) {
		scanf("%d",&M);
		loop(i,M) scanf("%d %d",A + i,B + i),A[i]--,B[i]--;
		loop(i,M) scanf("%lld",G + i);
		printf("Case #%d: ",t);
		ll res;
		if(!solve(res)) puts("UNBOUNDED");
		else printf("%lld\n",res);
	}
	return 0;
}
