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
//const int MAXN = 5000+1,MAXM = 20000 + 1;
//int n,m;
//int A[MAXM],B[MAXM];
//
//deque<int> to[MAXN];
//int cnt[MAXN];
//int J[MAXN];
//
//int getDist(int f,int t) {
//	if(f <= t) return t - f;
//	return n-f + t;
//}
//
//void build(){
//	loop(i,m) {
//		to[A[i]].push_back(B[i]);
//	}
//	for(int i = 1;i <= n;i++){
//		sort(all(to[i]),[i](const int & a,const int &b) {
//			int da = getDist(i,a),db = getDist(i,b);
//			return da > db;
//		});
//	}
//}
//
//ll solve(int cur) {
////	vi tmp;
//	ll mx = cur;
//	for(int i = 1;i <= n;i++) {
//		ll offset = 0;
//		if(i < cur) offset = n;
//		for(int j : to[i]){
//			int tmp = 0;
//			if(j < i) tmp = n;
//			mx = max(mx,offset + tmp + j);
//			offset += n;
//		}
//	}
////	sort(all(tmp));
////	print(tmp,int);
//	return mx - cur;
//}
//
//int main(int argc,char **argv){
//#ifdef HOME
//	freopen("A.in","r",stdin);
//#endif
//	scanf("%d %d",&n,&m);
//	loop(i,m) {
//		scanf("%d",A + i);
//		scanf("%d",B + i);
//	}
//	build();
//	for(int st = 1;st <= n;st++)
//		printf("%lld%c",solve(st)," \n"[st==n]);
////	cerr << solve(1) << endl;
//	return 0;
//}
