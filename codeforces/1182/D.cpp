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
//const int MAX = 100*1000 + 10;
//int deg[MAX];
//vi G[MAX];
//int n;
//int f[MAX];
//int P[MAX];
//
//bool dfs(int u,int p,int d){
//	if(P[u] != -1 && P[u] != p) return 0;
//	int k = sz(G[u]);
//	if(f[d] != -1 && f[d] != k) return 0;
//	f[d] = k;
//	for(int v : G[u])
//		if(v != p)
//			if(!dfs(v,u,d + 1))
//				return 0;
//	return 1;
//}
//
//
//int solve() {
//	range(u,1,n) P[u] = -1;
//	for(int u = 1;u <= n;u++) {
//		sort(all(G[u]),[](const int & a,const int & b) {
//			return deg[a] < deg[b];
//		});
//		int D[] = {deg[G[u][0]],deg[G[u].back()]};
//		if(D[0] == D[1]) {
//			continue;
//		}
//		int ctr[] = {0,0};
//		for(int v : G[u]) {
//			loop(i,2) if(deg[v] == D[i]) ctr[i]++;
//		}
//		if(ctr[0] + ctr[1] != deg[u]) return 0;
//		if(ctr[0] != 1 && ctr[1] != 1) return 0;
//		if(deg[u] == 2) {
//			continue;
//		}
//		else {
//			P[u] = (ctr[0] == 1) ? G[u][0] : G[u].back();
//		}
//	}
//
//	for(int u = 1;u <= n;u++){
//		if(P[u] != -1) continue;
//		memset(f,-1,sizeof f);
////		cerr << "Cand " << u << endl;
//		if(dfs(u,0,0))
//			return u;
//	}
//	return -1;
//}
//
//int main(int argc,char **argv){
//#ifdef HOME
//	freopen("in.in","r",stdin);
//#endif
//	scanf("%d",&n);
//	loop(e,n-1) {
//		int a,b; scanf("%d %d",&a,&b);
//		G[a].push_back(b);
//		G[b].push_back(a);
//		deg[a]++;
//		deg[b]++;
//	}
//
//	cout << solve() << endl;
//	return 0;
//}
