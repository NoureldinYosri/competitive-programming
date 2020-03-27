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
 
const int MAX = 10*1000 + 10,B = 58;
struct point{
	double x,y;
	point(){x=y=0;}
	point(double a,double b):x(a),y(b){}
	inline double real(){return x;}
	inline double imag(){return y;}
	point operator * (const point & o) const {
		double a = x*o.x - y*o.y;
		double b = x*o.y + y*o.x;
		return point(a,b);
	}
	point operator * (const double c) const {
		return point(c*x,c*y);
	}
	point operator - (const point & o) const {
		return point(x-o.x,y-o.y);
	}
	point operator + (const point & o) const {
		return point(x+o.x,y+o.y);
	}
};
const double EPS = 1e-4;
double X[MAX],Y[MAX];
point P[MAX];
int n;
point in;
 
#define conj(p) point(p.x,-p.y)
#define norm(p) ((p)*conj(p)).real()
#define cross(p,q) (conj(p)*(q)).imag()
#define dot(A,B) ((A)*conj(B)).real()
#define same(x,y) (abs((x)-(y)) < EPS)
#define leq(x,y) (((x) < (y)) || same(x,y))
 
 
 
double memLen[MAX];
 
 
 
bool PointInPoly(point p) {
//	cout << "is " << p << " in poly" << endl;
	loop(i,n){
		point A = P[i] - p;
		point B = P[i+1] - p;
		double s = cross(A,B);
		if(leq(s,0)) continue;
		return 0;
	}
	return 1;
}
 
double f(double x,double y) {
	point p(x,y);
//	cout << p << endl;
//	assert(PointInPoly(p));
	double R = 1e9;
	loop(i,n){
		point A = p - P[i];
		point B = P[i + 1] - P[i];
		double d = abs(cross(A,B))/memLen[i];
		R = min(R,d);
	}
//	cout << p << " " << R << endl;
	return R;
}
 
 
double f(double x) {
	double s = 1e9,e = -1e9;
	loop(i,n){
		int j = i + 1;
		double l = min(P[i].real(),P[j].real());
		double r = max(P[i].real(),P[j].real());
		if(leq(l,x) && leq(x,r)) {
			if(same(l,r)) {
				s = min(s,P[i].imag());
				s = min(s,P[i].imag());
				e = max(e,P[i].imag());
				e = max(e,P[i].imag());
			}
			else{
				point d = P[j] - P[i];
				point p = P[i] + d*((x - P[i].x)/d.x);
				double y = p.imag();
				s = min(s,y);
				e = max(e,y);
			}
		}
	}
	for(int t = 0;t < B && s + EPS < e;t++) {
		double m1 = s + (e-s)/3.0;
		double m2 = m1 + (e-s)/3.0;
		if(f(x,m1) < f(x,m2)) s = m1;
		else e = m2;
	}
	return max(f(x,s),f(x,e));
}


 
int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d",&n);
	loop(i,n) {
		scanf("%lf %lf",X + i,Y + i);
		point p(X[i],Y[i]);
		P[i] = p;
		if(i && mp(Y[i],X[i]) < mp(Y[0],X[0])) {
			swap(X[i],X[0]);
			swap(Y[i],Y[0]);
			swap(P[i],P[0]);
		}
	}
	sort(P + 1,P + n,[](const point & a,const point & b) {
		point A = a - P[0],B = b - P[0];
		return cross(A,B) < 0;
	});
//	loop(i,n) cout << P[i].real() << " " << P[i].imag() << endl;
 
 
	loop(i,n){
		int j = (i + 1)%n;
		point p = P[j] - P[i];
		memLen[i] = sqrt(norm(p));
	}
	P[n] = P[0];
 
	double s = 1e9,e = -1e9;
	loop(i,n) s = min(s,X[i]),e = max(e,X[i]);


	const double invphi = (sqrt(5) - 1) / 2 ;
	const double invphi2 = (3 - sqrt(5)) / 2;

    double h = e - s;
    double a = s, b = e;
    int m = int(ceil(log(1e-6 / h) / log(invphi)));

	double  c = a + invphi2 * h;
	double d = a + invphi * h;
    double yc = f(c);
    double yd = f(d);

    for(int k = 0;k < m-1; k++){
        if (yc > yd){
            b = d;
            d = c;
            yd = yc;
            h = invphi * h;
            c = a + invphi2 * h;
            yc = f(c);
        }
        else{
            a = c;
            c = d;
            yc = yd;
            h = invphi * h;
            d = a + invphi * h;
            yd = f(d);
        }
    }

	printf("%.3f\n",f(a));
	return 0;
}
