//#pragma GCC optimize ("O3")
//#include <bits/stdc++.h>
//#define loop(i,n) for(int i = 0;i < (n);i++)
//#define range(i,a,b) for(int i = (a);i <= (b);i++)
//#define all(A) A.begin(),A.end()
//#define pb push_back
//#define mp make_pair
//#define sz(A) ((int)A.size())
//#define vi vector<int>
//#define vd vector<double>
//#define vp vector<pair<int,int> >
//#define ll long long
//#define pi pair<int,int>
//#define popcnt(x) __builtin_popcountll(x)
//#define LSOne(x) ((x) & (-(x)))
//#define xx first
//#define yy second
//#define PQ priority_queue
//#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
//#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
//#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
//#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
//#define what_is(x) cerr << #x << " is " << x << endl
//#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
//using namespace std;
//
//const int MAXN = 100*1000 + 10,MAXD = 50 + 2;
//vi G[MAXN],rG[MAXN];
//int n,m,D,N;
//int vis[MAXN];
//vi ord;
//vi C[MAXN];
//vp CG[MAXN];
//int SCCid[MAXN];
//char grid[MAXN][MAXD];
//int dp[MAXN][MAXD];
//
//void dfs(int u) {
//	if(vis[u]) return ;
//	vis[u] = 1;
//	for(int v : G[u])
//		dfs(v);
//	ord.push_back(u);
//}
//
//void getSCC(int u,int id) {
//	if(vis[u]) return;
//	SCCid[u] = id;
//	vis[u] = 1;
//	C[id].push_back(u);
//	for(int v : rG[u])
//		getSCC(v,id);
//}
//
//
//
//int Rev[MAXN][MAXD];
//int For[MAXN][MAXD];
//int psi[MAXN][MAXD];
//
//void dfs(int u,int d,int id,bool sure,int vis[MAXN][MAXD],vi *G) {
//	d %= D;
//	if(SCCid[u] != id) return;
//	if(vis[u][d]) return;
//	vis[u][d] = sure;
//	for(int v : G[u])
//		dfs(v,d+1,id,1,vis,G);
//}
//
//int getKing(int id) {
//	if(SCCid[1] == id) return 1;
//	return C[id][0];
//}
//
//int solve(int u,int d) {
//	d %= D;
//	int & ret = dp[u][d];
//	if(ret != -1) return ret;
//	int id = SCCid[u],king = getKing(id);
//	if(u != king) {
//		ret = 0;
//		loop(i,D){
//			if(Rev[u][i])
//				ret = max(ret,solve(king,d + i));
//		}
//		return ret;
//	}
//	ret = 0;
//	for(pi e : CG[id]) {
//		int f = e.xx,t = e.yy;
//		loop(i,D) if(For[f][i]) ret = max(ret,solve(t,i + d + 1));
//	}
//	ret += psi[id][d];
////	cerr << u << " " << d << "(" << king << ")" << ": " << ret << endl;
//	return ret;
//}
//
//
//
//int main(int argc,char **argv){
//#ifdef HOME
//	freopen("in.in","r",stdin);
//#endif
//	scanf("%d %d %d",&n,&m,&D);
//	loop(i,m){
//		int a,b;
//		scanf("%d %d",&a,&b);
//		G[a].push_back(b);
//		rG[b].push_back(a);
//	}
//	for(int i = 1;i <= n;i++)
//		dfs(i);
//	reverse(all(ord));
//	memset(vis,0,sizeof vis);
//	for(int u : ord)
//		if(!vis[u])
//			getSCC(u,++N);
//
//	for(int i = 1;i <= n;i++)
//		scanf("%s",grid[i]);
//	for(int i = 1;i <= N;i++){
//		for(int u : C[i]) {
//			for(int v : G[u]) {
//				if(SCCid[v] == i) continue;
//				CG[i].push_back(mp(u,v));
//			}
//		}
//		int king = getKing(i);
//		int sure = (king == 1) || (sz(C[i]) == 1);
//		dfs(king,0,i,sure,For,G);
//		dfs(king,0,i,0,Rev,rG);
//		for(int s = 0;s < D;s++) {
//			for(int u : C[i]) {
//				bool f = 0;
//				loop(d,D) if(For[u][d]) {
//					int k = (s + d)%D;
//					f |= grid[u][k] == '1';
//				}
//				psi[i][s] += f;
//			}
//		}
//	}
//	memset(dp,-1,sizeof dp);
//	printf("%d\n",solve(1,0));
//	return 0;
//}
