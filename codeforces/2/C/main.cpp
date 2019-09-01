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


struct circle{
	double x0,y0,r;
public:
	double getRatio(double x,double y) {
		double f = (x - x0)*(x - x0) + (y - y0)*(y - y0);
		f /= r*r;
		return f;
	}
	double getDx(double x,double y){
		double dfx = 2*(x - x0);
		dfx /= r*r;
		return dfx;
	}
	double getDy(double x,double y) {
		double dfy = 2*(y - y0);
		dfy /= r*r;
		return dfy;
	}
	friend istream & operator >> (istream & st,circle & c) {
		st >> c.x0 >> c.y0 >> c.r;
		return st;
	}
};

circle C[3];
bool check(double x,double y) {
	double R[3];
	loop(i,3) R[i] = C[i].getRatio(x,y);
	double e = 0;
	loop(i,2) {
		double r = R[i + 1] - R[i];
		e += r*r;
	}
//	cerr << e << endl;
	return e < 1e-9;
}

const double Th = 1e-100;

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	double x = 0,y = 0;
	loop(i,3) {
		cin >> C[i];
		x += C[i].x0;
		y += C[i].y0;
	}
	x /= 3,y /= 3;
	double step = 1e-3;
	for(int t = 0;t < 1000*1000;t++) {
		double dex = 0,dey = 0;
		loop(i,2) {
			double coef = 2*(C[i + 1].getRatio(x,y) - C[i].getRatio(x,y));
			dex += coef*(C[i + 1].getDx(x,y) - C[i].getDx(x,y));
			dey += coef*(C[i + 1].getDy(x,y) - C[i].getDy(x,y));
		}
		x -= step * dex;
		y -= step * dey;
		if(abs(x) < Th) x = 0;
		if(abs(y) < Th) y = 0;
//		double e = 0;
//		loop(i,2) {
//			double r = C[i + 1].getRatio(x,y) - C[i].getRatio(x,y);
//			e += r*r;
//		}
//		cerr << e << endl;
	}
	if(check(x,y)) printf("%.6f %.6f\n",x,y);
	return 0;
}
