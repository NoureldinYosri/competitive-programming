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

int n, R;
vi F, S, P;
double dp[50][50*111];
double E;

double solve(int i, int r){
	if(r > R) return r + E;
	if(i == n) return r;
	auto & ret = dp[i][r];
	if(ret == ret) return ret;
	ret = 0;
	for(auto [p, dt] : vector<pair<double, int>>{{P[i]/100.0, F[i]}, {1 - P[i]/100.0, S[i]}}){
		int t = r + dt;
		if(t > R) {
			ret = ret + p*(t + E);
		} else {
			auto e = min(solve(i+1, t), t + E);
			ret = ret + p*e;			
		}
	} 
	return ret;
}

double compute(double t){
	E = t;
	memset(dp, -1, sizeof dp);
	return solve(0, 0);
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	PRESTDIO();
	cin >> n >> R;
	F.resize(n);
	S.resize(n);
	P.resize(n);
	loop(i, n) cin >> F[i] >> S[i] >> P[i];
	memset(dp, -1, sizeof dp);
		
	double s = 0, siz = 1e9;
	for(; siz > 1e-9; siz /= 2.0) {
		double m = s + siz/2.0;
		if(compute(m) > m) s += siz/2.0;
	}
	cout << setprecision(12) << s << endl;
	return 0;
}
