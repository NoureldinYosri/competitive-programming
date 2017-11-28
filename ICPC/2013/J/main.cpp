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


typedef complex<double> point;
#define EPS 1e-9
#define	vec(a,b) ((b)-(a))
#define	polar(r,t) ((r)*exp(point(0,(t))))
#define	angle(v) (atan2((v).Y,(v).X))
#define	length(v) ((double)hypot((v).imag(),(v).real()))
#define	lengthSqr(v) (dot(v,v))
#define	dot(a,b) ((conj(a)*(b)).real())
#define	cross(a,b) ((conj(a)*(b)).imag())
#define	rotate(v,t) (polar(v,t))
#define	rotateabout(v,t,a) (rotate(vec(a,v),t)+(a))
#define	reflect(p,m) ((conj((p)/(m)))*(m))
#define	normalize(p) ((p)/length(p))
#define	same(a,b) (lengthSqr(vec(a,b))<EPS)
#define	mid(a,b) (((a)+(b))/point(2,0))
#define	perp(a) (point(-(a).Y,(a).X))
#define	colliner pointOnLine

enum STATE {
	IN, OUT, BOUNDRY
};

const int MAX = 100*1000;
const point O (0.0,0.0);
int X[100],Y[100],n,r;
bool inCircle(point a) {
	double L = length(a);
	return L < r || abs(L-r) < EPS;
}

int circleLineIntersection(const point& p0, const point& p1,const point& cen,long double rad, point& r1, point & r2) {
	if (same(p0,p1)) {
		if (fabs(lengthSqr(vec(p0,cen)) - (rad * rad)) < EPS)
		{
			r1 = r2 = p0;
			return 1;
		}
		return 0;
	}
	double a, b, c, t1, t2;
	a = dot(p1-p0,p1-p0);
	b = 2 * dot(p1-p0,p0-cen);
	c = dot(p0-cen,p0-cen) - rad * rad;
	double det = b * b - 4 * a * c;
	int res;
	if (fabs(det) < EPS)
		det = 0, res = 1;
	else if (det < 0)
		res = 0;
	else
		res = 2;
	det = sqrt(det);
	t1 = (-b + det) / (2 * a);
	t2 = (-b - det) / (2 * a);
	r1 = p0 + (double)t1 * (p1 - p0);
	r2 = p0 + (double)t2 * (p1 - p0);
	return res;
}

bool inRange(double s,double e,double x){
	if(s > e) swap(s,e);
	if(abs(s-x) < EPS) return 1;
	if(abs(e-x) < EPS) return 1;
	return s <= x && x <= e;
}

bool inSegment(point a,point b,point p){
	if(real(a) > real(b)) swap(a,b);
	return  inRange(real(a),real(b),real(p)) && inRange(imag(a),imag(b),imag(p));
}

int MyCircleLineIntersection(const point& p0, const point& p1,const point& cen,long double rad, point& r1, point & r2) {
	int cnt = circleLineIntersection(p0,p1,cen,rad,r1,r2);
	if(cnt == 0) return 0;
	if(cnt == 1) return imag(r1) >= -EPS;
	if(imag(r1) < -EPS) swap(r1,r2);
	if(imag(r1) < -EPS) return 0;
	if(imag(r2) < -EPS) return inSegment(p0,p1,r1);
	if(inSegment(p0,p1,r2)) swap(r1,r2);
	int ret = inSegment(p0,p1,r1) + inSegment(p0,p1,r2);
	return ret;
}


int randint(int s,int e){
	int l = e -s + 1;
	return s + rand()%l;
}

int getSgn(point p,point a,point b) {
	double s = cross(a - p,b - p);
	if(abs(s) < EPS) return 0;
	return (s > 0) - (s < 0);
}

bool inTriangle(point p,point a,point b,point c) {
	int s1 = getSgn(p,a,b),s2 = getSgn(p,b,c),s3 = getSgn(p,c,a);
	if(!s1 || !s2 || !s3) return 1;
	return s1 == s2 && s2 == s3;
}

double work2(point a,point b){
	int cnt = 0;
	for(int i = 0;i < MAX;i++){
		int is = randint(0,MAX);
		int it = randint(0,MAX);
		double s = is*1.0/MAX,t = it*1.0/MAX;
		point p = s*a +  t*b;
		if(!inTriangle(p,O,a,b)) {
			--i;
			continue;
		}
		cnt += inCircle(p);
	}
	return cnt*abs(cross(a,b))/MAX;
}

double getSectorArea(point p,point q) {
	double ct = dot(p,q)/length(p)/length(q);
	double t = acos(ct);
	if(abs(t) < EPS) t = 0;
	if(t < 0) t += PI;
	return r*r*t;
}

double work(point a,point b) {
	if(inCircle(a) && inCircle(b)) return abs(cross(a,b));
	point p,q;
	int cnt = MyCircleLineIntersection(a,b,O,r,p,q);
	if(inCircle(a) || inCircle(b)) {
		assert(cnt == 1);
		if(inCircle(a)) swap(a,b);
		point t;
		assert(MyCircleLineIntersection(O,a,O,r,q,t) == 1);
		return abs(cross(b,p)) + getSectorArea(p,q);
	}
	// either there are 2 intersections or a touch or nothing
	if(cnt <= 1) {
		point A,B,t;
		assert(MyCircleLineIntersection(O,a,O,r,A,t) == 1);
		assert(MyCircleLineIntersection(O,b,O,r,B,t) == 1);
		return getSectorArea(A,B);
	}
	if(real(p) > real(q)) swap(p,q);
	point A,B;
	point t;
	assert(MyCircleLineIntersection(O,a,O,r,A,t) == 1);
	assert(MyCircleLineIntersection(O,b,O,r,B,t) == 1);
	if(real(A) > real(B)) swap(A,B);
	return getSectorArea(A,p) + getSectorArea(B,q) + abs(cross(p,q));
}

double solve(){
	double ans = 0.0;
	for(int i = 0;i < n;i++){
		int j = (i+1)%n;
		int sgn = 0;
		point a (X[i],Y[i]),b (X[j],Y[j]);
		double s = cross(a,b);
		if(abs(s) < EPS) sgn = 0;
		else sgn = (s > 0) - (s < 0);
		double area = work(a,b);
		ans += sgn*area;
	}
	ans = abs(ans)/2;
	return ans;
}

int main(){
	srand(time(0));
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d",&n,&r);
	loop(i,n) scanf("%d %d",X + i,Y + i);
	printf("%.9f\n",solve());
	return 0;
}
