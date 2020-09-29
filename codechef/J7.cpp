#pragma GCC optimize ("O3")
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
using namespace std;

const double eps = 1e-12;
double P, S;

double solve(double x1){
	double b = P/4 - x1;
	double c = S/2 - x1*b;
	double d = b*b - 4*c;
	if(abs(d) < eps) d = 0;
	if(d < 0) return -1;
	d = sqrt(d);
	double x2 = (b - d)/2;
	double x3 = (b + d)/2;

	return x1*x2*x3;
}

double get_end(){
	double s = 0,e = P/4;
	while(e - s > eps){
		double m = s + (e-s)/2;
		double V = solve(m);
		if(V < 0) e = m;
		else s = m;
	}
	return s;
}

double solve(){
/*	double s = 0, e = get_end();
	while(e-s > eps){
		double m1 = s + (e-s)/3;
		double m2 = m1 + (e-s)/3;
		if(solve(m1) < solve(m2)) s = m1;
		else e = m2;
	}
	return max(solve(s), solve(e));
*/

	double a = 6, b = -P, c = S;
	double d = b*b - 4*a*c;
	d = sqrt(d);
	double ans = 0;
	loop(i, 2){
		double x = (-b + (2*i - 1)* d)/(2*a);
		double z = P/4 - 2*x;
		ans = max(ans, x*x*z);
	}
	return ans;
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--){
		scanf("%lf %lf", &P, &S);
		printf("%.2f\n", solve());
	}
	return 0;
}
