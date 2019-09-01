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

using point = complex<double>;


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int len[3];
	loop(i,3) cin >> len[i];
	loop(i,3) {
		int j = (i + 1)%3;
		int k = 3 - i - j;
		int l = abs(len[j] - len[k]),r = len[j] + len[k];
		if(len[i] <= l || r <= len[i]){
			puts("Impossible");
			return 0;
		}
	}
	double a = len[0],b = len[1],c = len[2];
	double ct = (a*a + c*c - b*b)/(2.0*a*c);
	double t = acos(ct);
	point A(0.0,0.0);
	point B(a,0);
	point C = polar(c,t);
	point T[3] = {A,B,C};
	loop(i,3) printf("%.9f %.9f\n",T[i].real(),T[i].imag());
	return 0;
}
#endif
