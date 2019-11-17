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

point read(){
	double x,y;
	cin >> x >> y;
	return point(x,y);
}

double dot(point p,point q) {
	return (conj(p)*q).real();
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	point p = read();;
	int r; cin >> r;
	point q = read();
	int R; cin >> R;
	if(R < r) {
		swap(r,R);
		swap(p,q);
	}
	point dir = p - q;
	double dist = sqrt(dot(dir,dir));
	double rd = (r + R - dist)/2.0;
	dist = max(dist,0.0);
	if(dist > 0) dir /= dist;
	point c = q + dir * (R - rd);
	printf("%.10f %.10f %0.10f\n",c.real(),c.imag(),rd);
	return 0;
}
#endif
