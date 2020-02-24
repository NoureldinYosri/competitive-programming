#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define popcnt(x) __builtin_popcountll(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
using namespace std;


const double eps = 1e-9;

double adaptiveSimpsonsAux(function<double(const double &)> f, double a, double b,
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

double adaptiveSimpsons(function<double(const double &)> f,
		double a, double b,	double epsilon, int maxRecursionDepth) {
	double c = (a + b) / 2, h = b - a;
	double fa = f(a), fb = f(b), fc = f(c);
	double S = (h / 6) * (fa + 4 * fc + fb);
	return adaptiveSimpsonsAux(f, a, b, epsilon, S, fa, fb, fc,maxRecursionDepth);
}

double get_area(double theta, function<double(const double&)> R){
	auto f = [R](const double & x){
		return pow(R(x), 2.0)/2.0;
	};
	return adaptiveSimpsons(f, 0, theta, eps, 20);
}

pair<double, double> solve(double a1, double b1, double a2, double b2, double t1, double T){
	double t2 = t1 * pow(a2/a1, 1.5);
	double f2 = sqrt(a2*a2 - b2*b2);
	double e = b2/a2; e = sqrt(1 - e*e);
	T = fmod(T, t2);
	
	double total_area = a2*b2*M_PI;
	double target_area = total_area * T/t2;
	
	
	auto R = [a2, e](const double & theta){
		return a2*(1 - e*e)/(1 + e*cos(theta));
	};
	
//	cerr << total_area << "*" << T << "/" << t2 << " = " << target_area << endl;
//	cerr << get_area(2*M_PI, R) << endl;

	double l = 0,r = 2*M_PI;	
	for(int i = 0; i < 64 && r-l > eps; i++){
		double m = l + (r-l)/2.0;
		if(get_area(m, R) >= target_area) r = m;
		else l = m;
	}
	double theta = l;
	//cerr << theta*180/M_PI << " " << get_area(theta, R) << endl;
	double d = R(theta);
	double x = d*cos(theta);
	double y = d*sin(theta);
	x += f2;
	return pair<double,double>(x, y);	
}

double repr(double x){
	static char S[100];
/*	sprintf(S, "%.3f", abs(x));
	double y;
	sscanf(S, "%lf", &y);
	if(y > 0) return x;
	return 0;
*/
	return x;
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	int T, a1, b1, a2, b2, t1;
	for(int t = 1;
			scanf("%d %d %d %d %d %d", &a1, &b1, &t1, &a2, &b2, &T) == 6 && (a1 || b1 || a2 || b2 || t1 || T);
			t++){
		assert(a1 >= b1);
		assert(a2 >= b2);
		pair<double, double> ans = solve(a1, b1, a2, b2, t1, T);
		printf("Solar System %d: %.3f %.3f\n", t, repr(ans.first), repr(ans.second));
	}
	return 0;
}
