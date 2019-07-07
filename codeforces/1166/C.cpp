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
//bool cond(int a,int b) {
//	a = abs(a),b = abs(b);
//	if(a > b) swap(a,b);
//	return b <= 2*a;
//}
//
//void sample(){
//	int X[2] = {rand()%1000,rand()%1000};
//	loop(i,2) X[i] *= 2*(rand()%2) - 1;
//	int s = abs(X[0]),e = abs(X[1]);
//	if(s > e) swap(s,e);
//	int l = abs(X[0] - X[1]),r = abs(X[0] + X[1]);
//	if(l > r) swap(l,r);
//	int a = X[0],b = X[1];
//	if(l <= s && e <= r) {
//		cerr << "found " << X[0] << " " << X[1] << endl;
//		assert(cond(a,b));
//	}
//	else if(cond(a,b)){
//		cerr << "week cond " << X[0] << " " << X[1] << endl;
//		exit(0);
//	}
//}
//
//int A[1 << 20],n;
//
//int main(int argc,char **argv){
//#ifdef HOME
//	freopen("in.in","r",stdin);
//#endif
//	scanf("%d",&n);
//	loop(i,n) {
//		scanf("%d",A + i);
//		A[i] = abs(A[i]);
//	}
//	sort(A,A + n);
//	ll ans = 0;
//	loop(i,n){
//		int tmp = upper_bound(A,A + n,2*A[i]) - (A + i) - 1;
////		cerr << A[i] << " " << tmp << endl;
//		ans += tmp;
//	}
//	cout << ans << endl;
//	return 0;
//}
