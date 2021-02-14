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

const int MAXW = 200;

double f(int n, int m){
	if(gcd(n, m) == 1) return sqrt(n*(ll)n + m*(ll)m);
	if(n > m) swap(n, m);
	double ret = 1e18;
	for(int x = 0; x <= n; x++){
		int y = (x*(ll)m)/n - 1;
		y = max(y, 0);
		loop(i, 5){
//			cerr << pi(x, y) << " " << pi(n - x, m - y) << endl;
			if(y <= m && x+y > 0 && pi(x, y) != pi(n - x, m - y) && 
				gcd(x, y) == 1 && gcd(n - x, m - y) == 1)
				ret = min(ret, hypot(x, y) + hypot(n - x, m - y));
			y++;
		}

	}
	
	return ret;
}



int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--) {
		int n, m; scanf("%d %d", &n, &m);
		printf("%.10f\n", f(n, m));
	}
	return 0;
}
