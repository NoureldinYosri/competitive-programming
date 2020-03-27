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


double adaptiveSimpsonsAux(double (*f)(const double&), double a, double b,
		double epsilon, double S, double fa, double fb, double fc, int bottom) {
	double c = (a + b) / 2, h = b - a;
	double d = (a + c) / 2, e = (c + b) / 2;
	double fd = f(d), fe = f(e);
	double Sleft = (h / 12) * (fa + 4 * fd + fc);
	double Sright = (h / 12) * (fc + 4 * fe + fb);
	double S2 = Sleft + Sright;
	if (bottom <= 0 || fabs(S2 - S) <= 15 * epsilon) return S2 + (S2 - S) / 15;
	return adaptiveSimpsonsAux(f, a, c, epsilon / 2, Sleft, fa, fc, fd,bottom - 1)
			+ adaptiveSimpsonsAux(f, c, b, epsilon / 2, Sright, fc, fb, fe,bottom - 1);
}
double adaptiveSimpsons(double (*f)(const double&),
		double a, double b,	double epsilon, int maxRecursionDepth) {
//	cerr << a << " " << b << endl;
	double c = (a + b) / 2, h = b - a;
	double fa = f(a), fb = f(b), fc = f(c);
	double S = (h / 6) * (fa + 4 * fc + fb);
	return adaptiveSimpsonsAux(f, a, b, epsilon, S, fa, fb, fc,maxRecursionDepth);
}

const double eps = 1e-12;
const int MAX = 200*1000 + 10;
char type[MAX];
int L[MAX], R[MAX];
int X[MAX], Y[MAX], D[MAX];
int n;

double leq(double a, double b){
	return a < b || abs(a - b) < eps;
}

double f(const double & x){
	static vector<pair<double, double>> V; 
	V.clear();
	loop(i, n){
		if(!(leq(L[i], x) && leq(x, R[i]))) continue;
		assert(leq(L[i], x) && leq(x, R[i]));
		if(type[i] == 'A'){
			V.emplace_back(Y[i] - D[i], Y[i] + D[i]);
		}
		else if(leq(x, X[i])){
			double xd = x - L[i];
			V.emplace_back(Y[i] - xd, Y[i] + xd);
		}
		else {
			double xd = x - X[i];
			V.emplace_back(Y[i] - D[i] + xd, Y[i] + D[i] - xd);
		}
	}
	sort(all(V));
	double s = -3000,e = -3000;
	double ret = 0;
	for(auto p : V){
		if(p.first <= e) e = max(e, p.second);
		else {
			ret += e-s;
			s = p.first;
			e = p.second;
		}
	}
	ret += e-s;
	//cerr << x << " " << ret << endl;
	return ret;
}



int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	vector<pi> V;
	scanf("%d", &n);
	loop(i, n){
		scanf(" %c %d %d %d", type + i, X + i, Y + i, D + i);
		D[i] >>= 1;
		L[i] = X[i] - D[i];
		R[i] = X[i] + D[i];
		V.emplace_back(L[i], R[i]);
	}
	sort(all(V));
	
	int s = -3000, e = -3000;
	double ans = 0.0;
	for(auto p : V){
		if(p.first <= e) e = max(e, p.second);
		else {
			if(s != -3000) ans += adaptiveSimpsons(f, s, e, eps, 20);
			s = p.first;
			e = p.second;
		}
	}
	if(s != -3000) 
		ans += adaptiveSimpsons(f, -11, 11, 1e-15, 40);
	printf("%f\n", ans);
	for(int i = -11; i <= 11; i++)
		cout << i + 0.5 << " " << f(i + 0.5) << endl;
	return 0;
}
