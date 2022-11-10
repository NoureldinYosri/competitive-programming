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
const int MAXN = 100*1000 + 10;
ll X[MAXN], V[MAXN];
int n;

double T(double x){
	double ret = 0;
	loop(i, n) ret = max(ret, abs(X[i] - x)/V[i]);
	
	return ret;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d", &n);
	loop(i, n) scanf("%lld %lld", X + i, V + i);
	double s = *min_element(X, X + n), e = *max_element(X, X + n);
	for(int t = 0; t < 70 && e-s > eps; t++){
		double m1 = s + (e-s)/3;
		double m2 = m1 + (e-s)/3;
		if(T(m1) < T(m2)) e = m2 - eps;
		else s = m1 + eps;
	}
	printf("%.10f\n", T(s));
	return 0;
}