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




int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int s,r;
	while(cin >> s >> r){
		double ans = 0;

		if(s*s <= 2*r*r) {
			ans = s*s;
		}
		else {
			ans = PI*r*r;
			int L2 = 4*r*r-s*s;
			if(L2 > 0) {
				double ct = (2*r*r- L2)/(2.0*r*r);
				double t = acos(ct);
				double A = 0.5*r*r*(t - sin(t));
		//		cout << t * 180/PI << " " << t - sin(t) << " " << A << endl;
				ans -= 4*A;
			}
		}
		printf("%.3f\n",ans);
	}
	return 0;
}
