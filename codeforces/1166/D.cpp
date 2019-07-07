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
//vector<ll> S;
//ll a,b,m;
//
//int lg(double x) {
//	static double log2 = log(2);
//	return floor(log(x)/log2);
//}
//
//void create_test(){
//	a = rand()%10 + 1;
//	int len = rand()%5;
//	m = rand()%10 + 1;
//	ll s = b = a;
//	loop(i,len) {
//		b = s + rand()%m + 1;
//		s += b;
//	}
//}
//
//bool solve() {
//	if(b < a) return 0;
//	S.clear();
//	S.push_back(a);
//	if(a == b) return 1;
//	ll len = min(lg(b/(a + 1.0)) + 2,50);
//	ll R = b - (a << (len - 2));
//	assert(R >= 0);
////	cerr << len << " " << R << endl;
//	R --;
//	for(int k = 1;k+1 < len;k++) {
//		ll exponent = len - 2 - k;
//		ll coef = 1LL << exponent;
//		R -= coef;
//	}
//	if(R < 0) return 0;
////	cerr << "R: " << R << endl;
//	ll v = a;
//	for(int k = 1;k+1 < len;k++) {
//		ll exponent = len - 2 - k;
//		ll coef = 1LL << exponent;
////		cerr << k << " " << R << " " << coef << endl;
//		ll r = min(R/coef,m-1) + 1;
//		ll term = v + r;
//		v += term;
////		cerr << term << endl;
//		S.push_back(term);
//		R -= (r-1)*coef;
//		assert(R >= 0);
//	}
//	R++;
//	if(R > m) return 0;
//	if(R < 1) return 0;
//	S.push_back(b);
//	return 1;
//}
//
//void test(){
//	loop(t,1000) {
//		create_test();
//		if(!solve()){
//			cerr << "failed on " << a << " " << b << " " << m << endl;
//			exit(0);
//		}
//	}
//}
//
//int main(int argc,char **argv){
//#ifdef HOME
//	freopen("in.in","r",stdin);
//#endif
//	int Q; scanf("%d",&Q);
//	loop(q,Q) {
//		scanf("%lld %lld %lld",&a,&b,&m);
//		if(solve()) {
//			printf("%d",sz(S));
//			for(ll x : S) printf(" %lld",x);
//			puts("");
//		}
//		else puts("-1");
//	}
////	test();
//	return 0;
//}
