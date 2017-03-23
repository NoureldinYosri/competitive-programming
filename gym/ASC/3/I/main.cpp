#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define point pair<double,double>
#define pl pair<ll,ll>
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

int r1,r2; 

double f(const double & x){
	return 8*sqrt((r1*r1 - x*x)*(r2*r2 - x*x));
}
	
double adaptiveSimpsonsAux(double(*f)(const double&), double a,double b,
	double epsilon, double S, double fa, double fb, double fc, int bottom) {
	double c = (a + b) / 2, h = b - a;
	double d = (a + c) / 2, e = (c + b) / 2;
	double fd = f(d), fe = f(e);
	double Sleft = (h / 12) * (fa + 4 * fd + fc);
	double Sright = (h / 12) * (fc + 4 * fe + fb);
	double S2 = Sleft + Sright;
	if (bottom <= 0 || fabs(S2 - S) <= 15 * epsilon)
		return S2 + (S2 - S) / 15;
	return adaptiveSimpsonsAux(f, a, c, epsilon / 2, Sleft, fa,fc, fd,bottom - 1) 
			+ adaptiveSimpsonsAux(f, c, b,epsilon / 2, Sright, fc,fb, fe, bottom - 1);
}

double adaptiveSimpsons(double(*f)(const double&), double a, double b, double epsilon, int maxRecursionDepth) { 
	double c = (a + b) / 2, h = b - a;
	double fa = f(a), fb = f(b), fc = f(c);
	double S = (h / 6) * (fa + 4 * fc + fb);
	return adaptiveSimpsonsAux(f, a, b, epsilon, S, fa, fb, fc,maxRecursionDepth);
}

int main(){
	freopen("twocyl.in","r",stdin);
	freopen("twocyl.out","w",stdout);
	cin >> r1 >> r2;
	double ans = adaptiveSimpsons(f,0.0,min(r1,r2)+0.0,1e-5,20);
	printf("%.4f\n",ans);

	return 0;
}
