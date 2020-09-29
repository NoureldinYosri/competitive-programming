#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
typedef std::vector<int> vi;
typedef std::pair<int,int> pi;
typedef std::vector<pi> vp;
typedef long long ll;
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
template<class A,class B>
std::ostream& operator << (std::ostream& st,const std::pair<A,B> p) {
	st << "(" << p.first << ", " << p.second << ")";
	return st;
}
using namespace std;

const long double eps = 1e-12;
const int MAX = 1 << 20;
long double S[MAX], K[MAX], V[MAX];
int n;
long double E0;

long double get_root(long double v, long double rhs){
	long double a = 1;
	long double b = -v;
	long double c = 0;
	long double d = -rhs;
	
	complex<long double> delta0 = pow(b, 2) - 3*a*c;
	complex<long double> delta1 = 2*pow(b, 3) - 9*a*b*c + 27*pow(a, 2)*d;
	
	complex<long double> c0 = sqrt(pow(delta1, 2) - 4.0L*pow(delta0, 3));
	complex<long double> C = (delta1 + c0)/2.0L;
	if(abs(C) < eps) C = (delta1 - c0)/2.0L;
	C = pow(C, 1/3.0);
	
	complex<long double> w0 = polar(1.0, 2*M_PI/3.0), w = 1;
	
	loop(i, 3){
		complex<long double> x = -1/(3*a) * (b + w*C + delta0/(w*C));
		long double u = x.real();
		if(abs(u) < eps) u = 0;
		if(abs(x.imag()) <= eps && u >= 0) {
		//	cout << x << endl;
			return u;
		}
		
		w = w*w0;
	}
//	assert(0);
	return 1e5;
}

const long double oo = LLONG_MAX;

long double getE(long double lambda){
	long double E = 0;
	loop(i, n){
		long double rhs = 1/(lambda * 2*K[i]);
		long double u = get_root(V[i], rhs);
		long double dv = abs(u - V[i]);
		if(dv > sqrt((E0-E)/(K[i]*S[i])) + 10*eps) return oo;
		E += K[i]*(u - V[i])*(u - V[i])*S[i];
//		cout << u << " " << K[i]*(u - V[i])*(u - V[i]) << endl;
		if(E > E0) return E;
	}
	return E;
}

long double get_time(long double lambda){
	long double t = 0;
	loop(i, n){
		long double rhs = 1/(lambda * 2*K[i]);
		long double u = get_root(V[i], rhs);
		t += S[i]/u;
	}
	return t;	
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	cin >> n >> E0;
	
	
	loop(i, n) cin >> S[i] >> K[i] >> V[i];;
	long double s = 0, len = 10;
	while(len > eps){
		long double m = s + len/2.0;
		if(getE(m) > E0) s = m;
		len /= 2.0;
	}
	long double ans = get_time(s);
	
	printf("%.10f\n", (double)ans);
	return 0;
}
