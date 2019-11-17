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

inline double cross(point a,point b) {
	return (conj(a)*b).imag();
}
inline double cross(point o,point a,point b) {
	return cross(a-o,b-o);
}
inline double dot(point a,point b) {
	return (conj(a)*b).real();
}
inline double norm(point a,bool takeRoot) {
	double res = dot(a,a);
	if(takeRoot) res = sqrt(res);
	return res;
}
bool leq(double a,double b) {
	return a < b || abs(a-b) < EPS;
}

const int MAX = 111;
point P[MAX];
int n;

bool same(double x,double y) {
	return abs(x-y) < EPS;
}

double getArg(point p){
	double t = arg(p);
	if(same(t,0)) return 0;
	if(t > 0) return t;
	return t + 2*PI;
}

double pointLineDist(point p,point a,point r){
	return abs(cross(p - a,r));
}

int W[MAX];
int getNumCircles(point q,point r) {
	int res = 0;
	loop(i,n) res += W[i] * leq(pointLineDist(P[i],q,r),1);
	return res;
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d",&n);
	map<pair<string,string>,int> id;
	int m = 0;
	loop(i,n) {
		string X,Y; cin >> X >> Y;
		auto q = make_pair(X,Y);
		if(id.count(q)) {
			W[id[q]]++;
			continue;
		}
		W[m] = 1;
		id[q] = m;
		stringstream ss;
		ss << X << " " <<  Y;
		double x,y; ss >> x >> y;
		P[m] = point(x,y);
//		cout << P[m] << endl;
		m++;
	}
	n = m;
//	prArr(W, n,int);
	int ans = *max_element(W,W + n);
	loop(i,n) loop(j,i) {
		point r = P[j] - P[i];
		double d = norm(r,1);
		r /= d;
		point n = point(r.imag(),-r.real());
		for(int sgn = -1;sgn <= 1;sgn += 2)
			ans = max(ans,getNumCircles(P[i] + sgn*1.0*n,r));

		if(leq(2,d)) {
			d = max(d,2.0);
			point q = P[i] + d/2*r;
			double t = asin(2/d);
			for(int sgn = -1;sgn <= 1;sgn += 2)
				ans = max(ans,getNumCircles(q,r * polar(1.0,sgn*t)));
		}
	}

	printf("%d\n",ans);
	return 0;
}
