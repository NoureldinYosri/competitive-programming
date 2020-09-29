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

int read_scaled_double(){
	static char buffer[50];
	scanf("%s", buffer);
	int L = strlen(buffer);
	int sgn = (buffer[0] == '-') ? -1 : 1;
	int i = find(buffer, buffer + L, '.') - buffer;
	int x = 0, y = 0;
	sscanf(buffer, "%d", &x); 
	if(i != L) {
		sscanf(buffer + i + 1, "%d", &y);
		int have = L - i - 1;
		while(have < 3) y *= 10, have ++;
		assert(have == 3);
	}
	if(x) sgn = 1; 
	return (x*1000 + y)*sgn;
}

int getScore(double x, double y, int w){
	double t = atan2(y, x);
	if(abs(t) < 1e-12) t = 0;
	if(t < 0) t += 2*PI;
	return ceil((t*w)/(2*PI));
}

void tc(){
	int w;
	ll b, d, s; scanf("%d %lld %lld %lld", &w, &b, &d, &s);
	b *= b;
	d *= d;
	s *= s;
	int n; scanf("%d", &n);
	int ans = 0;
	loop(i, n){
		double x, y; scanf("%lf %lf", &x, &y);
		double r2 = x*x + y*y;
		if(r2 <= b) ans += 50;
		else if(r2 <= s) {
			int v = getScore(x, y, w);
			if(r2 <= d) v <<= 1;
			ans += v;
		}
	}
	
	printf("%d\n", ans);
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--) tc();
	return 0;
}
