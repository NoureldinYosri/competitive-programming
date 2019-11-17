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

point S,D;
point B;
point R;
double rB,rR;

point read(){
	double x,y; cin >> x >> y;
	return point(x,y);
}

double dot(point a,point b){
	return (conj(a)*b).real();
}

double len(point p) {
	return sqrt(dot(p,p));
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	S = read();
	D = read();
	B = read();
	cin >> rB;
	R = read();
	cin >> rR;

	S -= R;
	D -= R;
	double L = len(D - S);
	double d1 = len(S);
	double d2 = len(D);
	double r = rR;
	double l1 = sqrt(d1*d1 - r*r);
	double l2 = sqrt(d2*d2 - r*r);
	double t1 = atan2(l1,r);
	double t2 = atan2(l2,r);
	double c = (d1*d1 + d2*d2 - L*L)/(2*d1*d2);
	c = max(c,-1.0);
	c = min(c,1.0);
	double t123 = acos(c);
	double t3 = t123 - t1 - t2;
//	cout << t1*180/PI << " " << t2*180/PI << " " << t3*180/PI << endl;
	double ans = l1 + l2 + t3*r;
	printf("%.10f\n",ans);
	return 0;
}
#endif
