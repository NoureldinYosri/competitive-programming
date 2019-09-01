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
const double EPS = 1e-12;

point read(){
	double x,y;
	cin >> x >> y;
	return point(x,y);
}

double dist(point p) {
	return sqrt((p*conj(p)).real());
}

double cross(point A,point B) {
	return (conj(A)*B).imag();
}

double dot(point A,point B) {
	return (A*conj(B)).real();
}
bool leq(double a,double b) {
	return a < b || abs(a-b) < EPS;
}

double pointLineDist(point p,point A,point B) {
	return abs(cross(p - A,B - A))/dist(B - A);
}

bool projOnSegment(point p,point A,point B) {
	double s = dot(p - A,B - A);
	if(leq(0,s)) {
		s = dot(p - B,A - B);
		return leq(0,s);
	}
	else return 0;
}
bool same(double a,double b) {
	return abs(a-b) < EPS;
}

double pointSegmentDist(point p,point A,point B) {
	if(same(dist(B-A),0)) return dist(A-p);
	double d = pointLineDist(p,A,B);
	if(projOnSegment(p,A,B)) return d;
	return min(dist(A-p),dist(B-p));
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	point A = read();
	point B = read();
	point C = read();
	double L; cin >> L;

	double mx = max(dist(B-C),dist(A-C)) - L;
	double mn = pointSegmentDist(C,A,B) - L;
	mx = max(mx,0.0);
	mn = max(mn,0.0);
	printf("%.2f\n%.2f\n",mn,mx);
	return 0;
}
