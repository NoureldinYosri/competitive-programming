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

ll X[2], Y[2], R[2];
ll dist2;
long double dist;

ll sq(ll x){
	return x*x;
}

double solve(){
	if(dist2 >= sq(R[0] + R[1])) return 0;
	
	if(R[0] < R[1]){
		swap(X[0], X[1]);
		swap(Y[0], Y[1]);
		swap(R[0], R[1]);
	}

	if(dist2 <= sq(R[0] - R[1])) return PI * sq(R[1]);
	
	
	if(dist2 > sq(R[0])) {
		long double theta[2];
		long double ans = 0;
		loop(i, 2){
			long double & t = theta[i];
			t = (dist2 + (long double)sq(R[i]) - pow((long double)R[i^1], 2))/(2*dist*R[i]);
			t = acos(t);
			if(abs(t) < eps) t = 0;
			t = 2*t;
//			cerr << R[i] << " " << t*180/PI << ": " << 0.5*sq(R[i])*(t - sin(t)) << endl;
			ans += 0.5*sq(R[i])*(t - sin(t));
//			cerr << t*180/PI << endl;
		}
		return ans;
	}
	double ct = (sq(R[1]) + dist2 - sq(R[0]))/(2*R[1]*dist);
	double theta = 0;
	if(abs(ct) < eps) ct = 0;
	if(ct < 0) theta = PI - acos(-ct);
	else theta = acos(ct);
	
	theta = 2*theta;
	theta = 2*PI - theta;
	double ans = PI*sq(R[1]);
	ans -= 0.5*sq(R[1])*(theta - sin(theta));
	ct = (sq(R[0]) + (double)dist2 - sq(R[1]))/(2*R[0]*dist);
	if(abs(ct) < eps) ct = 0;
	double phi = (ct >= 0) ? 2*acos(ct) : (2*(PI - acos(-ct)));
	ans += 0.5*sq(R[0])*(phi - sin(phi));
	
	return ans;	
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	loop(i, 2) cin >> X[i] >> Y[i] >> R[i];
	dist2 = (X[0] - X[1])*(X[0] - X[1]) + (Y[0] - Y[1])*(Y[0] - Y[1]);
	dist = sqrt(dist2);
	
	printf("%.30f\n", solve());
	
	return 0;
}
