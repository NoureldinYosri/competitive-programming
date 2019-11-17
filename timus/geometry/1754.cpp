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

struct point3d{
	ll P[3];
	point3d(){
		memset(this,0,sizeof *this);
	}
	point3d(double x,double y,double z) {
		P[0] = x;
		P[1] = y;
		P[2] = z;
	}
	friend istream& operator >> (istream & st,point3d & p) {
		loop(i,3) st >> p.P[i];
		return st;
	}
	friend ostream& operator << (ostream & st,const point3d & p) {
		st << "(";
		loop(i,3) {
			st << setprecision(3) << fixed << p.P[i];
			if(i < 2) st << ", ";
		}
		st << ")";
		return st;
	}

	point3d operator - (const point3d & o) {
		point3d ret;
		loop(i,3) ret.P[i] = P[i] - o.P[i];
		return ret;
	}
	point3d cross(const point3d & o) {
		point3d ret;
		loop(i,3) {
			int sgn = (i%2 == 0) ? 1 : -1;
			ret.P[i] = 0;
			int j = (i == 0) ? 1 : 0;
			int k = 3 - i - j;
			ret.P[i] = sgn*(P[j]*o.P[k] - P[k]*o.P[j]);
		}
		return ret;
	}
	ll dot(const point3d & o) {
		ll ret = 0;
		loop(i,3) ret += P[i]*o.P[i];
		return ret;
	}
	bool isZero(){
		loop(i,3) if(P[i]) return 0;
		return 1;
	}
	double length(){
		double res = 0;
		loop(i,3) res += P[i]*(double)P[i];
		return sqrt(res);
	}
	ll z(){
		return P[2];
	}
	void norm(){
		ll g = 0;
		loop(i,3) {
			ll v = abs(P[i]);
			if(!v) continue;
			g = __gcd(g,v);
		}
		if(!g) g = 1;
		loop(i,3) P[i] /= g;
	}
};


int mana,h,H;
point3d P[5];

bool leq(double x,double y) {
	return x < y || abs(x-y) < 1e-12;
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	cin >> mana >> h >> H;
	if(mana < h) {
		puts("NO");
		return 0;
	}
	ll r = mana - h;
	loop(i,5) {
		double x,y; cin >> x >> y;
		P[i] = point3d(x,y,0);
	}
	P[4].P[2] = H;

	vector<point3d> pyramid{P+1,P+5};
	point3d p = P[0];
	p.P[2] = h;

	for(int a = 0;a < 4;a++) {
		int b = (a + 1)%4;
		int c = (b + 1)%4;


		point3d x = pyramid[b] - pyramid[a];
		point3d y = pyramid[c] - pyramid[a];
		point3d n = x.cross(y);
		n.norm();

		ll d = abs(n.dot(p - pyramid[a]));

		if(leq(d,r*n.length())) {
			puts("YES");
			return 0;
		}
	}
	puts("NO");
	return 0;
}
#endif
