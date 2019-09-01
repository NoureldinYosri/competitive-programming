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

typedef complex<double> point;
const int MAXN = 111;
pi I[MAXN];
point P[MAXN];
int n;

void read(){
	scanf("%d",&n);
	loop(i,n) scanf("%d %d",&I[i].first,&I[i].second);
}

int cross(pi o,pi a,pi b) {
	a.first -= o.first,a.second -= o.second;
	b.first -= o.first,b.second -= o.second;
	return a.first*b.second - a.second*b.first;
}

double cross(point a,point b){
	return (conj(a)*b).imag();
}

double getTheta(){
	int A = 0;
	for(int i = 1;i+1 < n;i++)
		A += cross(I[0],I[i],I[i+1]);
	assert(A >= 0);
	int a = 0;
	for(int i = 1;i+1 < n;i++) {
		int v = cross(I[0],I[i],I[i + 1]);
		assert(v >= 0);
		if(2*(a + v) >= A){
			point p0 (I[0].first,I[0].second);
			point p (I[i].first,I[i].second);
			point q (I[i+1].first,I[i+1].second);
			double lambda = (A/2.0 - a)/abs(cross(q-p,p-p0));
			point t = p + lambda * (q - p);
			return -arg(t)-PI/2;
		}
		a += v;
	}
}

void solve(){
	double t = getTheta();
	point w = polar(1.0,t);
	loop(i,n) P[i] = point(I[i].first,I[i].second)*w;
}

double val(double x) {
	static char aux[10];
	sprintf(aux,"%.6f",x);
	bool isZero = 1;
	int L = strlen(aux);
	loop(i,L) if(isdigit(aux[i])) isZero &= aux[i] == '0';
	if(isZero) x = 0;
	return x;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	tc(){
		read();
		solve();
		printf("Case %d:\n",t);
		loop(i,n) printf("%.6f %.6f\n",val(P[i].real()),val(P[i].imag()));
	}
	return 0;
}
