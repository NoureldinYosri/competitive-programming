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

using point = complex<long double>;

const double eps = 1e-9;
point P[4];
point p0,r,n;
double D[4];
int sgn[4];

bool same(double x,double y){
	return abs(x-y) < eps;
}
bool leq(double x,double y) {
	return x < y || same(x,y);
}

double dot(point p,point q) {
	return (p*conj(q)).real();
}
double cross(point p,point q) {
	return (conj(p)*q).imag();
}

double norm(point p) {
	return dot(p,p);
}

double getLength(point p) {
	return sqrt(norm(p));
}

void readLine(){
	double A,B,C;
	cin >> A >> B >> C;
	if(abs(B) > eps) p0 = point(0.0,-C/B);
	else p0 = point(-C/A,0.0);

	n = point(A,B);
	n /= getLength(n);
	r = point(-n.imag(),n.real());
	if(r.real() < 0) r *= -1.0;
	if(n.real() < 0) n *= -1.0;
//	cout << p0 << " " << r << " " << n << endl;
}


bool getS(const vi & ord,double & s) {
	loop(i,4) {
		int j = (i + 1)%4;
		int k = (j + 1)%4;
		double d1 = D[ord[i]]*sgn[i];
		double d2 = D[ord[j]]*sgn[j];
		double d3 = D[ord[k]]*sgn[k];
		double t = hypot(d2-d1,d3-d2);
		if(!i) {
			s = t;
//			cout << "set s to " << t << endl;
		}
		else if(!same(s,t)) {
//			cout << t << " != " << s << endl;
			return 0;
		}
	}
	return 1;
}

bool check(double s2,double *L,const vi & ord) {
	double d1 = D[ord[0]]*sgn[0],d4 = D[ord[3]]*sgn[3];
	double D2 = (d4 - d1)*(d4 - d1);
	double l = L[3];
	if(!same(s2,l*l + D2)) return 0;
	loop(j,4) {
		long double d = D[ord[j]]*sgn[j];
		long double l = L[j];
		int i = ord[j];
		P[i] = p0 + l*r + d*n;
	}
//	loop(j,4) cout << P[j] << endl;
//	cout << string(20,'-') << endl;
	loop(j,4) {
		int a = ord[j];
		int b = ord[(j + 1)%4];
		int c = ord[(j+2)%4];
		if(same(0.0,cross(P[b]-P[a],P[c]-P[a]))) return 0;
		if(!same(0.0,dot(P[a] - P[b],P[c]-P[b]))) return 0;
	}
	return 1;
}

bool bt(int i,double *L,const vi & ord,double s2) {
	if(i == 4) {
		bool res = check(s2,L,ord);
//		cerr << res << ": " ;
//		prArr(L,4,double);
		return res;
	}
	double d2 = D[ord[i]]*sgn[i],d1 = D[ord[i - 1]]*sgn[i-1];
	double D = d2-d1;
	double D2 = D*D;
	if(!leq(D2,s2)) return 0;
	double g = max(0.0,s2 - D2);
	g = sqrt(g);
	L[i] = L[i - 1] + g;
	if(bt(i+1,L,ord,s2)) return 1;
	L[i] = L[i - 1] - g;
	return bt(i+1,L,ord,s2);
}

bool solve(const vi & ord) {
	double s;
	if(!getS(ord,s) || same(s,0)) return 0;
//	cout << s << endl;
	double s2 = s*s;
	double L[4] = {0,0,0,0};
	return bt(1,L,ord,s2);
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	readLine();
	loop(i,4) cin >> D[i];
	vi ord;
	loop(i,4) ord.push_back(i);
	do{
		loop(msk,1 << 3) {
			int cm = msk << 1;
			loop(i,4) {
				sgn[i] = (cm >> i)&1;
				sgn[i] = 1-2*sgn[i];
			}
			if(solve(ord)) {
				loop(i,4) {
					printf("%.9f %.9f\n",(double)P[i].real(),(double)P[i].imag());
				}
				return 0;
			}
		}
	}while(next_permutation(ord.begin() + 1,ord.end()));
	cout << "Impossible" << endl;
	return 0;
}

/*
2.23607
3.16228
2.23607
3.16228
 *
 */
#endif
