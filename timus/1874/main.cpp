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
#define tc() int T; scanf("%d",&T); for(int t = 1;t <= T;t++)
using namespace std;

const int B = 1000;
const double EPS = 1e-12;
int a,b;

double A(double w,double h,bool debug = 0) {
	double L = sqrt(w*w + h*h);
	double ct = (a*a + b*b - L*L)/(2*a*b);
//	ct = max(ct,-1.0);
//	ct = min(ct,1.0);
	double t = acos(ct);
	if(debug) cerr << t*180/PI << " " << ct << " " << 0.5*a*b*sin(t) << endl;
//	assert(t == t);
	return 0.5*h*w + 0.5*a*b*sin(t);
}

double g(double w,bool debug = 0) {
	double s = max(pow(a-b,2.0)-w*w,0.0),e = max(pow(a+b,2.0)-w*w,0.0);
	s = sqrt(s);
	e = sqrt(e);
	for(int t = 0;t < B && s + EPS < e;t++){
		double m1 = s + (e-s)/3.0;
		double m2 = m1 + (e-s)/3.0;
		if(A(w,m1) < A(w,m2)) s = m1;
		else e = m2;
	}
	if(debug) cout << w << " " << s << " " << A(w,s,1) << endl;
	return max(A(w,s),A(w,e));
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	cin >> a >> b;
	if(a > b) swap(a,b);
//	double s = abs(a-b),e = a+b;
//	for(int t = 0;t < B && s < e;t++){
//		double m1 = s + (e-s)/3.0;
//		double m2 = m1 + (e-s)/3.0;
//		if(g(m1) < g(m2)) s = m1;
//		else e = m2;
//	}
//	cout << g(s,1) << endl;
//	printf("%.10f\n",max(g(s),g(e)));
	double A = (a*a + b*b)/4.0 + sqrtl(2.0)*a*b/2;
	printf("%.10f\n",A);
	return 0;
}
