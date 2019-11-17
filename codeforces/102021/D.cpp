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


const int MAX = 1 << 20;
int n;
int A[MAX];

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d",&n);
	loop(i,n) scanf("%d",A + i);
	ll L = 0,U = A[0];
	ll v = 0;
	for(int i = 0;i < n;i++) {
		// A[i] - x >= 0
		// A[i] - (s*x0 + v) >= 0
		// A[i] - s*x0 - v >= 0
		// A[i] - v >= s*x0
		v = A[i] - v;
		if(i%2) L = max(L,-v);
		else U = min(U,v);
//		cout << ((i%2) ? "x" : "-x") << " + " << v << ": " << L << " " << U << endl;
	}
	if(L <= U) printf("%lld\n",U-L+1);
	else puts("0");
	return 0;
}
#endif
