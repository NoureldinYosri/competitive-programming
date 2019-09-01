#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
typedef std::vector<int> vi;
typedef std::pair<int, int> pi;
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
template<class A, class B>
std::ostream& operator <<(std::ostream &st, const std::pair<A, B> p) {
	st << "(" << p.first << ", " << p.second << ")";
	return st;
}
#define tc() int T; scanf("%d",&T); for(int t = 1;t <= T;t++)
using namespace std;


double adaptiveSimpsonsAux(double (*f)(const double&), double a, double b,
				double epsilon, double S, double fa, double fb, double fc, int bottom) {
	double c = (a + b) / 2, h = b - a;
	double d = (a + c) / 2, e = (c + b) / 2;
	double fd = f(d), fe = f(e);
	double Sleft = (h / 12) * (fa + 4 * fd + fc);
	double Sright = (h / 12) * (fc + 4 * fe + fb);
	double S2 = Sleft + Sright;
	if (bottom <= 0 || fabs(S2 - S) <= 15 * epsilon)
		return S2 + (S2 - S) / 15;
	return adaptiveSimpsonsAux(f, a, c, epsilon / 2, Sleft, fa, fc, fd,bottom - 1)
			+ adaptiveSimpsonsAux(f, c, b,epsilon / 2, Sright, fc,fb, fe, bottom - 1);
}
//
// Adaptive Simpson's Rule
//
double adaptiveSimpsons(double (*f)(const double&),double a, double b, // interval [a,b]
		double epsilon, // error tolerance
		int maxRecursionDepth) { // recursion cap
	double c = (a + b) / 2, h = b - a;
	double fa = f(a), fb = f(b), fc = f(c);
	double S = (h / 6) * (fa + 4 * fc + fb);
	return adaptiveSimpsonsAux(f, a, b, epsilon, S, fa, fb, fc, maxRecursionDepth);
}

const int MAX = 20;
const double EPS = 1e-9;
int n;
double X[MAX],Y[MAX],R[MAX];

bool leq(double a,double b) {
	return a < b || abs(a-b) < EPS;
}
double f(const double & x) {
	static vector<pair<double,double>> aux;
	aux.clear();
	loop(i,n){
		double dx = abs(x - X[i]);
		if(leq(R[i],dx)) continue;
		double dy = sqrt(R[i]*R[i] - dx*dx);
		double y1 = Y[i] - dy;
		double y2 = Y[i] + dy;
		y1 = max(y1,0.0);
		y1 = min(y1,1.0);
		y2 = max(y2,0.0);
		y2 = min(y2,1.0);
		aux.emplace_back(y1,y2);
	}
	if(aux.empty()) return 0.0;
	sort(all(aux));
	double s = aux[0].first,e = aux[0].second;
	double ret = 0;
	for(auto p : aux) {
		if(leq(p.first,e)) e = max(e,p.second);
		else {
			ret += e-s;
			s = p.first;
			e = p.second;
		}
	}
	ret += e-s;
//	cerr << x << " " << ret << ": ";
//	for(auto p : aux) cerr << p << " ";
//	cerr << endl;
	return ret;
}

int main() {
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d",&n);
	loop(i,n) scanf("%lf %lf %lf",X + i,Y + i,R + i);
	double ans = adaptiveSimpsons(f,0,1,1e-6,20)*100;
	printf("%.10lf\n",ans);
	return 0;
}
