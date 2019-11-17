//#include <bits/stdc++.h>
//#define loop(i,n) for(int i = 0;i < (n);i++)
//#define all(A) A.begin(),A.end()
//#define pb push_back
//#define mp make_pair
//#define sz(A) ((int)A.size())
//typedef std::vector<int> vi;
//typedef std::pair<int,int> pi;
//typedef std::vector<pi> vp;
//typedef long long ll;
//#define popcnt(x) __builtin_popcount(x)
//#define LSOne(x) ((x) & (-(x)))
//#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
//#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
//#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
//#define what_is(x) cerr << #x << " is " << x << endl
//#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
//const double PI = acos(-1);
//template<class A,class B>
//std::ostream& operator << (std::ostream& st,const std::pair<A,B> p) {
//	st << "(" << p.first << ", " << p.second << ")";
//	return st;
//}
//#define tc() int T; scanf("%d",&T); for(int t = 1;t <= T;t++)
//using namespace std;
//
//const int MAX = 200*1000 + 10;
//int dfs_low[MAX],dfs_num[MAX],dfs_time;
//vi G[MAX];
//vi ST;
//int m,n,M;
//vi content[MAX],adj[MAX];
//int id[MAX];
//ll W[MAX],S[MAX];
//
//void extract(int root){
//	while(!ST.empty()) {
//		int u = ST.back(); ST.pop_back();
//		content[M].push_back(u);
//		id[u] = M;
//		if(u == root) break;
//	}
//	if(!content[M].empty()) {
////		print(content[M],int);
//		M++;
//	}
//}
//
//void dfsBi(int u,int p,int dfs_root) {
//	ST.push_back(u);
//	dfs_low[u] = dfs_num[u] = dfs_time++;
//	int t = 0;
//	for(int v : G[u]){
//		if (dfs_num[v] == -1) {
//			if (u == dfs_root) t++;
//			dfsBi(v,u,dfs_root);
//			if (dfs_low[v] > dfs_num[u])
//				extract(v);
//			dfs_low[u] = min(dfs_low[u], dfs_low[v]);
//		}
//		else if (v != p)
//			dfs_low[u] = min(dfs_low[u], dfs_num[v]);
//	}
//}
//
//void init(){
//	memset(dfs_num,-1,sizeof dfs_num);
//	dfs_time = 0;
//}
//
//pair<ll,bool> dp[MAX];
//
//pair<ll,bool> dfs(int u,int p) {
//	ll res = S[u];
//	bool canReturn = sz(content[u]) > 1;
//	for(int v : adj[u]) if(v != p){
//		pair<ll,bool> tmp = dfs(v,u);
//		if(tmp.second) {
//			res += tmp.first;
//			canReturn = 1;
//		}
//	}
////	for(int t : content[u]) cout << t << " ";
////	cout << ": " << res << " " << canReturn << endl;
//	return dp[u] = mp(res,canReturn);
//}
//
//ll solve(int u,int p) {
//	ll sum = dp[u].first;
//	ll best = sum;
//	for(int v : adj[u]) if(v != p){
//		ll tmp = 0;
//		if(dp[v].second) {
//			tmp = sum - dp[v].first;
//			tmp += solve(v,u);
//		}
//		else {
//			tmp = sum + solve(v,u);
//		}
//		best = max(best,tmp);
//	}
//	return best;
//}
//
//int main(){
//#ifdef HOME
//	freopen("in.in", "r", stdin);
//#endif
//	scanf("%d %d",&n,&m);
//	loop(i,n) scanf("%lld",W + i);
//	loop(e,m){
//		int a,b; scanf("%d %d",&a,&b);
//		a--,b--;
//		G[a].push_back(b);
//		G[b].push_back(a);
//	}
//	int root; scanf("%d",&root); root--;
//	init();
//	loop(i,n) if(dfs_num[i] == -1) {
//		dfsBi(i,-1,i);
//		extract(i);
//	}
//	loop(i,M) {
//		for(int u : content[i]){
//			for(int v : G[u]) {
//				int j = id[v];
//				if(i == j) continue;
//				adj[i].push_back(j);
//			}
//			S[i] += W[u];
//		}
//		sort(all(adj[i]));
//		adj[i].resize(unique(all(adj[i])) - adj[i].begin());
//	}
//	root = id[root];
//	dfs(root,-1);
//	cout << solve(root,-1) << endl;
//	return 0;
//}
