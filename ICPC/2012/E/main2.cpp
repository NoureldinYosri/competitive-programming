//#include <cstdio>
//#include <vector>
//#include <algorithm>
//#define loop(i,n) for(int i = 0;i < (n);i++)
//#define range(i,a,b) for(int i = (a);i <= (b);i++)
//#define all(A) A.begin(),A.end()
//#define pb push_back
//#define mp make_pair
//#define sz(A) ((int)A.size())
//#define vi vector<int>
//#define vl vector<long long>
//#define vd vector<double>
//#define vp vector<pair<int,int> >
//#define ll long long
//#define pi pair<int,int>
//#define popcnt(x) __builtin_popcount(x)
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
//vi G[75];
//int n;
//vi vis;
//vi taken;
//
//vi greedy(){
//	vis = vi(n,0);
//	int ctr = 0;
//	vi ret;
//	while(ctr < n){
//		vi deg(n,0);
//		int best = 0,choice = 0;
//		loop(i,n) {
//			for(int v : G[i]) deg[i] += !vis[v];
//			deg[i] += !vis[i];
//			if(deg[i] > best){
//				best = deg[i];
//				choice = i;
//			}
//		}
//		ret.pb(choice);
//		ctr += best;
//		vis[choice] = 1;
//		for(int v : G[choice]) vis[v] = 1;
//	}
//	vis = vi(n,0);
//	taken = vi(n,0);
//	return ret;
//}
//
//bool impossible(int rem){
//	static vi aux;
//	aux.clear();
//	int need = 0;
//	loop(i,n) {
//		if(!taken[i]) aux.pb(sz(G[i]) + 1);
//		need += !vis[i];
//	}
////	sort(all(aux));
////	reverse(all(aux));
//	int s = 0;
//	loop(i,rem) s += aux[i];
//	return s < need;
//}
//
//
//int V[10],vm = 0;
//
//bool bt(int len){
//	if(!len){
//		bool all_covered = 1;
//		loop(i,n) all_covered &= vis[i] > 0;
//		return all_covered;
//	}
////	if(impossible(len)) return 0;
//	for(int u = !vm ? -1 : V[vm-1] + 1;u < n;u++){
//		V[vm++] = u;
//		for(int v : G[u]) vis[v]++;
//		vis[u]++;
//		if(bt(len - 1)) return 1;
//		vis[u]--;
//		for(int v : G[u]) vis[v]--;
//		vm--;
//	}
//	return 0;
//}
//
//int main(){
//	#ifdef HOME
//		freopen("in.in", "r", stdin);
//	#endif
//	for(int t = 1;scanf("%d",&n) == 1;t++){
//		char buffer[80];
//		loop(i,n) G[i].clear();
//		loop(i,n){
//			scanf("%s",buffer);
//			loop(j,n) if(buffer[j] == '1') G[i].pb(j);
//		}
//		vi ans = greedy();
//		vm = 0;
//		for(int len = 1;len < sz(ans) && !bt(len);len++);
//		if(!vm) ans = vi{V,V + vm};
//		printf("Case %d: %d",t,sz(ans));
//		for(int x : ans) printf(" %d",x + 1);
//		puts("");
//	}
//	return 0;
//}
