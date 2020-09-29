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


const double eps = 1e-15;
int n, D;
int speed[111];

double snell(double st, double t0, double s0){
	return asin(st*sin(t0)/s0);
}

double get_X(double theta){
	double x = 0;
	loop(i, n){
		x += 100*tan(theta);
		if(i+1 < n) theta = snell(speed[i+1], theta, speed[i]);
	}
	return x;
}

double get_time(double theta){
	double t = 0;
	loop(i, n){
		t += 100/(speed[i]*cos(theta));
		if(i+1 < n) theta = snell(speed[i+1], theta, speed[i]);
	}
	return t;
}

double solve(){
	double s = 0, len = M_PI/2;
	for(;len > eps; len /= 2.0){
		double m = s + len/2.0;
		if(get_X(m) < D) s = m;
	}
	return get_time(s);
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	for(int t = 1; t <= T;t++){
		scanf("%d %d", &n, &D);
		loop(i, n) scanf("%d", &speed[i]);
		printf("Case %d: %.9f\n", t, solve());
	}
	return 0;
}
