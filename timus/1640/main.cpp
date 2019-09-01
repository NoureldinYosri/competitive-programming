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

const int MAX = 100,EPS = 1e-6;
pi I[MAX];
point P[MAX];
int n;


void moveLowestToFront(){
	int c = min_element(I,I + n,[](const pi & a,const pi & b) {
		return tie(a.second,a.first) < tie(b.second,b.first);
	}) - I;
	if(c) swap(I[c],I[0]);
	loop(i,n) P[i] = point(I[i].first,I[i].second);
}

double len(point p,bool takeRoot = 1) {
	double ret = (p*conj(p)).real();
	if(takeRoot) ret = sqrt(ret);
	return ret;
}

bool same(double a,double b) {
	return abs(a-b) < EPS;
}

bool leq(double a,double b) {
	return a < b || same(a,b);
}

bool cond(point O,double R) {
	R *= R;
//	cerr << O << endl;
	loop(i,n){
		double d = len(O - P[i],0);
		if(!leq(d,R) || same(d,0)) {
//			cerr << "failed on " << P[i] << " " << R-d << endl;
			return 0;
		}
	}
	return 1;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	while(scanf("%d",&n) == 1){
		loop(i,n) scanf("%d %d",&I[i].first,&I[i].second);
		moveLowestToFront();
		double R = 0;
		point O (1001.0,1001.0);
		loop(i,n) R = max(R,len(O - P[i],0));
		R = sqrt(R);
		printf("%.10f %.10f %.10f\n",O.real(),O.imag(),R);
	}
	return 0;
}
#endif
