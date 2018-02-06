//#pragma GCC optimize ("O3")
//#include <bits/stdc++.h>
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
//const double PI = acos(-1);
//using namespace std;
//
//const int MAX = 300*1000 + 10,mod = 1e9 + 7;
//vi G[MAX];
//int val[MAX],n,m;
//
//int add(int a,int b) {
//	a += b;
//	if(a >= mod) a -= mod;
//	if(a < 0) a += mod;
//	return a;
//}
//
//void dfs(int u,int p,int k,int a,int b) {
//	if(k < 0) return ;
//	val[u] = add(val[u],a);
//	a = add(a,b);
//	swap(a,b);
//	for(int v : G[u]) if(v != p) dfs(v,u,k-1,a,b);
//}
//
//void clean(){
//	range(i,1,n) G[i].clear(),val[i] = 0;
//}
//
//int main(){
//	#ifdef HOME
//		freopen("in.in", "r", stdin);
//	#endif
//	int T; scanf("%d",&T);
//	range(t,1,T) {
//		scanf("%d %d",&n,&m);
//		loop(e,n-1) {
//			int a,b; scanf("%d %d",&a,&b);
//			G[a].pb(b);
//			G[b].pb(a);
//		}
//		loop(i,m) {
//			int type ,v; scanf("%d %d",&type,&v);
//			if(type == 1) {
//				int k,a,b; scanf("%d %d %d",&k,&a,&b);
//				dfs(v,0,k,a,b);
////				prArr(val+1,n,int);
//			}
//			else printf("%d\n",val[v]);
//		}
//		clean();
//	}
//	return 0;
//}
