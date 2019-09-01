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


const double EPS = 1e-12;
using point = std::complex<double>;
#define dot(p,q) ((p)*conj(q)).real()
#define norm(p) dot((p),(p))
#define mag(p) sqrt(norm(p))
#define cross(p,q) (conj(p)*(q)).imag()

std::istream& operator >> (std::istream & is,point & p) {
	double x,y;
	is >> x >> y;
	p = point(x,y);
	return is;
}

const int MAX = 111;
point P[MAX];

bool same(double a,double b) {
	return abs(a-b) < EPS;
}
bool leq(double a,double b) {
	return a < b || same(a,b);
}

double pointLineDist(point p,point a,point b) {
	assert(!same(norm(a-b),0));
	return abs(cross(p-a,b-a))/mag(a-b);
}

double pointSegmentDist(point p,point a,point b) {
	if(same(norm(a-b),0)) return mag(p-a);
	double d = pointLineDist(p,a,b);
	double x = dot(p-a,b-a),y = dot(p-b,a-b);
	return (leq(0,x) && leq(0,y)) ? d : min(mag(p-a),mag(p-b));
}


bool pointInPoly(point p,point *P,int n){
	//assumes convex polygon in ccw order
	loop(i,n){
		int j = (i + 1)%n;
		double s = cross(P[i]-p,P[j]-p);
//		cout << p << " " << P[i] << " " << P[j] << " " << s << endl;
		if(!leq(0,s)) return 0;
	}
	return 1;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	point O; cin >> O;
	int n; cin >> n;
	loop(i,n) cin >> P[i];
	double ans = 1e18;
	loop(i,n) {
		int j = (i + 1)%n;
		ans = min(ans,pointSegmentDist(O,P[i],P[j]));
	}
	if(pointInPoly(O,P,n)) ans = 0.0;
	ans *= 2.0;
	printf("%.3f\n",ans);
	return 0;
}
#endif
