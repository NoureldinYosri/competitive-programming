#ifdef ACTIVE
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

using point = complex<double>;
const int MAX = 100*1000 + 10;
double f[MAX];
int X[MAX],Y[MAX],n;

double cross(point o,point p,point q){
	p -= o;
	q -= o;
	return (conj(p)*q).imag();
}


point getPoint(point a,point b,int ty) {
	point dr = b - a;
	if(abs(dr.imag()) < 1e-12) return a;
	// a.imag() + t * dr.imag() = Y[i]
	double step = (ty - a.imag())/dr.imag();
	return a + dr*step;
}

double leq(double a,double b) {
	return a < b || abs(a - b) < 1e-12;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d",&n);
	loop(i,n) scanf("%d %d",X + i,Y + i);
	double ans = 0;
	vector<point> ST;
	ST.emplace_back(X[0],Y[0]);
	for(int i = 1;i < n;i++){
		point d (X[i],Y[i]);
		point c (X[i-1],Y[i-1]);
		point prv = c;
		while(!ST.empty() && leq(ST.back().imag(),Y[i])) {
//			cerr << ST.back() << " vs " << d << endl;
			point b = ST.back();
			ST.pop_back();
			if(ST.empty()) break;
			point a = ST.back();
			int y = min(a.imag(),d.imag());
			a = getPoint(a,b,y);
			point q = getPoint(c,d,y);
			double base1 = abs((q - a).real());
			double base2 = abs((c - b).real());
			double h = y - b.imag();
			double A = (base1 + base2)*h/2;
			if(leq(0,h)) {
//				cerr << a << " " << b << " " << c << " " << q << " -> " << A << endl;
				ans += A;
				c = q;
				prv = a;
			}
			else break;
		}
		ST.push_back(prv);
		ST.push_back(c);
		ST.push_back(d);
	}
	printf("%.9lf\n",ans);
	return 0;
}
#endif
