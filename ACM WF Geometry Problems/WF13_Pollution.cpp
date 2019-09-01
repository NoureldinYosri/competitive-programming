#ifdef ACTIVE
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
typedef std::vector<int> vi;
typedef std::pair<int, int> pi;
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
template<class A, class B>
std::ostream& operator <<(std::ostream &st, const std::pair<A, B> p) {
	st << "(" << p.first << ", " << p.second << ")";
	return st;
}
#define tc() int T; scanf("%d",&T); for(int t = 1;t <= T;t++)
using namespace std;

const double EPS = 1e-12;
using point = complex<double>;
const int MAX = 111;
int n, R;
point P[MAX];

bool same(double a,double b) {
	return abs(a-b) < EPS;
}

bool leq(double a, double b) {
	return a < b || abs(a - b) < EPS;
}

double dot(point a, point b) {
	return (conj(a) * b).real();
}
double cross(point a, point b) {
	return (conj(a) * b).imag();
}
double cross(point o, point a, point b) {
	return cross(a - o, b - o);
}
double dist(point a) {
	return sqrt(dot(a, a));
}

double getArc(point a, point b) {
	point ab = a - b;
	double L2 = dot(ab,ab);
	double ct = (R*R + R*R - L2)/(2*R*R);
	double t = acos(ct);
//	cout << a << " " << b << " " << 0.5*R*R*(t - sin(t)) << " " << t*180/PI << " " << L2 << " " << ct << endl;
	return 0.5 * R * R * (t - sin(t));
}

bool inCircle(point p) {
	return leq(dot(p, p), R * R);
}

struct vertex{
	point p;
	int nxt;
	vertex() {
		nxt = -1;
	}
	vertex(point q) {
		p = q;
		nxt = -1;
	}
};

void getInter(point A,point B,vector<vertex> & poly,vi & circum) {
	point a = A,b = B - A;
	double L = dist(b);
	b /= L;
	double u = 2*(a.real()*b.real() + a.imag()*b.imag());
	double v = dot(a,a) - R*R;
	double det = u*u-4*v;
	if(leq(0,det)) {
		det = sqrt(det);
		double l1 = (-u - det)/2,l2 = (-u + det)/2;
		if(leq(0,l1) && leq(l2,L)) {
			vertex f1(a + l1*b),f2(a + l2*b);
			int i = sz(poly),j = i +1;
			f1.nxt = j;
			poly.push_back(f1);
			circum.push_back(i);
			poly.push_back(f2);
			circum.push_back(j);
			return;
		}
		bool f1 = 0,f2 = 0;
		f1 = leq(0,l1) && leq(l1,L);
		f2 = leq(0,l2) && leq(l2,L);
		assert(!(f1 && f2));
		if(f1 || f2) {
			double l = f1 ? l1 : l2;
			point p = a + l*b;
			circum.push_back(poly.size());
			vertex f(p);
			if(inCircle(A)) poly.back().nxt = poly.size();
			if(inCircle(B)) f.nxt = sz(poly) + 1;
			poly.push_back(f);
		}
	}
}

double solve() {
	vector<vertex> poly;
	vi circum;
	P[n] = P[0];
	loop(i,n) {
		if(inCircle(P[i])) {
			poly.push_back(P[i]);
			if(inCircle(P[i+1])) {
				poly.back().nxt = poly.size();
				continue;
			}
		}
		getInter(P[i],P[i+1],poly,circum);
	}
//	for(auto f : poly) {
//		cout << f.p << " " ;
//		if(f.nxt == -1) cout << -1 << endl;
//		else cout << poly[f.nxt].p << endl;
//	}
	n = sz(poly);
	assert(sz(circum)%2 == 0);
	sort(all(circum),[poly](const int & a,const int & b) {
		return poly[a].p.real() < poly[b].p.real();
	});
	double ans = 0;
	vector<bool> hasIn(n,0);
	for(auto & p : poly) {
		assert(p.nxt <= sz(poly));
		if(p.nxt == sz(poly)) p.nxt = 0;
		if(p.nxt != -1) hasIn[p.nxt] = 1;
	}
	for(int j = sz(circum)-1;j >= 0;j--) {
		int i = circum[j];
		if(poly[i].nxt != -1) continue;
		int k = j - 1;
		while(1) {
			if(k < 0) k += sz(circum);
			if(!hasIn[circum[k]]) break;
			k--;
		}
		poly[i].nxt = circum[k];
		ans += getArc(poly[i].p,poly[circum[k]].p);
	}
	vector<bool> vis(n,0);
	vector<point> aux;
	for(int i = 0;i < n;i++) if(!vis[i]) {
		aux.clear();
		int j = i;
//		cout << "polygon: ";
		while(!vis[j]) {
			vis[j] = 1;
			aux.push_back(poly[j].p);
//			cout << poly[j].p << " ";
			j = poly[j].nxt;
			assert(j != -1);
		}
//		cout << endl;
		if(sz(aux) < 3) continue;
		int m = sz(aux);
		double tmp = 0;
		for(int j = 1;j+1 < m;j++)
			tmp += cross(aux[0],aux[j],aux[j+1]);
		tmp = abs(tmp)/2.0;
		ans += tmp;
	}
	return ans;
}

pi I[MAX];

int main() {
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	while (scanf("%d %d", &n, &R) == 2) {
		loop(i,n)
		{
			int x, y;
			scanf("%d %d", &x, &y);
			P[i] = point(x, y);
			I[i] = pi(x,y);
		}
//		printf("Circle 0 0 %d\n",R);
//		loop(i,n) {
//			int j = (i + 1)%n;
//			printf("Segment %d %d %d %d\n",I[i].first,I[i].second,I[j].first,I[j].second);
//		}
		printf("%.6f\n", solve());
	}
	return 0;
}
#endif
