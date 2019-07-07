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
//int LIM = 1000 *1000;
//
//ll A[2 << 10];
//
//bool build(int n,int a,ll S) {
//	int m = n-1;
//	for(int i = 0;i+1 < n;i++) {
//		A[i] = S/m;
//		S -= A[i];
//	}
//	for(int i = 0;i+1 < n && S;i++,S--)
//		A[i] ++;
//	loop(i,n-1) A[i] *= -1;
//	A[n-1] = a;
//	reverse(A,A+n-1);
//	loop(i,n) if(abs(A[i]) > LIM) return 0;
//	printf("%d\n",n);
//	loop(i,n) printf("%lld%c",A[i]," \n"[i==n-1]);
//	return 1;
//}
//
//int main(int argc,char **argv){
//#ifdef HOME
//	freopen("B.in","r",stdin);
//#endif
//	int k;
//	cin >> k ;
//
//	for(int n = 2;n <= 2000;n++) {
//		int m = n-1;
//		int r = (n-k%n)%n;
//		// a = q*n + r > k/m
//		int qn = max(k/m-r,0);
//		ll q = qn/n + 1;
//		ll a = n*q + r;
////		cerr << a << " " << q <<  " " << r << " " << k/m << endl;
//		assert(a > k/m);
//		if(a > LIM) continue;
//		ll f = a*(n-1LL) - k;
//
//		if(f%n == 0) {
//			ll S = f/n;
//			if(build(n,a,S))
//				return 0;
//		}
//	}
//	cout << -1 << endl;
//	return 0;
//}
