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
//const int DIM = 5,mod = 1000000007;
//
//int add(int a,int b,int m) {
//	a += b;
//	if(a >= m) a -= m;
//	if(a < 0) a += m;
//	return a;
//}
//int mul(int a,int b,int m) {
//	return (a*(ll)b)%m;
//}
//
//int POWER(int a,ll p) {
//	if(p <= 0) return 1;
//	int b = 1;
//	for(;p > 1;p >>= 1) {
//		if(p & 1) b = mul(a,b,mod);
//		a = mul(a,a,mod);
//	}
//	return mul(a,b,mod);
//}
//
//void mul(int A[DIM][DIM],int B[DIM][DIM],int dim) {
//	static int C[DIM][DIM];
//	loop(i,dim) loop(j,dim) {
//		C[i][j] = 0;
//		loop(k,dim) C[i][j] = add(C[i][j],mul(A[i][k],B[k][j],mod-1),mod-1);
//	}
//	loop(i,dim) loop(j,dim) A[i][j] = C[i][j];
//}
//
//void make_eye(int A[DIM][DIM]) {
//	loop(i,DIM) loop(j,DIM) A[i][j] = i==j;
//}
//void EXP(int A[DIM][DIM],ll p,int dim) {
//	assert(p >= 0);
//	if(!p) return make_eye(A);
//	int B[DIM][DIM]; make_eye(B);
////	cerr << "raise to " << p << endl;
//	for(;p > 1;p >>= 1) {
//		if(p & 1) mul(B,A,dim);
//		mul(A,A,dim);
//	}
//	mul(A,B,dim);
//}
//
//int main(int argc,char **argv){
//#ifdef HOME
//	freopen("in.in","r",stdin);
//#endif
//	ll n,f1,f2,f3,c;
//	cin >> n >> f1 >> f2 >> f3 >> c;
//	f1 %= mod;
//	f2 %= mod;
//	f3 %= mod;
//	c %= mod;
//
//	int A[DIM][DIM] = {{1,1,1},{1,0,0},{0,1,0}};
//	EXP(A,n - 3,3);
//	f1 = POWER(f1,A[0][2]);
//	f2 = POWER(f2,A[0][1]);
//	f3 = POWER(f3,A[0][0]);
////	prArr(A[0],3,int);
//	int B[DIM][DIM] = {
//			{1,0,0,0,1},
//			{2,1,1,1,2},
//			{0,1,0,0,0},
//			{0,0,1,0,0},
//			{0,0,0,0,1}
//	};
//	EXP(B,n-3,5);
//	int e = B[1][4];
////	cerr << c << "^" << e << " = " ;
//	c = POWER(c,e);
////	cerr << c << endl;
//
//	int ans = mul(c,mul(mul(f1,f2,mod),f3,mod),mod);
//	cout << ans << endl;
//	return 0;
//}
