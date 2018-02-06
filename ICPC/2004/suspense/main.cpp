#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
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
const double PI = acos(-1);
using namespace std;

char L[25],R[25];
int m,n;
double width;

// min(J_w,T_w) - B >= 2
// L-B = 1
// cat: [-3,0.5]
// B >= 1
// room = 3 , window = 1.5 ,window_bottom >= 1
vp I;


double adaptiveSimpsonsAux(function<double (double)> f, double a, double b, double epsilon, double S, double fa, double fb, double fc, int bottom) {
	double c = (a + b) / 2, h = b - a;
	double d = (a + c) / 2, e = (c + b) / 2;
	double fd = f(d), fe = f(e);
	double Sleft = (h / 12) * (fa + 4 * fd + fc);
	double Sright = (h / 12) * (fc + 4 * fe + fb);
	double S2 = Sleft + Sright;
	if (bottom <= 0 || fabs(S2 - S) <= 15 * epsilon)
		return S2 + (S2 - S) / 15;
	return adaptiveSimpsonsAux(f, a, c, epsilon / 2, Sleft, fa,fc, fd,bottom - 1) + adaptiveSimpsonsAux(f, c, b,epsilon / 2, Sright, fc, fb, fe, bottom - 1);
}

double adaptiveSimpsons(function<double (double)> f,  double a, double b,  double epsilon,  int maxRecursionDepth) {
	double c = (a + b) / 2, h = b - a;
	double fa = f(a), fb = f(b), fc = f(c);
	double S = (h / 6) * (fa + 4 * fc + fb);
	return adaptiveSimpsonsAux(f, a, b, epsilon, S, fa, fb, fc,maxRecursionDepth);
}

double getRoot(double a,double b,double c,double & x) {
	double d = b*b - 4*a*c;
	cerr << "d= " << d << endl;
	if(abs(d) < 1e-9) d = 0;
	if(d < 0) return 0;
	d = sqrt(d);
	x = (-b + d)/(2*a);
	if(abs(x - width) < 1e-9) x = width - 1e-9;
	if(x > width) x = (-b-d)/(2*a);
	if(abs(x) < 1e-9) x = 0;
	return x >= 0;
}

double compute_length(double h,double J_w,double T_w) {
	// f(x) = a*x^2 + b*x + c
	// f(0) = J_w -> c = J_w
	// f(mid) = h and f(width) = T_w
	// a*width^2 + b*width*2 = 4*(h - J_w)
	// a*width^2 + b*width = T_w - J_w
	double b = 0,c = h,l = sqrt((T_w - h)/(J_w - h)) + 1;
	l = width/l;

	double r = width - l;
	double a = (J_w - h)/(l*l);

//	cerr << 4*a*a << " " << -l << ".." << r<< endl;
//	auto f = [a,b,c](const double & x){
//		return a*x*x + b*x + c;
//	};
	auto df = [a,b,c](const double & x){
		double cdf = 2*a*x + b;
		return sqrt(1 + cdf*cdf);
	};
//	cerr << J_w << " " << h << " " << T_w << endl;
//	cerr << f(-l) << " " << f(0) << " " << f(r) << endl;
	return adaptiveSimpsons(df,-l,r,1e-6,20);

//	double ul = l*(2*a),ur = r*2*a;
//	auto F = [](const double & x) {
//		return (x*sqrt(x*x + 1) + asinh(x))/2;
//	};
//	return (F(ur) - F(-ul))/(2*a);
}


bool canGoUp(int B,char c) {
	int b = B/2,j = b/3;
	for(int i = max(j-1,0);i <= j+1 && i < m ;i++) {
		if(L[i] != c) continue;
		int pos = (3*i + 1)*2;
		if(pos < B) {
			int d = B - pos;
			if(d < 1) return 1;
		}
		else {
			int d = pos - B;
			if(d < 6) return 1;
		}
	}
	for(int i = max(j-1,0);i <= j+1 && i < n ;i++) {
		if(R[i] != c) continue;
		int pos = (3*i + 1)*2;
		if(pos < B) {
			int d = B - pos;
			if(d < 1) return 1;
		}
		else {
			int d = pos - B;
			if(d < 6) return 1;
		}
	}
	return 0;
}

bool canGoDown(int B,char c) {
	int b = B/2,j = b/3;
	for(int i = max(j-1,0);i <= j+1 && i < m ;i++) {
		if(L[i] != c) continue;
		int pos = (3*i + 1)*2;
		if(pos < B) {
			int d = B - pos;
			if(d < 6) return 1;
		}
		else {
			int d = pos - B;
			if(d < 1) return 1;
		}
	}
	for(int i = max(j-1,0);i <= j+1 && i < n ;i++) {
		if(R[i] != c) continue;
		int pos = (3*i + 1)*2;
		if(pos < B) {
			int d = B - pos;
			if(d < 6) return 1;
		}
		else {
			int d = pos - B;
			if(d < 1) return 1;
		}
	}
	return 0;
}


int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
//		freopen("out.out","w",stdout);
	#endif
	for(int t = 1;scanf("%d %d %lf",&m,&n,&width) == 3 && !(m == 0 && n == 0 && width == 0);t++) {
		loop(i,m) scanf(" %c",L + i);
		loop(i,n) scanf(" %c",R + i);
		double ans = 0.0; bool found = 0;
		int J_w = (m - 1)*3 + 1,T_w = (n - 1)*3 + 1;
		// L <= min(J_w,T_w)
		// 1 <= B
		// B <= min(J_w,T_w) - 2
		// B <= L - 1
		int en = min(J_w,T_w) - 2;
		for(int B = 2;B <= 2*en;B++){
			if(canGoUp(B,'C') && canGoDown(B,'B')) continue;
			found = 1;
			double tmp = compute_length(B/2.0 + 1,J_w,T_w);
//			fprintf(stderr,"f(%.1f) = %.3f\n",B/2.0,tmp);
			ans = max(ans,tmp);
		}
		if(t!=1) puts("");
		printf("Case %d: ",t);
		if(found) printf("%.3f\n",ans);
		else puts("impossible");
	}
	return 0;
}
