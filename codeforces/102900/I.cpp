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


double compute(int i, int m, const vector<double> & arcs){
	double ret = 0;
	
	for(int d = 1; d <= m; d++){
		int s = 1 + (d != m);
		double x = d*arcs[i];
		for(int j = 0; j < i; j++){
			x = min(x, 2*(i - j) + arcs[j]*d);
		}
		ret += x*s;
	}
	return ret;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int n, m; scanf("%d %d", &n, &m);
	vector<double> f(n + 1), arcs(n + 1);
	for(int i = 0; i <= n; i++){
		arcs[i] = (2*PI*i)/(2*m);
	}
	for(int i = 0; i <= n; i++){
		f[i] = compute(i, m, arcs);
	}
//	print(f, double);
	double ans = 0;
	for(auto x : f) ans += m*x;
	loop(i, sz(f)) loop(j, i) {
		int k = (j > 0) ? (2*m) : (m > 1);
		double v = (i - j)*k + f[j];
		ans += 2*m*v;
	}
	printf("%.10f\n", ans);
	return 0;
}
